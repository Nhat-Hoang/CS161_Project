// 18125050
// Nguyen Phan Nhat Hoang
// Individual Project: Caro / Gomoku

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include "console.h"
#include "Animation.h"
#include "StartScreen.h"
#include "StartGame.h"
#include "LoadGame.h"
#include "OptionGame.h"
#include "StaticsGame.h"
#include "AboutGame.h"
#include "QuitGame.h"
#include "TurnBack.h"
#include "Setting.h"

using namespace std;


int main() {
	SetConsoleOutputCP(437);	// set to display extended ascii characters
	resizeConsole(1180, 620);	// size of console screen
	Nocursortype();				// hide the mouse
	Execute_1();
	clrscr();
	Start_Screen();
	while (1) {
		clrscr();
		Screen();
		int select = Menu();
		switch (select) {
		case 1: {
			//Clear_Menu();
			Start_Game();
			break;
		}
		case 2: {
			Clear_Menu();
			Load_Game();
			break;
		}
		case 3: {
			Clear_Menu();
			Option_Game();
			break;
		}
		case 4: {
			Clear_Menu();
			Statics_Game();
			break;
		}
		case 5: {
			Clear_Menu();
			clrscr();
			About_Game();
			break;
		}
		case 6: {
			Clear_Menu(); 
			int choose = Quit_Game();
			if (choose == 0) {
				gotoXY(0, 27);
				exit(0);
			}
			else {

			}
			break;
		}
		}
	} 
	return 0;
}