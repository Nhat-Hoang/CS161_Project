#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "console.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define ConsoleWidth  112
#define ConsoleHeight 30
#define Color 15

enum Status { UP, DOWN, ENTER };

Status key4(int z) {
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

int About_Game() {

	ifstream textfile("About.txt");
	string s1; //store a line of file

	stringstream ss;
	ss << textfile.rdbuf(); //pass data in buffer into stream ss
	s1 = ss.str(); //assign to s1 string
	cout << s1.data() << endl;

	gotoXY(0, 0); cout << "   " << endl;
	int n = 7;
	int tt = 1;
	int *mau = new int[n];
	for (int i = 0; i > n; i++) mau[i] = Color;

	while (1) {

		int z = _getch();
		Status TrangThai = key4(z);
		switch (TrangThai)
		{
		case UP: {
			//if (tt == 1) tt = n - 1;
			--tt;
			break;
		}
		case DOWN: {
			if (tt == n - 1) tt = 1;
			else ++tt;
			break;
		}
		case ENTER: return tt;
		for (int i = 0; i < n; i++) mau[i] = Color;
					//	mau[tt] = 124;
		}
	}
}