#include "PlaceShips.h"

bool PlaceShips::placeCheck(int x0, int y0, int endX, int endY)
{
	vector<vector<Cell*>> matrixCells = field->getMatrixCells();
	bool wrongPos = false;
	for (int i = x0; i <= endX; i++)
	{
		for (int j = y0; j <= endY; j++)
		{
			Cell* currCell = matrixCells[i][j];
			wrongPos = currCell->isType(partShip) || currCell->isType(nearShip);
			if (wrongPos)
				break;
		}
		if (wrongPos)
			break;
	}
	return !wrongPos;
}

void PlaceShips::addShipToMatrix(Ship* ship)
{
	for (Cell* cell : ship->getCells())
		field->changeTypeCell(cell->getX(), cell->getY(), partShip);
}

void PlaceShips::place()
{
	for (Ship* ship : field->getShips())
	{
		setCells(ship);
		addShipToMatrix(ship);
		field->markAround(ship, nearShip);
	}
}

void PlaceRandom::setCells(Ship* ship)
{
	int x0, y0, endX, endY, minX, minY, maxX, maxY, dx, dy, direction;
	int lengthShip = ship->getLength();
	do
	{
		dx = dy = 0;
		x0 = rand() % FN;
		y0 = rand() % FN;
		direction = rand() % 4 + 1;
		switch (direction)
		{
			case up: dy = -1; break;
			case down: dy = 1; break;
			case left: dx = -1; break;
			case right: dx = 1; break;
		}
		endX = x0 + dx * (lengthShip - 1);
		endY = y0 + dy * (lengthShip - 1);
		minX = x0 < endX ? x0 : endX;
		minY = y0 < endY ? y0 : endY;
		maxX = x0 > endX ? x0 : endX;
		maxY = y0 > endY ? y0 : endY;
	} while (!field->borderCheck(x0, y0) || !field->borderCheck(endX, endY) || !placeCheck(minX, minY, maxX, maxY));
	for (int i = minX; i <= maxX; i++)
		for (int j = minY; j <= maxY; j++)
			ship->addCell(new Cell(i, j, partShip));
	ship->setDirection(direction);
}

void PlaceManually::setCells(Ship* ship)
{
	int x0, y0, endX, endY, minX, minY, maxX, maxY, dx, dy, direction = undirected;
	char X;
	int lengthShip = ship->getLength();
	GamePrinter* printer = GamePrinter::getInstance();
	printer->printField(field, false);
	printer->printTextEndl("Разместите корабль длинной: " + std::to_string(lengthShip));
	do
	{
		do
		{
			printer->printText("Введите начальные координаты: ");
			cin >> y0 >> X;
			x0 = field->convertX(X);
			y0--;
		} while (!field->borderCheck(x0, y0));
		if (lengthShip != 1)
		{
			do
			{
				printer->printTextEndl("Ввыберете направление розмищения:");
				printer->printTextEndl("1 - вверх");
				printer->printTextEndl("2 - вниз");
				printer->printTextEndl("3 - влево");
				printer->printTextEndl("4 - вправо");
				cin >> direction;
			} while (direction < 1 || direction > 4);
		}
		dx = dy = 0;
		switch (direction)
		{
			case up: dy = -1; break;
			case down: dy = 1; break;
			case left: dx = -1; break;
			case right: dx = 1; break;
		}
		endX = x0 + dx * (lengthShip - 1);
		endY = y0 + dy * (lengthShip - 1);
		minX = x0 < endX ? x0 : endX;
		minY = y0 < endY ? y0 : endY;
		maxX = x0 > endX ? x0 : endX;
		maxY = y0 > endY ? y0 : endY;
		if (!field->borderCheck(x0, y0) || !field->borderCheck(endX, endY))
			printer->printTextEndl("Корабль выходит за границы! Выберете другое напрaвление!");
		else if (!placeCheck(minY, minX, maxY, maxX))
			printer->printTextEndl("Неправельное расположение!");
	} while (!field->borderCheck(x0, y0) || !field->borderCheck(endX, endY) || !placeCheck(minY, minX, maxY, maxX));
	system("cls");
	for (int i = minY; i <= maxY; i++)
		for (int j = minX; j <= maxX; j++)
			ship->addCell(new Cell(i, j, partShip));
	ship->setDirection(direction);
}
