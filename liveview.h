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
		~LiveView();

		void setFile(QUrl &file);

		bool event(QEvent *event) override;

	public slots:
		void reloadFile();
		void checkForUpdate();

	private slots:
		void statusChangedHandler();
		void quit();

	signals:
		void fileChanged();

	private:
		QUrl _qmlUrl;
		QQuickView *_controlPanel;
		static const QUrl errorPage;
		QTimer *_refreshTimer;
		QDateTime _lastModifiedTime;

		void initTimer();
		void initControlPanel();
};

#endif // LIVEVIEW_H
