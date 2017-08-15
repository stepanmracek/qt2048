#include "gamemodel.h"

#include <iostream>

GameModel::GameModel(int size, QObject *parent):
	QAbstractListModel(parent),
	_size(size),
	_score(0),
	_data(size * size)
{ }

QVariant GameModel::data(const QModelIndex &index, int role) const {
	if (role == ValueRole)
		return QVariant::fromValue(_data.at(index.row()));
	else
		return QVariant();
}

int GameModel::data(int row, int col) const {
	return data(index(_size * row + col), ValueRole).toInt();
}

bool GameModel::setData(const QModelIndex &index, const QVariant &value, int role) {
	if (role == ValueRole) {
		bool ok;
		int newValue = value.toInt(&ok);
		if (!ok) return false;

		int oldValue = _data.at(index.row());
		if (newValue != oldValue) {
			_data[index.row()] = newValue;
			QVector<int> roles;
			roles << ValueRole;
			emit dataChanged(index, index, roles);
			return true;
		}
		return false;
	}
	return false;
}

bool GameModel::setData(int row, int col, int value) {
	return setData(index(_size * row + col), value, ValueRole);
}

Qt::ItemFlags GameModel::flags(const QModelIndex &index) const {
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QHash<int, QByteArray> GameModel::roleNames() const {
	QHash<int, QByteArray> rn = QAbstractListModel::roleNames();
	rn[ValueRole] = "value";
	return rn;
}

void GameModel::print() {
	for (int r = 0; r < _size; r++) {
		for (int c = 0; c < _size; c++) {
			std::cout << _data[_size * r + c] << " ";
		}
		std::cout << std::endl;
	}
}

bool GameModel::playerMove(int direction) {
	int start = 0;
	int step = 1;
	if (direction == Direction::Down || direction == Direction::Right) {
		start = _size - 1;
		step = -1;
	}

	bool change = false;
	for (int c = 0; c < _size; c++) {
		QVector<int> newValues;
		int lastVal = -1;
		int r = start;
		for (int tmp = 0; tmp < _size; tmp++, r = r + step) {
			int val = (direction == Direction::Up || direction == Direction::Down) ? data(r, c) : data(c, r);

			if (!val) {
				if (tmp == _size - 1 && lastVal > 0)
					newValues.push_back(lastVal);

			} else if (lastVal == val) {
				newValues.push_back(2 * val);
				setScore(_score + 2 * val);
				lastVal = -1;
			} else {
				if (lastVal > 0)
					newValues.push_back(lastVal);

				if (tmp == _size - 1)
					newValues.push_back(val);

				lastVal = val;
			}
		}

		newValues.resize(_size);
		for (int tmp = 0, r = start; tmp < _size; tmp++, r = r + step) {
			if (direction == Direction::Up || direction == Direction::Down)
				change = change | setData(r, c, newValues[tmp]);
			else
				change = change | setData(c, r, newValues[tmp]);
		}
	}
	return change;
}

bool GameModel::computerMove() {
	QVector<QModelIndex> free;
	for (int r = 0; r < _size; r++) {
		for (int c = 0; c < _size; c++) {
			if (!data(r, c)) free.append(index(_size * r + c));
		}
	}

	if (!free.size()) return false;

	setData(free[rand() % free.size()], 2, ValueRole);
	return true;
}

void GameModel::setScore(int score) {
	if (_score != score) {
		_score = score;
		emit scoreChanged(score);
	}
}

int GameModel::score() { return _score; }

void GameModel::reset() {
	_data = QVector<int>(_size * _size);
	_score = 0;

	computerMove();
	computerMove();
}
