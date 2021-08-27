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
		printer->printTextEndl("Выберете режим игры:");
		printer->printTextEndl("1 - человек-компьютер");
		printer->printTextEndl("2 - компьютер-компьютер");
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
		printer->printTextEndl("Введите 1, чтобы начать игру заново");
		cin >> cont;
	} while (cont == 1);
	return 0;
}