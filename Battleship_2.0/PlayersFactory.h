#pragma once
#include "Player.h"

class PlayersFactory
{
public:
	PlayersFactory() = default;
	virtual Player* createPlayer1() = 0;
	virtual Player* createPlayer2() = 0;
};

class UserAndCompFactory : public PlayersFactory
{
public:
	UserAndCompFactory() : PlayersFactory() { }
	virtual Player* createPlayer1() override;
	virtual Player* createPlayer2() = 0;
};

class UserAndWeakCompFactory : public UserAndCompFactory
{
public:
	UserAndWeakCompFactory() : UserAndCompFactory() { }
	virtual Player* createPlayer2() override;
};

class UserAndStrongCompFactory : public UserAndCompFactory
{
public:
	UserAndStrongCompFactory() : UserAndCompFactory() { }
	virtual Player* createPlayer2() override;
};

class StrongAndStrongCompFactory : public PlayersFactory
{
public:
	StrongAndStrongCompFactory() : PlayersFactory() { }
	virtual Player* createPlayer1() override;
	virtual Player* createPlayer2() override;
};

class WeakAndWeakCompFactory : public PlayersFactory
{
public:
	WeakAndWeakCompFactory() : PlayersFactory() { }
	virtual Player* createPlayer1() override;
	virtual Player* createPlayer2() override;
};

class WeakAndStrongCompFactory : public WeakAndWeakCompFactory
{
public:
	WeakAndStrongCompFactory() : WeakAndWeakCompFactory() { }
	virtual Player* createPlayer2() override;
};

class StrongAndWeakCompFactory : public StrongAndStrongCompFactory
{
public:
	StrongAndWeakCompFactory() : StrongAndStrongCompFactory() { }
	virtual Player* createPlayer2() override;
};