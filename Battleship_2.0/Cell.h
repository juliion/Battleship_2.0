#pragma once

enum CellType
{
	empty, // o
	partShip, // #
	nearShip,
	hit,
	miss
};
class Cell
{
	int x;
	int y;
	int type;
public:
	Cell(int x_, int y_) : x{ x_ }, y{ y_ }, type{ empty } {}
	Cell(int x_, int y_, int t) : x{ x_ }, y{ y_ }, type{ t } {}
	int getX();
	int getY();
	void setType(int type);
	int getType();
	bool isType(int type);
	friend bool operator==(Cell& c1, Cell& c2);
}; 

