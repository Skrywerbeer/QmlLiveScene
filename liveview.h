#ifndef LIVEVIEW_H
#define LIVEVIEW_H

#include <QObject>
#include <QQuickView>
#include <QQmlEngine>
#include <QQuickItem>
#include <QUrl>
#include <QTimer>
#include <QDateTime>

class LiveView : public QQuickView {
		Q_OBJECT
	public:
		explicit LiveView(QUrl &file, QWindow *parent = nullptr);
		explicit LiveView(QWindow *parent = nullptr);

		void setFile(QUrl &file);

	public slots:
		void reloadFile();

	private slots:
		void statusChangedHandler();

	signals:
		void fileChanged();

	private:
		QUrl _qmlUrl;
		static const QUrl errorPage;
		QTimer *_refreshTimer;
		QDateTime _lastModifiedTime;

		void initTimer();
};

#endif // LIVEVIEW_H
