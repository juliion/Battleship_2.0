#pragma once
#include "GameUI.h"

class CreatorGameUI
{
public: 
	CreatorGameUI() = default;
	virtual GameUI* create() = 0;
};

class CreatorUserVsCompGameUI : public CreatorGameUI
{
public:
	CreatorUserVsCompGameUI() : CreatorGameUI() { }
	virtual GameUI* create() override;
};

class CreatorCompVsCompGameUI : public CreatorGameUI
{
public:
	CreatorCompVsCompGameUI() : CreatorGameUI() { }
	virtual GameUI* create() override;
};

