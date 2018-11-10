#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "console.h"
#include <string>
#include "StartScreen.h"


using namespace std;

#define ConsoleWidth  134
#define ConsoleHeight 62
#define Color 15

string Option[7] = {"", "Icons","Game Rules","Board size","Sound & Music", "Background","Back" };
enum Status { UP, DOWN, ENTER };
Status key0(int z) {
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


int Option_Game() {
	int n = 7;
	int tt = 0;
	int *mau = new int[n];
	for (int i = 0; i > n; i++) mau[i] = Color;
	while (1) {
		int x;
		int y = 22;
		int lent[7] = {1, 6, 11, 11, 14, 11, 5 };
		for (int i = 0; i < n; i++) {
			x = ((ConsoleWidth - lent[i]) / 2) - 2;
			gotoXY(x, y);
			TextColor(mau[i]);
			cout << Option[i] << endl;
			y++;
		}
		int z = _getch();
		Status TrangThai = key0(z);
		switch (TrangThai)
		{
		case UP: {
			if (tt == 1 || tt == 0) tt = n - 1;
			else --tt;
			break;
		}
		case DOWN: {
			if (tt == n - 1) tt = 0;
			else ++tt;
			break;
		}
		case ENTER:  if (tt == 3)
			exit(0);
					 else return tt;
		}
		for (int i = 0; i < n; i++) mau[i] = Color;
		mau[tt] = 124;
	}
}

void Board(int n) {

	// first line
	cout << (char)218;
	int i, j;
	for (i = 1; i < n; i++)
		cout << (char)196 << (char)196 << (char)196 << (char)194;
	cout << (char)196 << (char)196 << (char)196;
	cout << (char)191 << endl;

	// middle lines
	for (i = 1; i < n; i++) {
		for (j = 1; j < n + 2; j++)
			cout << (char)179 << "   ";
		cout << endl << (char)195;
		for (j = 1; j < n; j++)
			cout << (char)196 << (char)196 << (char)196 << (char)197;
		cout << (char)196 << (char)196 << (char)196;
		cout << (char)180 << endl;
	}

	// last line
	for (j = 1; j < n + 2; j++)
		cout << (char)179 << "   ";
	cout << endl << (char)192;
	for (i = 1; i < n; i++)
		cout << (char)196 << (char)196 << (char)196 << (char)193;
	cout << (char)196 << (char)196 << (char)196;
	cout << (char)217;
}



