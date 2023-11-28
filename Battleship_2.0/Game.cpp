#include "Game.h"

void Game::changeShooter()
{
	firstIsShooting = !firstIsShooting;
}

void Game::checkShoot(Field* opponentField, Cell* cell)
{
	int x = cell->getX();
	int y = cell->getY();
	if (opponentField->isTypeCell(x, y, hit) || opponentField->isTypeCell(x, y, miss))
		return;
	if (opponentField->isTypeCell(x, y, partShip))
		opponentField->changeTypeCell(x, y, hit);
	else 
		opponentField->changeTypeCell(x, y, miss);
}

void Game::setPlayers(PlayersFactory* factory)
{
	player1 = factory->createPlayer1();
	player2 = factory->createPlayer2();
}

void Game::placePlayerShips(int id, int placementType)
{
	Player* player = nullptr;
	switch (id)
	{
		case first: player = player1; break;
		case second: player = player2; break;
	}
	player->placeShips(placementType);
}

Player* Game::getPlayer(int id)
{
	Player* player = nullptr;
	switch (id)
	{
		case first: player = player1; break;
		case second: player = player2; break;
	}
	return player;
}

void Game::run(bool mask1, bool mask2, string name1, string name2)
{
	do
	{
		GamePrinter* printer = GamePrinter::getInstance();
		Player* shooter = firstIsShooting ? player1 : player2;
		Player* opponent = firstIsShooting ? player2 : player1;
		Field* opField = opponent->getField();
		printer->printBattle(player1->getField(), player2->getField(), mask1, mask2, name1, name2);
		Cell* attackedCell = shooter->atack(opField);
		system("cls");
		if (attackedCell->getX() == -2 && attackedCell->getY() == -1)
		{
			stop = true;
			return;
		}
		checkShoot(opField, attackedCell);
		printer->printBattle(player1->getField(), player2->getField(), mask1, mask2, name1, name2);
		if (opField->isTypeCell(attackedCell->getX(), attackedCell->getY(), hit))
		{
			printer->printTextEndl("Hit!");
			Ship* attackedShip = opField->getShip(attackedCell);
			attackedShip->hurt(attackedCell);
			if (!attackedShip->checkLive())
			{
				attackedShip->kill();
				printer->printTextEndl("Killed!");
				opField->markAround(attackedShip, miss);
			}
		}
		else
		{
			printer->printTextEndl("Missed!");
			changeShooter();
		}
		Sleep(1000);
		system("cls");
	} while ((player1->hasLivingShips() && player2->hasLivingShips()) && !stop);
}

int Game::getWinner()
{
	if (player1->hasLivingShips() && !stop)
		return first;
	return second;
}