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

// Option menu :)
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
		case ENTER: return tt;
		}
		for (int i = 0; i < n; i++) mau[i] = Color;
		mau[tt] = 124;
	}
}
int IconChar() {
	int n = 6, tt = 1, cur = 0;
	gotoXY(70, 24);
	cout << ' ' << endl;
	gotoXY(70, 25);
	cout << char(88) << " vs " << char(79) << endl;
	gotoXY(70, 26);
	cout << char(48) << " vs " << char(49) << endl;
	gotoXY(70, 27);
	cout << char(224) << " vs " << char(225) << endl;
	gotoXY(70, 28);
	cout << char(227) << " vs " << char(235) << endl;
	gotoXY(70, 29);
	cout << char(156) << " vs " << char(157) << endl;
	int y = 24;
	int x = ((ConsoleWidth - 10) / 2) - 2;
	while (1) {
		cur = tt;
		gotoXY(x, y+tt);
		TextColor(15);
		cout << char(175)<< char(175) << endl;

		int z = _getch();
		Control select = cOption(z);
		switch (select) {
		case UP:
			if (tt == 1) tt = n - 1;
			else --tt;
			break;
		case DOWN:
			if (tt == n - 1) tt = 1;
			else ++tt;
			break;
		case ENTER:  return tt;
		}
		gotoXY(x, y + cur);
		TextColor(15);
		cout << "  " << endl;
	}
}
int IconColor() {
	int n = 7, tt = 1, cur = 0;
	gotoXY(70, 24);
	cout << ' ' << endl;
	gotoXY(70, 25);									// Red vs Green
	TextColor(12); cout << 'X';
	TextColor(15); cout << " vs ";
	TextColor(10); cout << 'O' << endl;
	gotoXY(70, 26);									// Green vs Red
	TextColor(10); cout << 'X';						
	TextColor(15); cout << " vs ";
	TextColor(12); cout << 'O' << endl;
	gotoXY(70, 27);									// Blue vs Yellow
	TextColor(9); cout << 'X';
	TextColor(15); cout << " vs ";
	TextColor(14); cout << 'O' << endl;
	gotoXY(70, 28);									// Yellow vs Blue
	TextColor(14); cout << 'X';
	TextColor(15); cout << " vs ";
	TextColor(9); cout << 'O' << endl;
	gotoXY(70, 29);									// Purple vs Cryan
	TextColor(13); cout << 'X';
	TextColor(15); cout << " vs ";
	TextColor(11); cout << 'O' << endl;
	gotoXY(70, 30);									// Cryan vs Purple
	TextColor(11); cout << 'X';
	TextColor(15); cout << " vs ";
	TextColor(13); cout << 'O' << endl;
	int y = 24;
	int x = ((ConsoleWidth - 10) / 2) - 2;
	while (1) {
		cur = tt;
		gotoXY(x, y + tt);
		TextColor(15);
		cout << char(175) << char(175) << endl;

		int z = _getch();
		Control select = cOption(z);
		switch (select) {
		case UP:
			if (tt == 1) tt = n - 1;
			else --tt;
			break;
		case DOWN:
			if (tt == n - 1) tt = 1;
			else ++tt;
			break;
		case ENTER:  return tt;
		}
		gotoXY(x, y + cur);
		TextColor(15);
		cout << "  " << endl;
	}
}
int IconOption() {
	int n = 3, tt = 0, mau[4];
	int lent[3] = { 1, 15, 11};
	string Option[3] = { "", "Icon Character","Icon Color"};
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
		case ENTER: return tt;
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
int Option_Game(int &row, int &column, char &charX, char &charO, int &intX, int &intO, int &coX, int &coO){
	ifstream game;						// Read parameters from file for the game
	game.open("Setting.txt");
	game >> row;
	game >> column;
	game >> intX;
	game >> intO;
	game >> coX;
	game >> coO;
	game.close();
	while (1) {
		Clear_Screen();
		int choose = Option_Choose();
		switch (choose) {
		case 1: {
			Clear_Screen();
			int icon = IconOption();
			if (icon == 1){
				Clear_Screen();
				int chara = IconChar();
				switch (chara) {
				case 1: 
					intX = 88; intO = 79;
					break;
				case 2:
					intX = 48; intO = 49;
					break;
				case 3:
					intX = 224; intO = 225;
					break;
				case 4:
					intX = 227; intO = 235;
					break;
				case 5:
					intX = 156; intO = 157;
					break;
				}
				charX = char(intX); charO = char(intO);
			}
			else {
				Clear_Screen();
				int color = IconColor();
				switch (color) {
				case 1:
					coX = 12; coO = 10;
					break;
				case 2:
					coX = 10; coO = 12;
					break;
				case 3:
					coX = 9; coO = 14;
					break;
				case 4:
					coX = 14; coO = 9;
					break;
				case 5:
					coX = 13; coO = 11;
					break;
				case 6:
					coX = 11; coO = 13;
					break;
				}
			}
			break;
		}
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
			break;
		}
		case 3:								// On/Off sound and music using PlaySound();
			break;
		case 4:								// Have not had any idea yet
			break;
		case 5: return 0;					// exit Options
		}
		ofstream Game;					// Write parameters to file in order to save them for later games
		Game.open("Setting.txt");
		Game << row << endl;
		Game << column << endl;
		Game << intX << endl;
		Game << intO << endl;
		Game << coX << endl;
		Game << coO << endl;
		Game.close();
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
