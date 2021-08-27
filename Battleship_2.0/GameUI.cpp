#include "GameUI.h"
using std::cin;

void UserVsCompGameUI::userPlacement()
{
	int placementType;
	GamePrinter* printer = GamePrinter::getInstance();
	do
	{
		printer->printTextEndl("��������, ��� �� ������ ���������� ���� �������:");
		printer->printTextEndl("1 - ��������");
		printer->printTextEndl("2 - �������");
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
		printer->printTextEndl("�������� ������� ���������: ");
		printer->printTextEndl("1 - �����");
		printer->printTextEndl("2 - ������");
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
		printer->printTextEndl("������� 1, ����� �������� ������������");
		printer->printTextEndl("��� ����� ������ �����, ����� ����������");
		cin >> change;
		system("cls");
	} while (change == 1);
	game->run(false, true, "��", "���������");
	int idWinner = game->getWinner();
	printer->printColorText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", magenta);
	printer->printTextEndl("");
	switch (idWinner)
	{
		case first: printer->printTextEndl("    �� ��������!!"); break;
		case second: printer->printTextEndl("    ��������� �������!!"); break;
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
		printer->printTextEndl("�������� ������� ��������� ��� ������� ����������: ");
		printer->printTextEndl("1 - �����");
		printer->printTextEndl("2 - ������");
		cin >> diffLevel1;
		system("cls");
	} while (diffLevel1 < 1 || diffLevel1 > 2);
	do
	{
		printer->printTextEndl("�������� ������� ��������� ��� ������� ����������: ");
		printer->printTextEndl("1 - �����");
		printer->printTextEndl("2 - ������");
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
	game->run(true, true, "��������� �1", "��������� �2");
	int idWinner = game->getWinner();
	printer->printColorText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", magenta);
	printer->printTextEndl("");
	switch (idWinner)
	{
	case first: printer->printTextEndl("    ������ ��������� �������"); break;
	case second: printer->printTextEndl("    ������ ��������� �������"); break;
	}
	printer->printColorText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", magenta);
	printer->printTextEndl("");
}