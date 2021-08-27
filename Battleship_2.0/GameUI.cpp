#include "GameUI.h"
using std::cin;

void UserVsCompGameUI::userPlacement()
{
	int placementType;
	GamePrinter* printer = GamePrinter::getInstance();
	do
	{
		printer->printTextEndl("Выберете, как вы хотите расставить свои корабли:");
		printer->printTextEndl("1 - рандомно");
		printer->printTextEndl("2 - вручную");
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
		printer->printTextEndl("Выберете уровень сложности: ");
		printer->printTextEndl("1 - легко");
		printer->printTextEndl("2 - сложно");
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
		printer->printTextEndl("Введите 1, чтобы поменять расположение");
		printer->printTextEndl("или любую другую цифру, чтобы продолжить");
		cin >> change;
		system("cls");
	} while (change == 1);
	game->run(false, true, "Вы", "Компьютер");
	int idWinner = game->getWinner();
	printer->printColorText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", magenta);
	printer->printTextEndl("");
	switch (idWinner)
	{
		case first: printer->printTextEndl("    Вы выиграли!!"); break;
		case second: printer->printTextEndl("    Компьютер победил!!"); break;
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
		printer->printTextEndl("Выберете уровень сложности для первого компьютера: ");
		printer->printTextEndl("1 - легко");
		printer->printTextEndl("2 - сложно");
		cin >> diffLevel1;
		system("cls");
	} while (diffLevel1 < 1 || diffLevel1 > 2);
	do
	{
		printer->printTextEndl("Выберете уровень сложности для второго компьютера: ");
		printer->printTextEndl("1 - легко");
		printer->printTextEndl("2 - сложно");
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
	game->run(true, true, "Компьютер №1", "Компьютер №2");
	int idWinner = game->getWinner();
	printer->printColorText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", magenta);
	printer->printTextEndl("");
	switch (idWinner)
	{
	case first: printer->printTextEndl("    Первый компьютер победил"); break;
	case second: printer->printTextEndl("    Второй компьютер победил"); break;
	}
	printer->printColorText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", magenta);
	printer->printTextEndl("");
}