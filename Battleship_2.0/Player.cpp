#include "Player.h"

Player::Player()
{
	field = new Field();
}

void Player::placeShips(int placementType)
{
	PlaceShips* pl = nullptr;
	field->clear();
	switch (placementType)
	{
		case random: pl = new PlaceRandom(field); break;
		case manually: pl = new PlaceManually(field); break;
	}
	pl->place();
}

Field* Player::getField()
{
	return field;
}

bool Player::hasLivingShips()
{
	for (Ship* ship : field->getShips())
	{
		if (ship->getLive())
			return true;
	}
	return false;
}

Cell* User::atack(Field* opponentField)
{
	GamePrinter* printer = GamePrinter::getInstance();
	int x, y;
	char X;
	do
	{
		printer->printColorText("                               |> Сдаться - введите -1s", white);
		printer->printTextEndl("");
		printer->printColorText("                               | ", white);
		printer->printTextEndl("");
		printer->printTextEndl("Стреляйте или сдавайтесь!");
		cin >> y >> X;
		x = opponentField->convertX(X);
		y--;
		if (y == -2 && x == -1)
			break;
	} while (!opponentField->borderCheck(x, y));
	return new Cell(y, x);
}

bool Computer::checkHit(Field* opponentField, int x, int y)
{
	return (!opponentField->isTypeCell(x, y, hit) && !opponentField->isTypeCell(x, y, miss));
}

Cell* WeakComputer::atack(Field* opponentField)
{
	int x, y;
	do
	{
		x = rand() % FN;
		y = rand() % FN;
	} while (!checkHit(opponentField, x, y));
	return  new Cell(x, y);
}

StrongComputer::StrongComputer() : Computer()
{
	prevHit = nullptr;
	wasHit = false;
	int y0 = 3;
	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < FN; x++)
		{
			if (i == 0 && x % 4 == 0 ||
				i == 1 && (x == 2 || x == 6))
				y0 = 3;
			if (i == 1 && x == 0)
				y0 = 1;
			for (int y = y0; y < FN; y += 4)
				fixedHits.push_back(new Cell(x, y));
			y0--;
		}
	}
}

Cell* StrongComputer::getPossibleCell(Field* opponentField)
{
	int x, y, direction, dx, dy;
	Ship* attackedShip = opponentField->getShip(prevHit);
	direction = attackedShip->getDirection();
	vector<Cell*> partsOfShip = attackedShip->getCells();
	do
	{
		dx = dy = 0;
		Cell* endCell = nullptr;
		switch (direction)
		{
			case up: 
			{
				dy = -1;
				endCell = partsOfShip[0];
			}
			break;
			case down: 
			{
				dy = 1;
				endCell = partsOfShip[partsOfShip.size() - 1];
			}
			break;
			case left:
			{
				dx = -1;
				endCell = partsOfShip[0];
			}
			break;
			case right: 
			{
				dx = 1;
				endCell = partsOfShip[partsOfShip.size() - 1];
			}
			break;
		}
		bool changeDir = opponentField->isTypeCell(endCell->getX(), endCell->getY(), hit);
		if (changeDir)
		{
			dx *= -1;
			dy *= -1;
		}
		x = prevHit->getX() + dx;
		y = prevHit->getY() + dy;
	} while (!opponentField->borderCheck(x, y) && !checkHit(opponentField, x, y));
	return new Cell(x, y);
}

Cell* StrongComputer::atack(Field* opponentField)
{
	int x, y;
	if (wasHit && opponentField->getShip(prevHit)->checkLive())
	{
		Cell* cell = getPossibleCell(opponentField);
		x = cell->getX();
		y = cell->getY();
	}
	else
	{
		do
		{
			if (!fixedHits.empty())
			{
				int ind = rand() % fixedHits.size();
				Cell* stCell = fixedHits[ind];
				x = stCell->getX();
				y = stCell->getY();
				fixedHits.erase(fixedHits.begin() + ind);
			}
			else
			{
				x = rand() % FN;
				y = rand() % FN;
			}
		} while (!checkHit(opponentField, x, y));
	}
	wasHit = opponentField->isTypeCell(x, y, partShip) || (prevHit != nullptr && opponentField->getShip(prevHit)->checkLive());
	if (wasHit)
		prevHit = new Cell(x, y);
	return new Cell(x, y);
}