#pragma once
#include "PlayersFactory.h"

enum PlayerId
{
	first = 1,
	second
};

class Game
{
	Player* player1;
	Player* player2;
	bool stop;
	bool firstIsShooting;
	void checkShoot(Field* opponentField, Cell* cell);
	void changeShooter();
public:
	Game() : player1{ nullptr }, player2{ nullptr }, firstIsShooting{ true }, stop{ false } { }
	void setPlayers(PlayersFactory* factory);
	void placePlayerShips(int id, int placementType);
	Player* getPlayer(int id);
	void run(bool mask1, bool mask2, string name1, string name2);
	int getWinner();
};
