#include "CreatorGameUI.h"

GameUI* CreatorUserVsCompGameUI::create()
{
	return new UserVsCompGameUI(new Game());
}

GameUI* CreatorCompVsCompGameUI::create()
{
	return new CompVsCompGameUI(new Game());
}