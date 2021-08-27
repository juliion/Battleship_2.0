#pragma once
#include <map>
#include "Ship.h"
#include "Cell.h"
#define FN 10
using std::map;
using std::string;

enum LengthShips
{
	fourDeck = 4,
	threeDeck = 3,
	doubleDeck = 2,
	singleDeck = 1
};

class Field
{
	vector<vector<Cell*>> matrixCells;
	vector<Ship*> ships;
public:
	Field();
	bool borderCheck(int x, int y);
	vector<Ship*> getShips();
	Ship* getShip(Cell* partOfShip);
	int countAliveShips();
	void changeTypeCell(int x, int y, int newType);
	bool isTypeCell(int x, int y, int type);
	vector<vector<Cell*>> getMatrixCells();
	void markAround(Cell* cell, int type);
	void markAround(Ship* ship, int type);
	void clear();
	int convertX(char X);
};

