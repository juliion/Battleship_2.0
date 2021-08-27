#pragma once
#include "Field.h"
#include "PlaceShips.h"

enum PlacementType
{
	random = 1,
	manually
};

class Player
{
protected:
	Field* field;
public:
	Player();
	void placeShips(int placementType);
	Field* getField();
	bool hasLivingShips();
	virtual Cell* atack(Field* opponentField) = 0;
};

class User : public Player
{
public:
	User() : Player() { }
	virtual Cell* atack(Field* opponentField) override;
};

class Computer : public Player
{
protected:
	bool checkHit(Field* opponentField, int x, int y);
public:
	Computer() : Player() { }
};

class WeakComputer : public Computer
{
public:
	WeakComputer() : Computer() { }
	virtual Cell* atack(Field* opponentField) override;
};
 
class StrongComputer : public Computer
{
	vector<Cell*> fixedHits;
	Cell* prevHit;
	bool wasHit;
	Cell* getPossibleCell(Field* opponentField);
public:
	StrongComputer();
	virtual Cell* atack(Field* opponentField) override;
};


