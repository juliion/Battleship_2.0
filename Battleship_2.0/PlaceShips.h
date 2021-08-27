#pragma once
#include "Field.h"
#include "GamePrinter.h"
using std::cin;

class PlaceShips
{
protected:
	Field* field;
	bool placeCheck(int x0, int y0, int endX, int endY);
	void addShipToMatrix(Ship* ship);
	virtual void setCells(Ship* ship) = 0;
public:
	PlaceShips(Field* f) : field{ f } { }
	void place();
};

class PlaceRandom : public PlaceShips
{
	virtual void setCells(Ship* ship) override;
public:
	PlaceRandom(Field* f): PlaceShips(f) { }
};

class PlaceManually : public PlaceShips
{
	virtual void setCells(Ship* ship) override;
public:
	PlaceManually(Field* f) : PlaceShips(f) { }
};


