#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "gamemodel.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	GameModel model(4);
	model.reset();

	QQmlApplicationEngine engine;

	engine.rootContext()->setContextProperty("game", &model);

	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
