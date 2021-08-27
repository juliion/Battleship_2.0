#include "CreatorGameUI.h"
#include<ctime>

void startGame(CreatorGameUI* cr)
{
	GameUI* gameUI = cr->create();
	gameUI->start();
}

void mainMenu()
{
	int gameMode;
	GamePrinter* printer = GamePrinter::getInstance();
	do
	{
		printer->printTextEndl("�������� ����� ����:");
		printer->printTextEndl("1 - �������-���������");
		printer->printTextEndl("2 - ���������-���������");
		cin >> gameMode;
		system("cls");
	} while (gameMode < 1 || gameMode > 2);
	switch (gameMode)
	{
	case userVsComp: startGame(new CreatorUserVsCompGameUI()); break;
	case compVsComp: startGame(new CreatorCompVsCompGameUI()); break;
	}
}

int main()
{
	setlocale(0, "");
	srand(time(0));
	int cont;
	GamePrinter* printer = GamePrinter::getInstance();
	do
	{
		mainMenu();
		printer->printTextEndl("������� 1, ����� ������ ���� ������");
		cin >> cont;
	} while (cont == 1);
	return 0;
}