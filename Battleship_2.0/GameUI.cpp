#include "GameUI.h"
using std::cin;

void UserVsCompGameUI::userPlacement()
{
	int placementType;
	GamePrinter* printer = GamePrinter::getInstance();
	do
	{
		printer->printTextEndl("Choose how you want to arrange your ships:");
		printer->printTextEndl("1 - randomly");
		printer->printTextEndl("2 - manually");
		cin >> placementType;
		system("cls");
	} while (placementType < 1 || placementType > 2);
	game->placePlayerShips(first, placementType);
	printer->printField(game->getPlayer(first)->getField(), false);
}

void UserVsCompGameUI::start()
{
	int diffLevel;
	GamePrinter* printer = GamePrinter::getInstance();
	do
	{
		printer->printTextEndl("Choose a level of difficulty: ");
		printer->printTextEndl("1 - easy");
		printer->printTextEndl("2 - difficult");
		cin >> diffLevel;
		system("cls");
	} while (diffLevel < 1 || diffLevel > 2);
	switch (diffLevel)
	{
		case easy: game->setPlayers(new UserAndWeakCompFactory()); break;
		case hard: game->setPlayers(new UserAndStrongCompFactory()); break;
	}
	game->placePlayerShips(second, random);
	int change;
	do
	{
		userPlacement();
		printer->printTextEndl("Enter 1 to change the location");
		printer->printTextEndl("or any other digit to continue");
		cin >> change;
		system("cls");
	} while (change == 1);
	game->run(false, true, "You", "Computer");
	int idWinner = game->getWinner();
	printer->printColorText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", magenta);
	printer->printTextEndl("");
	switch (idWinner)
	{
		case first: printer->printTextEndl("    You won"); break;
		case second: printer->printTextEndl("    Computer won"); break;
	}
	printer->printColorText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", magenta);
	printer->printTextEndl("");
}

void CompVsCompGameUI::start()
{
	int diffLevel1, diffLevel2;
	GamePrinter* printer = GamePrinter::getInstance();
	do
	{
		printer->printTextEndl("Choose a level of difficulty for 1 computer: ");
		printer->printTextEndl("1 - easy");
		printer->printTextEndl("2 - difficult");
		cin >> diffLevel1;
		system("cls");
	} while (diffLevel1 < 1 || diffLevel1 > 2);
	do
	{
		printer->printTextEndl("Choose a level of difficulty for 2 computer: ");
		printer->printTextEndl("1 - easy");
		printer->printTextEndl("2 - difficult");
		cin >> diffLevel2;
		system("cls");
	} while (diffLevel2 < 1 || diffLevel2 > 2);
	switch (diffLevel1)
	{
		case easy: 
		{
			if(diffLevel2 == easy)
				game->setPlayers(new WeakAndWeakCompFactory());
			else
				game->setPlayers(new StrongAndWeakCompFactory());
		}
		break;
		case hard:
		{
			if (diffLevel2 == easy)
				game->setPlayers(new WeakAndStrongCompFactory());
			else
				game->setPlayers(new StrongAndStrongCompFactory());
		}
		break;
	}
	game->placePlayerShips(first, random);
	game->placePlayerShips(second, random);
	game->run(true, true, "Computer 1", "Computer 2");
	int idWinner = game->getWinner();
	printer->printColorText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", magenta);
	printer->printTextEndl("");
	switch (idWinner)
	{
	case first: printer->printTextEndl("    Computer 1 won"); break;
	case second: printer->printTextEndl("    Computer 2 won"); break;
	}
	printer->printColorText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", magenta);
	printer->printTextEndl("");
}