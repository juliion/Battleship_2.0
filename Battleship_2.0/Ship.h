#pragma once
#include <iostream>
#include <vector>
#include "Cell.h"
using std::vector;

enum Direction
{
	undirected,
	up,
	down,
	left,
	right
};

class Ship
{
	vector<Cell*> partsOfShip;
	int length;
	int direction;
	bool live;
public:
	Ship(int l) : length{ l }, direction{ undirected }, live{ true } { }
	int getLength();
	void setDirection(int direction);
	int getDirection();
	void addCell(Cell* cell);
	void removeCells();
	void hurt(Cell* attackedCell);
	bool checkLive();
	void kill();
	bool getLive();
	void print();
	vector<Cell*> getCells();
};

