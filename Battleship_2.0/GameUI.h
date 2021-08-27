#pragma once
#include "Game.h"

enum gameMods
{
	userVsComp = 1,
	compVsComp
};

enum DifficultyLevels
{
	easy = 1,
	hard
};

class GameUI
{
protected:
	Game* game;
public:
	GameUI(Game* g) : game{ g } { }
	virtual void start() = 0;
};

class UserVsCompGameUI : public GameUI
{
	void userPlacement();
public:
	UserVsCompGameUI(Game* g) : GameUI(g) { }
	virtual void start() override;
};

class CompVsCompGameUI : public GameUI
{
public:
	CompVsCompGameUI(Game* g) : GameUI(g) { }
	virtual void start() override;
};
