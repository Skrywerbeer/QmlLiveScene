#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>

#include <QQmlContext>

#include <QDebug>

#include "liveview.h"

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QCommandLineParser parser;
	parser.addHelpOption();
	parser.addPositionalArgument("file", "The qml file to load");

	QGuiApplication app(argc, argv);
	parser.process(app);
	if (parser.positionalArguments().size() != 1)
		parser.showHelp();

	QUrl file(parser.positionalArguments().at(0));
	LiveView live(file);
	live.show();
	qDebug() << live.rootContext()->nameForObject(live.rootObject());

	return app.exec();
}
