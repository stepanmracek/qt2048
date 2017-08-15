#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QAbstractListModel>

class GameModel : public QAbstractListModel
{
	Q_OBJECT

	Q_PROPERTY(int score READ score WRITE setScore NOTIFY scoreChanged)

public:
	explicit GameModel(int size, QObject *parent = nullptr);

	enum Direction {
		Left,
		Right,
		Up,
		Down
	};

	int rowCount(const QModelIndex &parent = QModelIndex()) const { return _size * _size; }
	int columnCount(const QModelIndex &parent = QModelIndex()) const { return 1; }
	QHash<int, QByteArray> roleNames() const;
	QVariant data(const QModelIndex &index, int role) const;
	int data(int row, int col) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	bool setData(int row, int col, int value);
	Qt::ItemFlags flags(const QModelIndex &index) const;

	enum RoleNames {
		ValueRole = Qt::UserRole + 1
	};

	void print();

	Q_INVOKABLE bool playerMove(int direction);
	Q_INVOKABLE bool computerMove();
	Q_INVOKABLE int size() { return _size; }
	Q_INVOKABLE void reset();

	void setScore(int score);
	int score();

signals:
	void scoreChanged(int score);

private:
	int _size;
	int _score;
	QVector<int> _data;
};

#endif // GAMEMODEL_H
