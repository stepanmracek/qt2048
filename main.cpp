#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "gamemodel.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	GameModel model(4);
	model.setData(3, 0, 4);
	model.setData(2, 0, 4);
	model.setData(1, 0, 2);
	model.setData(0, 0, 2);

	model.setData(3, 1, 4);
	model.setData(2, 1, 4);
	model.setData(1, 1, 2);
	model.setData(0, 1, 0);

	model.setData(3, 2, 4);
	model.setData(2, 2, 0);
	model.setData(1, 2, 0);
	model.setData(0, 2, 4);

	model.setData(3, 3, 0);
	model.setData(2, 3, 0);
	model.setData(1, 3, 0);
	model.setData(0, 3, 2);

	model.print();

	/*model.playerMove(GameModel::Right);
	model.print();

	model.computerMove();
	model.print();

	model.playerMove(GameModel::Down);
	model.print();

	model.computerMove();
	model.print();

	model.playerMove(GameModel::Up);
	model.print();

	model.computerMove();
	model.print();

	model.playerMove(GameModel::Left);
	model.print();

	model.computerMove();
	model.print();*/

	QQmlApplicationEngine engine;

	engine.rootContext()->setContextProperty("game", &model);

	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
