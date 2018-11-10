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

string Quit[2] = { "YES","NO" };
enum Status { UP, DOWN, ENTER };
Status key1(int z) {
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

int Quit_Game() {
	string bye = "Do you want to quit?"; //length=21
	gotoXY((ConsoleWidth - 21) / 2 - 2, 22);
	TextColor(15);
	cout << bye << endl;
	int n = 2;
	int tt = 0;
	int *mau = new int[n];
	for (int i = 0; i > n; i++) mau[i] = Color;
	while (1) {
		int x;
		int y = 23;
		for (int i = 0; i < n; i++) {
			int lent[2] = { 4, 3 };
			x = ((ConsoleWidth - lent[i]) / 2) - 2;
			gotoXY(x, y);
			TextColor(mau[i]);
			cout << Quit[i] << endl;
			y++;
		}
		int z = _getch();
		Status TrangThai = key1(z);
		switch (TrangThai)
		{
		case UP: {
			if (tt == 0) tt = n - 1;
			else --tt;
			break;
		}
		case DOWN: {
			if (tt == n - 1) tt = 0;
			else ++tt;
			break;
		}
		case ENTER: return tt;
		}
		for (int i = 0; i < n; i++) mau[i] = Color;
		mau[tt] = 124;
	}
}
