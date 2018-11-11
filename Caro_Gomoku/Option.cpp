#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "console.h"
#include "StartScreen.h"
#include "PlayGame.h"

using namespace std;

#define ConsoleWidth  144
#define ConsoleHeight 62
#define Color 15

enum Control { UP, DOWN, ENTER};
Control cOption(int z) {
	if (z == 224) {
		char c;
		c = _getch();
		if (c == 72) return UP;
		if (c == 80) return DOWN;
	}
	else if (z == 87 || z == 119) return UP;        // W & w
	else if (z == 83 || z == 115) return DOWN;		// S & s
	else if (z == 13) return ENTER;
}

int Option_Choose() {
	int n = 6, tt = 0, mau[6];
	int lent[6] = { 1, 6, 11, 14, 11, 5 };
	string Option[7] = { "", "Icons","Board size","Sound & Music", "Background","Back" };
	for (int i = 0; i < n; i++) mau[i] = Color;
	while (1) {
		int y = 24;
		for (int i = 0; i < n; i++) {
			int x = ((ConsoleWidth - lent[i]) / 2) - 2;
			gotoXY(x, y);
			TextColor(mau[i]);
			cout << Option[i] << endl;
			y++;
		}
		int z = _getch();
		Control select = cOption(z);
		switch (select) {
		case UP:
			if (tt == 1 || tt == 0) tt = n - 1;
			else --tt;
			break;
		case DOWN:
			if (tt == n - 1) tt = 1;
			else ++tt;
			break;
		case ENTER:  if (tt == 3) exit(0);
					 else return tt;
		}
		for (int i = 0; i < n; i++) mau[i] = Color;
		mau[tt] = 124;
	}
}
int boardSize() {
	int n = 7, tt = 0, mau[7];
	for (int i = 0; i < n; i++) mau[i] = Color;
	string menuList[7] = { "", "10 x 10","13 x 13", "16 x 16", "19 x 19", "21 x 21", "Back" };
	int lent[7] = { 1, 8, 8, 8, 8, 8, 5 };
	while (1) {
		int x, y = 24;
		for (int i = 0; i < n; i++) {
			x = ((ConsoleWidth - lent[i]) / 2) - 2;
			gotoXY(x, y);
			TextColor(mau[i]);
			cout << menuList[i] << endl;
			y++;
		}
		int z = _getch();
		Control Moving = cOption(z);
		switch (Moving) {
		case UP:
			if (tt == 1 || tt == 0) tt = n - 1;
			else --tt;
			break;
		case DOWN:
			if (tt == n - 1) tt = 1;
			else ++tt;
			break;
		case ENTER:	return tt;
		}
		for (int i = 0; i < n; i++) mau[i] = Color;
		mau[tt] = 124;
	}
}
int Option_Game(int &row, int &column, char & charX, char &charO) {
	ifstream game;						// Read parameters from file for the game
	game.open("Setting.txt");
	game >> row;
	game >> column;
	game >> charX;
	game >> charO;
	game.close();
	while (1) {
		Clear_Screen();
		int choose = Option_Choose();
		switch (choose) {
		case 1:
			/*
			May change some icons of X and O also their color but not too much
			May set each pair XO with available color
			Do same as others options and menu
			*/
			break;
		case 2: {
			Clear_Screen();
			int select = boardSize();
			switch (select) {
			case 1:
				row = 10; column = 10;
				break;
			case 2:
				row = 13; column = 13;
				break;
			case 3:
				row = 16; column = 16;
				break;
			case 4:
				row = 19; column = 19;
				break;
			case 5:
				row = 21; column = 21;
				break;
			case 6: return 0;
			}
			ofstream Game;					// Write parameters to file in order to save them for later games
			Game.open("Setting.txt");
			Game << row << endl;
			Game << column << endl;
			Game << charX << endl;
			Game << charO << endl;
			Game.close();
			break;
		}
		case 3:								// On/Off sound and music using PlaySound();
			break;
		case 4:								// Have not had any idea yet
			break;
		case 5: return 0;					// exit Options
		}
	}
}
void Board(int &row, int &column) {
	TextColor(7);
	// first row
	cout << (char)218;
	int i, j;
	for (i = 1; i < column; i++)
		cout << (char)196 << (char)196 << (char)196 << (char)194;
	cout << (char)196 << (char)196 << (char)196;
	cout << (char)191 << endl;

	// middle rows
	for (i = 1; i < row; i++) {
		for (j = 1; j < column + 2; j++)
			cout << (char)179 << "   ";
		cout << endl << (char)195;
		for (j = 1; j < row; j++)
			cout << (char)196 << (char)196 << (char)196 << (char)197;
		cout << (char)196 << (char)196 << (char)196;
		cout << (char)180 << endl;
	}

	// last row
	for (j = 1; j < column + 2; j++)
		cout << (char)179 << "   ";
	cout << endl << (char)192;
	for (i = 1; i < column; i++)
		cout << (char)196 << (char)196 << (char)196 << (char)193;
	cout << (char)196 << (char)196 << (char)196;
	cout << (char)217;
}
