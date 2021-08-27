#include "Ship.h"

int Ship::getLength()
{
	return length;
}

void Ship::setDirection(int direction)
{
	this->direction = direction;
}

int Ship::getDirection()
{
	return direction;
}

void Ship::addCell(Cell* cell)
{
	partsOfShip.push_back(cell);
}

void Ship::removeCells()
{
	partsOfShip.clear();
}

void Ship::hurt(Cell* attackedCell)
{
	for (Cell* cell : partsOfShip)
	{
		if (*cell == *attackedCell)
			cell->setType(hit);
	}
}

bool Ship::checkLive()
{
	for (Cell* cell : partsOfShip)
	{
		if (!cell->isType(hit))
			return true;
	}
	return false;
}

void Ship::print()
{
	std::cout << "Length: " << length << std::endl;
	std::cout << "Live: " << live << std::endl;
}

bool Ship::getLive()
{
	return live;
}

void Ship::kill()
{
	live = false;
}

vector<Cell*> Ship::getCells()
{
	return partsOfShip;
}
