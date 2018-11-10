#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "console.h"
#include <string>


using namespace std;

#define ConsoleWidth  134
#define ConsoleHeight 62
#define Color 15

enum Status { UP, DOWN, ENTER };
string Statistics;

Status key3(int z) {
	if (z == 224) {
		char c;
		c = _getch();
		if (c == 72) return UP;
		if (c == 80) return DOWN;
	}
	else if (z == 87 || z == 119) return UP;         // W & w
	else if (z == 83 || z == 115) return DOWN;		// S & s
	else if (z == 13) return ENTER;
}

int Statics_Game() {
	return 0;
}