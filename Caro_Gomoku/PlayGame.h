#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "console.h"
#include "Animation.h"

using namespace std;

#define ConsoleWidth  144
#define ConsoleHeight 62
#define Color 15

int Load_Game(char a[][42], int &row, int &column, char &charX, char &charO, int &coX, int &coO, int score[][42], int Enemyscore[][42],
	int &PvP, int &PvC, int &Easy, int &Medium, int &Hard, int &wEasy, int &wMedium, int &wHard);					// Load game
int Save_Game(char a[][42], int &row, int &column, char &charX, char &charO, int &coX, int &coO, char mode);		// Save game

// Game play
int Start_Game(char a[][42], int &row, int &column, char &charX, char &charO, int &coX, int &coO,
				int &PvP, int &PvC, int &Easy, int &wEasy, int &Medium, int &wMedium, int &Hard, int &wHard);
int Select_Mode();
int Player_turn(char a[][42], int &row, int &column, int &x, int &y, int n, int m, int &step, int mode, int &PlayerX, int &PlayerY, 
					int &PcX, int &PcY, char &charX, char &charO, int &coX, int &coO, int score[][42], int Enemyscore[][42], char Mode);
int PP_Mode(char a[][42], int &row, int &column, int load, char &charX, char &charO, int &coX, int &coO, int &PvP);
int PC_Mode(char a[][42], int &row, int &column, char &charX, char &charO, int &coX, int &coO, int &PvC,
	int &Easy, int &wEasy, int &Medium, int &wMedium, int &Hard, int &wHard);
void Score_of_Cell(char a[][42], int &row, int &column, char &charX, char &charO, int score[][42], int Enemyscore[][42]);
void Score_of_Enemy_Cell(char a[][42], int &row, int &column, char &charX, char &charO, int score[][42], int Enemyscore[][42]);
int test_Move(char a[][42], int x, int y, int &row, int &column, int score[][42], int Enemyscore[][42], char &charX, char &charO);
int test_Move_High(char a[][42], int x, int y, int &row, int &column, int score[][42], int Enemyscore[][42], char &charX, char &charO);
int Easy_mode(char a[][42], int &row, int &column, int load, int score[][42], int Enemyscore[][42], 
				char &charX, char &charO, int &coX, int &coO, int &PvC, int &Easy, int &wEasy);
int Medium_mode(char a[][42], int &row, int &column, int load, int score[][42], int Enemyscore[][42], 
				char &charX, char &charO, int &coX, int &coO, int &PvC, int &Medium, int &wMedium);
int Hard_mode(char a[][42], int &row, int &column, int load, int score[][42], int Enemyscore[][42], 
				char &charX, char &charO, int &coX, int &coO, int &PvC, int &Hard, int &wHard);
int Check_Win(char a[][42], int x, int y, int &row, int &column, char &charX, char &charO);
void Undo(char a[][42], int &row, int &column, int n, int &step, int x, int y, int curX, int curY, 
	char &charX, char &charO, int &coX, int &coO, int score[][42], int Enemyscore[][42]);			// Undo move
