#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "console.h"
#include <string>


using namespace std;

#define ConsoleWidth  134
#define ConsoleHeight 62
#define Color 15

struct Define_Screen_Titile{
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
};
struct Define_Screen_Info {
	char Name[40];
	char MSSV[60];
	int x, y;
};

enum Status {UP, DOWN, ENTER};

Status key(int z) {
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


// Co 1 khoang trong o menuist[1] de menuList[2] -> menuList[7] hien thi giong nhau
int Menu() {
	int n = 7, tt = 0;
	int mau[7];
	for (int i = 0; i < n; i++) mau[i] = Color;
	
	while (1) {
		int x;
		int y = 22;
		string menuList[7] = { "", "Start","Load game", "Option", "Statistics", "About", "Quit" };
		int lent[7] = { 1, 6, 10, 7, 11, 6, 5 };
		for (int i = 0; i < n; i++) {
			x = ((ConsoleWidth-lent[i]) / 2)-2;
			gotoXY(x, y);
			TextColor(mau[i]);
			cout << menuList[i] << endl;
			y++;
		}
		int z = _getch();
		Status TrangThai = key(z);
		switch (TrangThai)
		{
		case UP: {
			if (tt == 1 || tt == 0) tt = n - 1;
			else --tt;
			break;
		}
		case DOWN: {
			if (tt == n - 1) tt = 1;
			else ++tt;
			break;
		}
		case ENTER: {
			for (int ahi = 0; ahi <= lent[tt]; ahi++) {
				gotoXY((ConsoleWidth - lent[tt]) / 2 - 2 + ahi, 19 + tt);
				TextColor(15);
				cout << " ";
			}
			return tt;
		}
		}
		for (int i = 0; i < n; i++) mau[i] = Color;
		mau[tt] = 124;
	}
}

void Start_Screen() {

	// TITILE
	{
		Define_Screen_Titile Titile;
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
		Titile.x = (ConsoleWidth - lenght) / 2;
		Titile.y = 3;

		//clrscr();

		// Print Titile
		gotoXY(Titile.x, Titile.y);
		TextColor(11);
		cout << Titile.line1 << endl;
		gotoXY(Titile.x, Titile.y + 12);
		cout << Titile.line13 << endl;
		Sleep(30);
		gotoXY(Titile.x, Titile.y + 1);
		cout << Titile.line2 << endl;
		gotoXY(Titile.x, Titile.y + 11);
		cout << Titile.line12 << endl;
		Sleep(25);
		gotoXY(Titile.x, Titile.y + 2);
		cout << Titile.line3 << endl;
		gotoXY(Titile.x, Titile.y + 10);
		cout << Titile.line11 << endl;
		Sleep(25);
		gotoXY(Titile.x, Titile.y + 3);
		cout << Titile.line4 << endl;
		gotoXY(Titile.x, Titile.y + 9);
		cout << Titile.line10 << endl;
		Sleep(25);
		gotoXY(Titile.x, Titile.y + 4);
		cout << Titile.line5 << endl;
		gotoXY(Titile.x, Titile.y + 8);
		cout << Titile.line9 << endl;
		Sleep(25);
		gotoXY(Titile.x, Titile.y + 5);
		cout << Titile.line6 << endl;
		gotoXY(Titile.x, Titile.y + 7);
		cout << Titile.line8 << endl;
		Sleep(25);
		gotoXY(Titile.x, Titile.y + 6);
		cout << Titile.line7 << endl;
		Sleep(60);
	}

	// Information
	{

		Define_Screen_Info Info;
		strcpy(Info.Name, "Name: Nguyen Phan Nhat Hoang");
		strcpy(Info.MSSV, "MSSV: 18125050    Class: 18APCS1");
		int Lent = strlen(Info.Name);
		Info.x = (ConsoleWidth - Lent) / 2 + 27;
		Info.y = 19;

		TextColor(15);
		Sleep(300);
		gotoXY(Info.x, Info.y);
		//cout << Info.Name << endl;
		for (int i = 0; i < strlen(Info.Name); i++) {
			cout << Info.Name[i];
			Sleep(40);
		}
		Sleep(200);
		gotoXY(Info.x, Info.y + 1);
		//cout << Info.MSSV << endl;
		for (int i = 0; i < strlen(Info.MSSV); i++) {
			cout << Info.MSSV[i];
			Sleep(40);
		}
		cout << endl;
	}
}

void Screen() {

	// TITILE
	{
		Define_Screen_Titile Titile;
		strcpy(Titile.line1, "     gggggg                                                                       ");
		strcpy(Titile.line2, "   gggggggggg                                             kkk                     ");
		strcpy(Titile.line3, "  gggg    gggg                                            kk                      ");
		strcpy(Titile.line4, " gggg      gggg                                           kk      kkk             ");
		strcpy(Titile.line5, "gggg        gggg                                          kk     kk               ");
		strcpy(Titile.line6, "gggg                 ooo     mm  mmm    mmmm      ooo     kk    kk     uu     uu  ");
		strcpy(Titile.line7, "gggg               ooooooo   mm mm mm  mm mmm   ooooooo   kk  kk       uu     uu  ");
		strcpy(Titile.line8, "gggg      gggggg  oo     oo  mmmm   mmm    mm  oo     oo  kkkkk        uu     uu  ");
		strcpy(Titile.line9, "gggg      gggggg  oo     oo  mm     mm     mm  oo     oo  kk kkk       uu     uu  ");
		strcpy(Titile.line10, "gggg        gggg  oo     oo  mm     mm     mm  oo     oo  kk  kk       uu     uu  ");
		strcpy(Titile.line11, " ggggg      ggg   oo     oo  mm     mm     mm  oo     oo  kk   kk      uu     uu  ");
		strcpy(Titile.line12, "  gggggg ggggg     ooooooo   mm     mm     mm   ooooooo   kk    kk      uuu uuuu  ");
		strcpy(Titile.line13, "   gggggggggg        ooo     mm     mm     mm     ooo     kk     kkkk    uuuuu uu ");

		int lenght = strlen(Titile.line1);
		Titile.x = (ConsoleWidth - lenght) / 2;
		Titile.y = 1;


		// Print Titile
		gotoXY(Titile.x, Titile.y);
		TextColor(11);
		cout << Titile.line1 << endl;
		gotoXY(Titile.x, Titile.y + 12);
		cout << Titile.line13 << endl;

		gotoXY(Titile.x, Titile.y + 1);
		cout << Titile.line2 << endl;
		gotoXY(Titile.x, Titile.y + 11);
		cout << Titile.line12 << endl;

		gotoXY(Titile.x, Titile.y + 2);
		cout << Titile.line3 << endl;
		gotoXY(Titile.x, Titile.y + 10);
		cout << Titile.line11 << endl;

		gotoXY(Titile.x, Titile.y + 3);
		cout << Titile.line4 << endl;
		gotoXY(Titile.x, Titile.y + 9);
		cout << Titile.line10 << endl;
		
		gotoXY(Titile.x, Titile.y + 4);
		cout << Titile.line5 << endl;
		gotoXY(Titile.x, Titile.y + 8);
		cout << Titile.line9 << endl;
		
		gotoXY(Titile.x, Titile.y + 5);
		cout << Titile.line6 << endl;
		gotoXY(Titile.x, Titile.y + 7);
		cout << Titile.line8 << endl;
	
		gotoXY(Titile.x, Titile.y + 6);
		cout << Titile.line7 << endl;
	}

	// Information
	{

		Define_Screen_Info Info;
		strcpy(Info.Name, "Name: Nguyen Phan Nhat Hoang");
		strcpy(Info.MSSV, "MSSV: 18125050    Class: 18APCS1");
		int Lent = strlen(Info.Name);
		Info.x = (ConsoleWidth - Lent) / 2 + 27;
		Info.y = 16;

		TextColor(15);
		gotoXY(Info.x, Info.y);
		cout << Info.Name << endl;

		gotoXY(Info.x, Info.y + 1);
		cout << Info.MSSV << endl;
		cout << endl;
	}
}

void Clear_Menu() {
	clrscr();
	system("Color 7");
	Screen();
}