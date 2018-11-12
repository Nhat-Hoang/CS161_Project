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

//Option game
int Option_Game(int &row, int &column, char &charX, char &charO, int &intX, int &intO, int &coX, int &coO);
void Board(int &row, int &column);						// Game board

