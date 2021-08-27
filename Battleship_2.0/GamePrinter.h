#pragma once
#include "Field.h"
#include "Windows.h"
#include <string>
using std::cout;
using std::endl;
using std::string;

enum ConsoleColor
{
    black = 0,
    blue = 1,
    green = 2,
    cyan = 3,
    red = 4,
    magenta = 5,
    brown = 6,
    lightGray = 7,
    darkGray = 8,
    lightBlue = 9,
    lightGreen = 10,
    lightCyan = 11,
    lightRed = 12,
    lightMagenta = 13,
    yellow = 14,
    white = 15
};

class GamePrinter
{
    static GamePrinter* instance;
    GamePrinter() = default;
public:
    GamePrinter(GamePrinter& other) = delete;
    void operator=(const GamePrinter&) = delete;
    static GamePrinter* getInstance();
	void printTextEndl(string text);
	void printText(string text);
	void printColorText(string text, int color);
	void printField(Field* field, bool mask);
    void printBattle(Field* f1, Field* f2, bool mask1, bool mask2, string name1, string name2);
};

