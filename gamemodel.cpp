#include "gamemodel.h"

#include <iostream>

GameModel::GameModel(int size, QObject *parent):
	QAbstractListModel(parent),
	_size(size),
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
		}
		return true;
	} else {
		return false;
	}
}

void GameModel::setData(int row, int col, int value) {
	int i = _size * row + col;
	QModelIndex idx = index(i);
	setData(idx, value, ValueRole);
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

void GameModel::playerMove(int direction) {
	int start = 0;
	int step = 1;
	if (direction == Direction::Down || direction == Direction::Right) {
		start = _size - 1;
		step = -1;
	}

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
				setData(r, c, newValues[tmp]);
			else
				setData(c, r, newValues[tmp]);
		}
	}
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
