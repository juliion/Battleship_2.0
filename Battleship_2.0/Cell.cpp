#include "Cell.h"

int Cell::getX()
{
	return x;
}

int Cell::getY()
{
	return y;
}

void Cell::setType(int type)
{
	this->type = type;
}

int Cell::getType()
{
	return type;
}

bool Cell::isType(int type)
{
	return this->type == type;
}

bool operator==(Cell& c1, Cell& c2)
{
	return (c1.x == c2.x && c1.y == c2.y);
}