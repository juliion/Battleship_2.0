#include "PlayersFactory.h"

Player* UserAndCompFactory::createPlayer1()
{
	return new User();
}

Player* UserAndWeakCompFactory::createPlayer2()
{
	return new WeakComputer();
}

Player* UserAndStrongCompFactory::createPlayer2()
{
	return new StrongComputer();
}

Player* StrongAndStrongCompFactory::createPlayer1()
{
	return new StrongComputer();
}

Player* StrongAndStrongCompFactory::createPlayer2()
{
	return new StrongComputer();
}

Player* WeakAndWeakCompFactory::createPlayer1()
{
	return new WeakComputer();
}

Player* WeakAndWeakCompFactory::createPlayer2()
{
	return new WeakComputer();
}

Player* WeakAndStrongCompFactory::createPlayer2()
{
	return new StrongComputer();
}

Player* StrongAndWeakCompFactory::createPlayer2()
{
	return new WeakComputer();
}