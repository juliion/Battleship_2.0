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
		printer->printTextEndl("Select a game mode:");
		printer->printTextEndl("1 - human-computer");
		printer->printTextEndl("2 - computer-computer");
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
		printer->printTextEndl("Enter 1 to open menu");
		cin >> cont;
	} while (cont == 1);
	return 0;
}