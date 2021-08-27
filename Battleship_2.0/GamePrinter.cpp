#include "GamePrinter.h"

GamePrinter* GamePrinter::instance = nullptr;

void GamePrinter::printTextEndl(string text)
{
	cout << text << endl;
}

GamePrinter* GamePrinter::getInstance()
{
	if (instance == nullptr) {
		instance = new GamePrinter();
	}
	return instance;
}

void GamePrinter::printText(string text)
{
	cout << text;
}

void GamePrinter::printColorText(string text, int color)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	cout << text;
	SetConsoleTextAttribute(hConsole, white);
}

void GamePrinter::printField(Field* field, bool mask)
{
	vector<vector<Cell*>> matrixCells = field->getMatrixCells();
	printTextEndl("     A  B  C  D  E  F  G  H  I  J");
	printTextEndl("   --------------------------------");
	for (int i = 0; i < FN; i++)
	{
		if (i >= 9)
			printText(std::to_string(i + 1) + "| ");
		else
			printText(std::to_string(i + 1) + " | ");
		for (int j = 0; j < FN; j++)
		{
			Cell* currCell = matrixCells[i][j];
			switch (currCell->getType())
			{
				case hit: printColorText(" x ", red); break;
				case miss: printColorText(" o ", green); break;
				case partShip:
				{
					if (!mask)
					{
						printColorText(" # ", cyan);
						break;
					}
				}
				default: printColorText(" . ", blue); break;
			}
		}
		if (i >= 9)
			printTextEndl(" |");
		else
			printTextEndl(" | ");
	}
	printTextEndl("   --------------------------------");
}

void GamePrinter::printBattle(Field* f1, Field* f2, bool mask1, bool mask2, string name1, string name2)
{
	printColorText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", cyan);
	printTextEndl("");
	printTextEndl("  Поле №1: " + name1 + "(осталось кораблей: " + std::to_string(f1->countAliveShips()) + ")     Поле №2: " + name2 + "(осталось кораблей: " + std::to_string(f2->countAliveShips()) + ")");
	printColorText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", cyan);
	printTextEndl("");
	printTextEndl("");
	printTextEndl("  Поле №1");
	printColorText("-----------", cyan);
	printTextEndl("");
	printField(f1, mask1);
	printTextEndl("");
	printTextEndl("");
	printTextEndl("  Поле №2");
	printColorText("-----------", cyan);
	printTextEndl("");
	printField(f2, mask2);
}