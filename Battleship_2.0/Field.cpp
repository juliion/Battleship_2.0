#include "Field.h"

Field::Field()
{
	for (int i = 0; i < FN; i++)
	{
		vector<Cell*> col;
		for (int j = 0; j < FN; j++)
		{
			col.push_back(new Cell(i, j));
		}
			matrixCells.push_back(col);
	}

	for (int length = fourDeck; length >= singleDeck; length--)
		for (int count = 0; count < FN / 2 - length; count++)
			ships.push_back(new Ship(length));
}

bool Field::borderCheck(int x, int y)
{
	return y >= 0 && y < FN && x >= 0 && x < FN;
}

vector<Ship*> Field::getShips()
{
	return ships;
}

Ship* Field::getShip(Cell* partOfShip)
{
	for (Ship* ship : ships)
	{
		for (Cell* cell : ship->getCells())
			if (*cell == *partOfShip)
				return ship;
	}
	return nullptr;
}

int Field::countAliveShips()
{
	int count = 0;
	for (Ship* ship : ships)
	{
		if (ship->getLive())
			count++;
	}
	return count;
}

void Field::changeTypeCell(int x, int y, int newType)
{
	matrixCells[x][y]->setType(newType);
}

bool Field::isTypeCell(int x, int y, int type)
{
	return matrixCells[x][y]->isType(type);
}

vector<vector<Cell*>> Field::getMatrixCells()
{
	return matrixCells;
}

void Field::markAround(Cell* cell, int type)
{
	int x = cell->getX();
	int y = cell->getY();
	for (int i = 1; i >= -1; i--)
	{
		for (int j = 1; j >= -1; j--)
		{
			if (i == 0 && j == 0)
				continue;
			int nearX = x + i;
			int nearY = y + j;
			if (borderCheck(nearX, nearY))
			{
				Cell* nearCell = matrixCells[nearX][nearY];
				if (!nearCell->isType(partShip) && !nearCell->isType(hit))
					changeTypeCell(nearX, nearY, type);
			}
		}
	}
}

void Field::markAround(Ship* ship, int type)
{
	for (Cell* partOfShip : ship->getCells())
		markAround(partOfShip, type);
}

void Field::clear()
{
	for (int i = 0; i < FN; i++)
		for (int j = 0; j < FN; j++)
			changeTypeCell(i, j, empty);
	for (Ship* ship : ships)
		ship->removeCells();
}

int Field::convertX(char X)
{
	int x = -1;
	char letters[FN] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	for (int i = 0; i < FN; i++)
	{
		if (X == letters[i])
			x = i;
	}
	return x;
}