#include "liveview.h"

const QUrl LiveView::errorPage("qrc:/qml/ErrorPage.qml");

LiveView::LiveView(QUrl &file, QWindow*parent) :
    QQuickView(parent),
    _qmlUrl(file) {
	setFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	connect(this, &QQuickView::statusChanged,
	        this, &LiveView::statusChangedHandler);
	setSource(_qmlUrl);
	initTimer();
	initControlPanel();
}

LiveView::~LiveView() {
	_controlPanel->deleteLater();
}

void LiveView::setFile(QUrl &file) {
	if (file == _qmlUrl)
		return;
	_qmlUrl = file;
	setSource(_qmlUrl);
	emit fileChanged();
}

void LiveView::timerEvent(QTimerEvent *event) {
	QFile qmlFile(_qmlUrl.toString());
	const QDateTime modTime = qmlFile.fileTime(QFileDevice::FileModificationTime);
	if (modTime != _lastModifiedTime) {
		_lastModifiedTime = modTime;
		reloadFile();
	}
}

void LiveView::reloadFile() {
	engine()->clearComponentCache();
	setSource(_qmlUrl);
}

void LiveView::checkForUpdate() {
	QFile qmlFile(_qmlUrl.toString());
	const QDateTime modTime = qmlFile.fileTime(QFileDevice::FileModificationTime);
	if (modTime != _lastModifiedTime) {
		_lastModifiedTime = modTime;
		reloadFile();
	}
}

void LiveView::statusChangedHandler() {
	if (status() == QQuickView::Error) {
		    const QString errMsg(errors().at(0).toString());
			engine()->clearComponentCache();
			setSource(errorPage);
			rootObject()->setProperty("message", errMsg);
	}
}

void LiveView::quit() {
	QCoreApplication::quit();
}

void LiveView::initTimer() {
	QFile qmlFile(_qmlUrl.toString());
	_lastModifiedTime = qmlFile.fileTime(QFileDevice::FileModificationTime);
	startTimer(1000);
}

void LiveView::initControlPanel() {
	_controlPanel = new QQuickView(QUrl("qrc:/qml/ControlPanel.qml"));
	_controlPanel->setFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	_controlPanel->setTitle("Controls");
	_controlPanel->setPosition(x() + width(), y());

	connect(this, &QQuickView::widthChanged, [=]() {
		_controlPanel->setX(x() + width());
	});
	connect(this, &QQuickView::xChanged, [=]() {
		const int RIGHT_EDGE = x() + width();
		if ((RIGHT_EDGE+_controlPanel->width()) > screen()->availableGeometry().width())
			_controlPanel->setX(x() - _controlPanel->width());
		else
			_controlPanel->setX(x() + width());
	});
	connect(this, &QQuickView::heightChanged, [=]() {
		_controlPanel->setY(y());
	});
	connect(this, &QQuickView::yChanged, [=]() {
		_controlPanel->setY(y());
	});
	connect(_controlPanel->rootObject(), SIGNAL(reload()),
	        this, SLOT(reloadFile()));
	connect(_controlPanel->rootObject(), SIGNAL(close()),
	        this, SLOT(quit()));
	connect(_controlPanel->rootObject(), SIGNAL(move()),
	        this, SLOT(startSystemMove()));
	_controlPanel->show();
}
