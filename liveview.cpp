#include "liveview.h"

const QUrl LiveView::errorPage("qrc:/pages/ErrorPage.qml");

LiveView::LiveView(QUrl &file, QWindow*parent) :
    QQuickView(parent),
    _qmlUrl(file),
    _refreshTimer(new QTimer) {
//	setFlag(Qt::WindowStaysOnTopHint, true);
//	setFlag(Qt::FramelessWindowHint, true);
	setFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

	connect(this, &QQuickView::statusChanged,
	        this, &LiveView::statusChangedHandler);

	setSource(_qmlUrl);
	initTimer();
}

LiveView::LiveView(QWindow *parent) :
    QQuickView(parent) {

}

void LiveView::setFile(QUrl &file) {
	if (file == _qmlUrl)
		return;
	_qmlUrl = file;
	setSource(_qmlUrl);
	emit fileChanged();
}

void LiveView::reloadFile() {
	QFile qmlFile(_qmlUrl.fileName());
	const QDateTime modTime = qmlFile.fileTime(QFileDevice::FileModificationTime);
	if (modTime != _lastModifiedTime) {
		_lastModifiedTime = modTime;
		engine()->clearComponentCache();
		setSource(_qmlUrl);
	}
}

void LiveView::statusChangedHandler() {
//	const auto errs = errors();
	if (status() == QQuickView::Error) {
		    const QString errMsg(errors().at(0).toString());
			engine()->clearComponentCache();
			setSource(errorPage);
			rootObject()->setProperty("message", errMsg);
	}
}

void LiveView::initTimer() {
	const uint REFRESH_TIMEOUT = 1000;
	_refreshTimer->setInterval(REFRESH_TIMEOUT);
	_refreshTimer->setSingleShot(false);
	QFile qmlFile(_qmlUrl.fileName());
	_lastModifiedTime = qmlFile.fileTime(QFileDevice::FileModificationTime);
	connect(_refreshTimer, &QTimer::timeout,
	        this, &LiveView::reloadFile);
	_refreshTimer->start();
}
