#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include "console.h"
#include <time.h>

#define ConsoleWidth    134
#define ConsoleHeight   62

using namespace std;

enum status {UP, DOWN, LEFT, RIGHT};

struct Define_Animation {
	char line1[90];
	char line2[90];
	char line3[90];
	char line4[90];
	char line5[90];
	char line6[90];
	char line7[90];
	char line8[90];
	char line9[90];
	char line10[90];
	char line11[90];
	char line12[90];
	char line13[90];
	int x, y;
	status tt;
};
struct Define_Animation_Name {
	char Name[40];
	char MSSV[60];
	int x, y;
	status tt;
};

void Execute_1() {

	srand(time(NULL)); // khoi tao bo sinh so random

	Define_Animation Titile;
	strcpy(Titile.line1,  "     gggggg                                                                       ");
	strcpy(Titile.line2,  "   gggggggggg                                             kkk                     ");
	strcpy(Titile.line3,  "  gggg    gggg                                            kk                      ");
	strcpy(Titile.line4,  " gggg      gggg                                           kk      kkk             ");
	strcpy(Titile.line5,  "gggg        gggg                                          kk     kk               ");
	strcpy(Titile.line6,  "gggg                 ooo     mm  mmm    mmmm      ooo     kk    kk     uu     uu  ");
	strcpy(Titile.line7,  "gggg               ooooooo   mm mm mm  mm mmm   ooooooo   kk  kk       uu     uu  ");
	strcpy(Titile.line8,  "gggg      gggggg  oo     oo  mmmm   mmm    mm  oo     oo  kkkkk        uu     uu  ");
	strcpy(Titile.line9,  "gggg      gggggg  oo     oo  mm     mm     mm  oo     oo  kk kkk       uu     uu  ");
	strcpy(Titile.line10, "gggg        gggg  oo     oo  mm     mm     mm  oo     oo  kk  kk       uu     uu  ");
	strcpy(Titile.line11, " ggggg      ggg   oo     oo  mm     mm     mm  oo     oo  kk   kk      uu     uu  ");
	strcpy(Titile.line12, "  gggggg ggggg     ooooooo   mm     mm     mm   ooooooo   kk    kk      uuu uuuu  ");
	strcpy(Titile.line13, "   gggggggggg        ooo     mm     mm     mm     ooo     kk     kkkk    uuuuu uu ");

	int lenght = strlen(Titile.line1);

	Titile.x = (ConsoleWidth- lenght) / 2;
	Titile.y = 7;
	Titile.tt = LEFT;

	int lenLoad = 1;

	// vong lap chay chu
	for (int i = 0; i < 50; i++) {
		clrscr();

		gotoXY((ConsoleWidth - 10) / 2, 23);
		TextColor(15);
		cout << "Loading..." << endl;

		// Print Titile
		gotoXY(Titile.x, Titile.y);		
		TextColor(8 + rand() % 8);
		cout << Titile.line1 << endl;
		gotoXY(Titile.x, Titile.y + 1);
		cout << Titile.line2 << endl;
		gotoXY(Titile.x, Titile.y + 2);
		cout << Titile.line3 << endl;
		gotoXY(Titile.x, Titile.y + 3);
		cout << Titile.line4 << endl;
		gotoXY(Titile.x, Titile.y + 4);
		cout << Titile.line5 << endl;
		gotoXY(Titile.x, Titile.y + 5);
		cout << Titile.line6 << endl;
		gotoXY(Titile.x, Titile.y + 6);
		cout << Titile.line7 << endl;
		gotoXY(Titile.x, Titile.y + 7);
		cout << Titile.line8 << endl;
		gotoXY(Titile.x, Titile.y + 8);
		cout << Titile.line9 << endl;
		gotoXY(Titile.x, Titile.y + 9);
		cout << Titile.line10 << endl;
		gotoXY(Titile.x, Titile.y + 10);
		cout << Titile.line11 << endl;
		gotoXY(Titile.x, Titile.y + 11);
		cout << Titile.line12 << endl;
		gotoXY(Titile.x, Titile.y + 12);
		cout << Titile.line13 << endl;

		// Reach the border Titile!!
		if (Titile.x <= ((ConsoleWidth - lenght) / 2 - 5))
			Titile.tt = RIGHT;
		else if (Titile.x >= (ConsoleWidth - lenght)/2 + 5)
			Titile.tt = LEFT;
		
		// Run Animation_Titile !!
		if (Titile.tt == LEFT)
			Titile.x--;
		else if (Titile.tt == RIGHT)
			Titile.x++;

		// Run Loading bar
		if (i % 2 == 0) {
			if (lenLoad < 25) {
				gotoXY((ConsoleWidth - 20) / 2 + lenLoad - 5, 24);
				TextColor(240);
				cout << " ";
				lenLoad++;
				gotoXY((ConsoleWidth - 2) / 2 - 1, 25);
				TextColor(15);
				cout << lenLoad * 4 << "%" << endl;
			}
			
		}
		if (lenLoad == 25) {
			gotoXY((ConsoleWidth - 2) / 2 - 1, 25);
			TextColor(15);
			cout << 100 << "%" << endl;
		}

		if (i < 49)
			Sleep(40);
		else {
			Sleep(200);
			gotoXY((ConsoleWidth - 20) / 2 - 4, 24);
			TextColor(15);
			cout << "                        " << endl;
			Sleep(200);
		}
	}
	
};

void Lose_Animation() {
	Define_Animation Lose;
	strcpy(Lose.line1, "Y    Y   OO   U   U     LL       OO   SSSSS EEEEEE  !! !!");
	strcpy(Lose.line2, " Y  Y  OO  OO U   U     LL     OO  OO SS    EE      !! !!");
	strcpy(Lose.line3, "  YY   OO  OO U   U     LL     OO  OO   SS  EEEE    !! !!");
	strcpy(Lose.line4, "  YY     OO   UUUUU     LLLLLL   OO   SSSSS EEEEEE  .. ..");

	int lenght = strlen(Lose.line1);

	Lose.x = 78;
	Lose.y = 8;
	int color;

	//Print
	for (int timeloop = 0; timeloop < 12; timeloop++) {
		if (timeloop % 2 == 0) color = 12;
		else color = 8;
		TextColor(timeloop);
		gotoXY(Lose.x, Lose.y);
		cout << Lose.line1 << endl;
		gotoXY(Lose.x, Lose.y+1);
		cout << Lose.line2 << endl;
		gotoXY(Lose.x, Lose.y+2);
		cout << Lose.line3 << endl;
		gotoXY(Lose.x, Lose.y+3);
		cout << Lose.line4 << endl;
		Sleep(50);
	}
}

void Win_Animation(int n) {
	Define_Animation Win;
	if (n == 0) {
		strcpy(Win.line1, "Y    Y   OO   U   U    W   W   W IIII NN   N  !! !!");
		strcpy(Win.line2, " Y  Y  OO  OO U   U     W WWW W   II  N N  N  !! !!");
		strcpy(Win.line3, "  YY   OO  OO U   U      WW WW    II  N  N N  !! !!");
		strcpy(Win.line4, "  YY     OO   UUUUU      W   W   IIII N   NN  .. ..");
	}
	else if (n == 1) {
		strcpy(Win.line1, "PPPPP  LL      AA   Y    Y EEEEEE RRRRR      11 ");
		strcpy(Win.line2, "PP  PP LL    AA  AA  Y  Y  EE     RR  RR    111 ");
		strcpy(Win.line3, "PPPP   LL    AAAAAA   YY   EEEE   RRRR       11 ");
		strcpy(Win.line4, "PP     LLLLL AA  AA   YY   EEEEEE RR  RR    1111");
	}
	else if (n == 2) {
		strcpy(Win.line1, "PPPPP  LL      AA   Y    Y EEEEEE RRRRR      22222");
		strcpy(Win.line2, "PP  PP LL    AA  AA  Y  Y  EE     RR  RR        22");
		strcpy(Win.line3, "PPPP   LL    AAAAAA   YY   EEEE   RRRR       222  ");
		strcpy(Win.line4, "PP     LLLLL AA  AA   YY   EEEEEE RR  RR     22222");
	}
	                                                                 
	strcpy(Win.line5, "W   W   W IIII NN   N  !! !!");
	strcpy(Win.line6, " W WWW W   II  N N  N  !! !!");
	strcpy(Win.line7, "  WW WW    II  N  N N  !! !!");
	strcpy(Win.line8, "  W   W   IIII N   NN  .. ..");
	int lenght = strlen(Win.line1);

	Win.x = 80;
	Win.y = 3;
	
	//Print
	for (int timeloop = 0; timeloop < 18; timeloop++) {
		int Color;
		// Change color of Animation
		switch (timeloop % 4) {
		case 0: {
			Color = 9;
			break;
		}
		case 1: {
			Color = 10;
			break;
		}
		case 2: {
			Color = 11;
			break;
		}
		case 3: {
			Color = 12;
			break;
		}
		}
		TextColor(Color);
		gotoXY(Win.x, Win.y);
		cout << Win.line1 << endl;
		gotoXY(Win.x, Win.y+1);
		cout << Win.line2 << endl;
		gotoXY(Win.x, Win.y+2);
		cout << Win.line3 << endl;
		gotoXY(Win.x, Win.y+3);
		cout << Win.line4 << endl;
		if (n != 0) {
			gotoXY(Win.x+4, Win.y+6);
			cout << Win.line5 << endl;
			gotoXY(Win.x+4, Win.y+7);
			cout << Win.line6 << endl;
			gotoXY(Win.x+4, Win.y+8);
			cout << Win.line7 << endl;
			gotoXY(Win.x+4, Win.y+9);
			cout << Win.line8 << endl;
		}

		Sleep(60);
	}
}
