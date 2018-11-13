// 18125050
// Nguyen Phan Nhat Hoang
// Individual Project: Caro / Gomoku

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <mmsystem.h>
#include "console.h"
#include "Setting.h"
#include "Animation.h"
#include "StartScreen.h"
#include "PlayGame.h"
#include "Option.h"

using namespace std;

#define ConsoleWidth  144
#define ConsoleHeight 62
#define Color 15

enum Control { UP, DOWN, ENTER};
Control move(int z) {
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

int About_Game();						// About us
int Statics_Game(int &PvP, int &PvC, int &Easy, int &wEasy, int &Medium, int &wMedium, int &Hard, int &wHard);		// Statistic								// Statistic

int Quit_Game();						// Exit game

int main() {
	int row, column;					// row & column of board game
	int intX, intO, coX, coO;
	char charX, charO;					// The display of character user play
	char a[84][42];						// Status of Playing game
	int PvP, PvC, Easy, wEasy, Medium, wMedium, Hard, wHard;
	int score[84][42], Enemyscore[84][42];

	SetConsoleOutputCP(437);			// set to display extended ascii characters
	resizeConsole(1280, 730);			// size of console screen
	Nocursortype();						// hide the mousepoint

	for (int i = 0; i < 84; i++)
		for (int j = 0; j < 42; j++)
			a[i][j] = ' ';				// initialize the value of a-array

	ifstream game;						// input parameters of game before playing
	game.open("Setting.txt");
	game >> row;
	game >> column;
	game >> intX;  
	game >> intO;
	charX = char(intX);					// Icon for player X
	charO = char(intO);					// Icon for player O
	game >> coX;						// color of X
	game >> coO;						// color of O
	game.close();
	Execute_1();						// Splash Screen
	clrscr();
	Start_Screen();
	while (1) {
		clrscr();
		Screen();
		int select = Menu();
		switch (select) {
		case 1: {
			ifstream statistics;
			statistics.open("Statistic.txt");
			statistics >> PvP;
			statistics >> PvC;
			statistics >> Easy;
			statistics >> wEasy;
			statistics >> Medium;
			statistics >> wMedium;
			statistics >> Hard;
			statistics >> wHard;
			statistics.close();
			Start_Game(a, row, column, charX, charO, coX, coO, PvP, PvC, Easy, wEasy, Medium, wMedium, Hard, wHard);
			ofstream statistic;
			statistic.open("Statistic.txt");
			statistic << PvP << endl;
			statistic << PvC << endl;
			statistic << Easy << endl;
			statistic << wEasy << endl;
			statistic << Medium << endl;
			statistic << wMedium << endl;
			statistic << Hard << endl;
			statistic << wHard << endl;
			statistic.close();
			break;
		}
		case 2:
			clrscr();
			system("Color 7");
			Load_Game(a, row, column, charX, charO, coX, coO, score, Enemyscore, PvP, PvC, Easy, Medium, Hard, wEasy, wMedium, wHard);
			break;
		case 3:
			Option_Game(row, column, charX, charO, intX, intO, coX, coO);
			break;
		case 4:
			clrscr();
			system("Color 7");
			Statics_Game(PvP, PvC, Easy, wEasy, Medium, wMedium, Hard, wHard);
			break;
		case 5:
			clrscr();
			system("Color 7");
			About_Game();
			break;
		case 6:
			Clear_Screen();
			int choose = Quit_Game();
			if (choose == 0)  exit(0);
			else 	break;
		}
	}
	return 0;
}

int About_Game() {
	ifstream textfile("About.txt");
	string s1;						//store a line of file
	stringstream ss;
	ss << textfile.rdbuf();			//pass data in buffer into stream ss
	s1 = ss.str();					//assign to s1 string
	cout << s1.data() << endl;
	gotoXY(0, 0);
	cout << "    " << endl;
	while (1) {
		int z = _getch();
		Control TrangThai = move(z);
		if (TrangThai == ENTER) return 0;
	}
}
int Statics_Game(int &PvP, int &PvC, int &Easy, int &wEasy, int &Medium, int &wMedium, int &Hard, int &wHard) {
	ifstream statistic;						// Read the input from file to get total number of games that played
	statistic.open("Statistic.txt");
	statistic >> PvP;
	statistic >> PvC;
	statistic >> Easy;
	statistic >> wEasy;
	statistic >> Medium;
	statistic >> wMedium;
	statistic >> Hard;
	statistic >> wHard;
	statistic.close();
	clrscr();
	system("Color 7");
	int x = 4, y = 2;
	gotoXY(x, y);
	cout << "Game played: " << endl;
	x += 3;
	gotoXY(x, y + 1);
	cout << "    Player-Player: " << PvP << endl;
	gotoXY(x, y + 2);
	cout << "     Player-PC: " << PvC << endl;
	gotoXY(x, y + 3);
	cout << "        Easy Mode: " << Easy << "     Win: " << wEasy << endl;
	gotoXY(x, y + 4);
	cout << "      Medium Mode: " << Medium << "     Win: " << wMedium << endl;
	gotoXY(x, y + 5);
	cout << "        Hard Mode: " << Hard << "     Win: " << wHard << endl;
	while (1) {						// Enter to exit Statistic 
		int z = _getch();
		Control TrangThai = move(z);
		if (TrangThai == ENTER) return 0;
	}
}

int Quit_Game() {
	string bye = "Do you want to quit?"; //length=21
	gotoXY((ConsoleWidth - 21) / 2 - 2, 24);
	TextColor(15);
	cout << bye << endl;
	int tt = 0;
	int mau[3];
	for (int i = 0; i < 3; i++) mau[i] = Color;
	string Quit[3] = { "", "YES","NO"};
	int lent[3] = { 1, 4, 3 };
	while (1) {
		int y = 25;
		for (int i = 1; i < 3; i++) {
			int x = ((ConsoleWidth - lent[i]) / 2) - 2;
			gotoXY(x, y);
			TextColor(mau[i]);
			cout << Quit[i] << endl;
			y++;
		}
		int z = _getch();
		Control select = move(z);
		switch (select) {
		case UP:
			if (tt == 1) tt = 2;
			else --tt;
			break;
		case DOWN:
			if (tt == 2) tt = 1;
			else ++tt;
			break;
		case ENTER:
			if (tt == 1) return 0;
			return tt;
		}
		for (int i = 0; i < 3; i++) mau[i] = Color;
		mau[tt] = 124;
	}
}
