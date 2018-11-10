#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "console.h"
#include <string>
#include "StartScreen.h"
#include "OptionGame.h"
#include "Setting.h"
#include "Animation.h"
using namespace std;

#define ConsoleWidth  134
#define ConsoleHeight 62
#define Color 15


enum Status { Up, Down, EnTer };
Status key2(int z) {
	if (z == 224) {
		char c;
		c = _getch();
		if (c == 72) return Up;
		if (c == 80) return Down;
	}
	else if (z == 87 || z == 119) return Up;         // W & w
	else if (z == 83 || z == 115) return Down;		// S & s
	else if (z == 13) return EnTer;
}

enum Control { UP, DOWN, LEFT, RIGHT, X, O, ENTER, ESC, SPACE };
Control move(int z) {
	if (z == 224) {
		char c;
		c = _getch();
		if (c == 72) return UP;
		if (c == 80) return DOWN;
		if (c == 75) return LEFT;
		if (c == 77) return RIGHT;
	}
	else if (z == 87 || z == 119) return UP;        // W & w
	else if (z == 83 || z == 115) return DOWN;		// S & s
	else if (z == 65 || z == 97)  return LEFT;		// A & a
	else if (z == 68 || z == 100) return RIGHT;		// D & d
	else if (z == 88 || z == 120) return X;
	else if (z == 79 || z == 111) return O;
	else if (z == 13) return ENTER;
	else if (z == 27 || z == 66 || z == 98) return ESC;
	else if (z == 32) return SPACE;
}

int Select_Mode();
void PP_Mode();
int PC_Mode();
void Score_of_Cell(int n);
int test_Move(int x, int y);
int test_Move_High(int x, int y);
int Easy_mode(int n);
int Medium_mode(int n);
int Hard_mode(int n);
int Check_Win(char a[][32], int x, int y, int n, int m);
int Pointer_medium(char a[][32], int n, int m);

char filled[64][32];
int score[64][32];
int Enemyscore[64][32];

int Start_Game() {
	while (1) {
		clrscr();
		Screen();
		int selected = Select_Mode();
		switch (selected) {
		case 1: {
			clrscr();
			system("Color 7");
			Board(16);
			PP_Mode();
			break;
		}
		case 2: {
			clrscr();
			system("Color 7");
			PC_Mode();
			break;
		}
		case 3: return 0;
		}
	}
}

int Select_Mode() {
	int n = 4, tt = 0;
	int mau[5];
	for (int i = 0; i < 5; i++) mau[i] = Color;
	while (1) {
		int x;
		int y = 22;
		int lent[4] = { 1, 14, 10, 5 };
		string Start[4] = { "", "Player-Player","Player-PC","Back" };
		for (int i = 0; i < n; i++) {
			x = ((ConsoleWidth - lent[i]) / 2) - 2;
			gotoXY(x, y);
			TextColor(mau[i]);
			cout << Start[i] << endl;
			y++;
		}
		int z = _getch();
		Status TrangThai = key2(z);
		switch (TrangThai)
		{
		case Up: {
			if (tt == 1 || tt == 0) tt = n - 1;
			else --tt;
			break;
		}
		case Down: {
			if (tt == n - 1) tt = 1;
			else ++tt;
			break;
		}
		case EnTer: return tt;
		}
		for (int i = 0; i < n; i++) mau[i] = Color;
		mau[tt] = 124;
	}
}

int Difficulty() {
	int n = 5, tt = 0;
	int mau[6];
	for (int i = 0; i < 6; i++) mau[i] = Color;
	while (1) {
		int x;
		int y = 22;
		int lent[5] = { 1, 5, 7, 5, 5 };
		string Difficult[5] = { "", "Easy","Medium","Hard", "Back" };
		for (int i = 0; i < n; i++) {
			x = ((ConsoleWidth - lent[i]) / 2) - 2;
			gotoXY(x, y);
			TextColor(mau[i]);
			cout << Difficult[i] << endl;
			y++;
		}
		int z = _getch();
		Status TrangThai = key2(z);
		switch (TrangThai)
		{
		case Up: {
			if (tt == 1 || tt == 0) tt = n - 1;
			else --tt;
			break;
		}
		case Down: {
			if (tt == n - 1) tt = 1;
			else ++tt;
			break;
		}
		case EnTer: return tt;
		}
		for (int i = 0; i < n; i++) mau[i] = Color;
		mau[tt] = 124;
	}
}

void PP_Mode() {

	Pointer_medium(filled, 16, 16);
}
int PC_Mode() {
	while (1) {
		clrscr();
		Screen();
		int choose = Difficulty();
		switch (choose) {
		case 1: {
			clrscr();
			Board(16);
			Easy_mode(16);
			break;
		}
		case 2: {
			system("Color 7");
			clrscr();
			Board(16);
			Medium_mode(16);
			break;
		}
		case 3: {
			system("Color 7");
			clrscr();
			Board(16);
			Hard_mode(16);
			break;
		}
		case 4: {
			system("Color 7");
			return 0;
		}
		}
	}
}

int Pointer_medium(char a[][32], int n, int m) {

	int mau[80][40];
	n *= 4;
	m *= 2;
	int x = 26;
	int y = 15;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			a[i][j] = ' ';


	int color;
	int step = 1;		// count the ordinal of steps

	while (1) {

		int CurX = x, CurY = y;

		// Check win
		int isWin = Check_Win(filled, x, y, 16, 16);
		if (isWin) {
			// Delete the mouse
			if (a[x][y] == 'X') {
				TextColor(12);
				gotoXY(x, y);
				cout << a[x][y] << endl;
			}
			else if (a[x][y] == 'O') {
				TextColor(10);
				gotoXY(x, y);
				cout << a[x][y] << endl;
			}
			// Win Animation
			if (step % 2 != 0) Win_Animation(2);		// Player 2 win
			else Win_Animation(1);						// Player 1 win
			gotoXY(90, 15);
			cout << "Enter to return to menu";
			while (1) {
				clrscr();
				system("Color 7");
				int zz = _getch();
				Control Choose = move(zz);
				switch (Choose) {
				case UP: {
					break;
				}
				case DOWN: {
					break;
				}
				case ENTER: return 0;
				}
			}	
		}

		int z = _getch();
		Control Moving = move(z);
		switch (Moving)
		{
		case UP: {
			if (y == 1) y = m - 1;
			else y -= 2;
			break;
		}
		case DOWN: {
			if (y == m - 1) y = 1;
			else y += 2;
			break;
		}
		case LEFT: {
			if (x == 2) x = n - 2;
			else x -= 4;
			break;
		}
		case RIGHT: {
			if (x == n - 2) x = 2;
			else x += 4;
			break;
		}
		case X: {
			if (step % 2 != 0) {
				if (a[x][y] == ' ') {
					TextColor(124);
					gotoXY(x, y);
					a[x][y] = 'X';
					cout << a[x][y] << endl;
					step++;
				}
			}
			break;
		}
		case O: {
			if (step % 2 == 0) {
				if (a[x][y] == ' ') {
					TextColor(122);
					gotoXY(x, y);
					a[x][y] = 'O';
					cout << a[x][y] << endl;
					step++;
				}
			}
			break;
		}
		case SPACE: {
			if (step % 2 != 0) {
				if (a[x][y] == ' ') {
					TextColor(124);
					gotoXY(x, y);
					a[x][y] = 'X';
					cout << a[x][y] << endl;
					step++;
				}
			}
			else {
				if (a[x][y] == ' ') {
					TextColor(122);
					gotoXY(x, y);
					a[x][y] = 'O';
					cout << a[x][y] << endl;
					step++;
				}
			}
			break;
		}
		case ESC: {
			return 0;
		}
		}

		// change color previous step
		if (CurX != x || CurY != y) {
			if (a[CurX][CurY] == 'X') color = 12;
			else if (a[CurX][CurY] == 'O') color = 10;
			else color = 0;
			TextColor(color);
			gotoXY(CurX, CurY);
			cout << a[CurX][CurY] << endl;
		}

		//change color present step
		if (a[x][y] == 'X') color = 124;
		else if (a[x][y] == 'O') color = 122;
		else color = 119;
		TextColor(color);
		gotoXY(x, y);
		cout << a[x][y] << endl;
	}
}		// 

int Easy_mode(int n) {

	int mau[80][40];
	int x = 30;
	int y = 17;
	for (int i = 0; i < 4*n; i++)
		for (int j = 0; j < 2*n; j++)
			filled[i][j] = ' ';

	int color;
	int step = 1;
	while (1) {
		int CurX = x, CurY = y;
		int locaX = 0, locaY = 0;

		// Check win
		int isWin = Check_Win(filled, x, y, 16, 16);
		if (isWin == 1) {
			// Delete the mouse
			if (filled[x][y] == 'X') {
				TextColor(12);
				gotoXY(x, y);
				cout << filled[x][y] << endl;
			}
			else if (filled[x][y] == 'O') {
				TextColor(10);
				gotoXY(x, y);
				cout << filled[x][y] << endl;
			}
			// Win Animation
			if (step % 2 == 0) Win_Animation(0);		// You win
			else Lose_Animation();						// You lose :)))
			gotoXY(90, 15);
			cout << "Enter to return to menu";
			while (1) {
				int zz = _getch();
				Control Choose = move(zz);
				switch (Choose) {
				case UP: {
					// Choose option
					system("Color 7");
					break;
				}
				case DOWN: {
					// Choose option
					system("Color 7");
					break;
				}
				case ENTER: {
					system("Color 7");
					return 0;
				}
				}
			}
		}

		//	Player turn
		if (step % 2 != 0) {	
			int z = _getch();
			Control Moving = move(z);
			switch (Moving)
			{
			case UP: {
				if (y == 1) y = 2 * n - 1;
				else y -= 2;
				break;
			}
			case DOWN: {
				if (y == 2 * n - 1) y = 1;
				else y += 2;
				break;
			}
			case LEFT: {
				if (x == 2) x = 4 * n - 2;
				else x -= 4;
				break;
			}
			case RIGHT: {
				if (x == 4 * n - 2) x = 2;
				else x += 4;
				break;
			}
			case X: {
				if (step % 2 != 0) {
					if (filled[x][y] == ' ') {
						TextColor(124);
						gotoXY(x, y);
						filled[x][y] = 'X';
						cout << filled[x][y] << endl;
						step++;
					}
				}
				break;
			}
			case SPACE: {
				if (step % 2 != 0) {
					if (filled[x][y] == ' ') {
						TextColor(124);
						gotoXY(x, y);
						filled[x][y] = 'X';
						cout << filled[x][y] << endl;
						step++;
					}
				}
				break;
			}
			case ESC: {
				return 0;
			}
			}
		}
		//	Computer turn
		else {
			// Choose max-score cell to enter
			int maxScore = 0;
			for (int i = 2; i < 64; i += 4)
				for (int j = 1; j < 32;j += 2)
					if (maxScore <= score[i][j]) {
						maxScore = score[i][j];
						locaX = i; locaY = j;
					}
			if (step == 2) {
				locaX = CurX + 4;
				locaY = CurY;
			}
			if (maxScore == 0) {
				locaX = CurX; locaY = CurY;
				while (filled[locaX][locaY] != ' ') {
					locaX++; locaY++;
				}
			}
			TextColor(122);
			gotoXY(locaX, locaY);
			filled[locaX][locaY] = 'O';
			cout << filled[locaX][locaY] << endl;
			step++;

			x = locaX; y = locaY;
		}
		Score_of_Cell(16);

		// change color previous step
		if (CurX != x || CurY != y) {
			if (filled[CurX][CurY] == 'X') color = 12;
			else if (filled[CurX][CurY] == 'O') color = 10;
			else color = 0;
			TextColor(color);
			gotoXY(CurX, CurY);
			cout << filled[CurX][CurY] << endl;
		}

		//change color present step
		if (filled[x][y] == 'X') color = 124;
		else if (filled[x][y] == 'O') color = 122;
		else color = 119;
		TextColor(color);
		gotoXY(x, y);
		cout << filled[x][y] << endl;
	}
	return 0;
}

int Medium_mode(int n) {
	int mau[80][40];
	int x = 30;
	int y = 17;
	for (int i = 0; i < 4 * n; i++)
		for (int j = 0; j < 2 * n; j++)
			filled[i][j] = ' ';

	int color;
	int step = 1;
	while (1) {
		int CurX = x, CurY = y;
		int locaX = 0, locaY = 0;
		int locaX1 = 0, locaY1 = 0;
		int locaX2 = 0, locaY2 = 0;

		// Check win
		int isWin = Check_Win(filled, x, y, 16, 16);
		if (isWin == 1) {
			// Delete the mouse
			if (filled[x][y] == 'X') {
				TextColor(12);
				gotoXY(x, y);
				cout << filled[x][y] << endl;
			}
			else if (filled[x][y] == 'O') {
				TextColor(10);
				gotoXY(x, y);
				cout << filled[x][y] << endl;
			}
			// Win Animation
			if (step % 2 == 0) Win_Animation(0);		// You win
			else Lose_Animation();						// You lose :)))
			gotoXY(90, 15);
			cout << "Enter to return to menu";
			while (1) {
				int zz = _getch();
				Control Choose = move(zz);
				switch (Choose) {
				case UP: {
					// Choose option
					system("Color 7");
					break;
				}
				case DOWN: {
					// Choose option
					system("Color 7");
					break;
				}
				case ENTER: {
					system("Color 7");
					return 0;
				}
				}
			}
		}

		//	Player turn
		if (step % 2 != 0) {
			int z = _getch();
			Control Moving = move(z);
			switch (Moving)
			{
			case UP: {
				if (y == 1) y = 2 * n - 1;
				else y -= 2;
				break;
			}
			case DOWN: {
				if (y == 2 * n - 1) y = 1;
				else y += 2;
				break;
			}
			case LEFT: {
				if (x == 2) x = 4 * n - 2;
				else x -= 4;
				break;
			}
			case RIGHT: {
				if (x == 4 * n - 2) x = 2;
				else x += 4;
				break;
			}
			case X: {
				if (step % 2 != 0) {
					if (filled[x][y] == ' ') {
						TextColor(124);
						gotoXY(x, y);
						filled[x][y] = 'X';
						cout << filled[x][y] << endl;
						step++;
					}
				}
				break;
			}
			case SPACE: {
				if (step % 2 != 0) {
					if (filled[x][y] == ' ') {
						TextColor(124);
						gotoXY(x, y);
						filled[x][y] = 'X';
						cout << filled[x][y] << endl;
						step++;
					}
				}
				break;
			}
			case ESC: {
				return 0;
			}
			}
		}
		//	Computer turn
		else {
			// Choose max-score cell to enter
			int max1Score = 0;
			for (int i = 2; i < 64; i += 4)
				for (int j = 1; j < 32;j += 2)
					if (max1Score <= score[i][j]) {
						max1Score = score[i][j];
						locaX1 = i; locaY1 = j;
					}
			int max2Score = 0;
			for (int i = 2; i < 64; i += 4)
				for (int j = 1; j < 32;j += 2)
					if ((max2Score <= score[i][j]) && (max1Score >= score[i][j])) {
						max2Score = score[i][j];
						locaX2 = i; locaY2 = j;
					}
			// Find the better move to play
			int attempt1 = test_Move(locaX1, locaY1);
			int attempt2 = test_Move(locaX2, locaY2);
			if (attempt1 > attempt2) {
				locaX = locaX1; locaY = locaY1;
			}
			else {
				locaX = locaX2; locaY = locaY2;
			}
			if (step == 2) {
				locaX = CurX + 4;
				locaY = CurY + 2;
			}

			TextColor(122);
			gotoXY(locaX, locaY);
			filled[locaX][locaY] = 'O';
			cout << filled[locaX][locaY] << endl;
			step++;

			x = locaX; y = locaY;
		}
		Score_of_Cell(16);

		// change color previous step
		if (CurX != x || CurY != y) {
			if (filled[CurX][CurY] == 'X') color = 12;
			else if (filled[CurX][CurY] == 'O') color = 10;
			else color = 0;
			TextColor(color);
			gotoXY(CurX, CurY);
			cout << filled[CurX][CurY] << endl;
		}

		//change color present step
		if (filled[x][y] == 'X') color = 124;
		else if (filled[x][y] == 'O') color = 122;
		else color = 119;
		TextColor(color);
		gotoXY(x, y);
		cout << filled[x][y] << endl;
	}
	return 0;
}

int Hard_mode(int n) {
	int mau[80][40];
	int x = 30;
	int y = 17;
	for (int i = 0; i < 4 * n; i++)
		for (int j = 0; j < 2 * n; j++)
			filled[i][j] = ' ';

	int color;
	int step = 1;
	while (1) {
		int CurX = x, CurY = y;
		int locaX = 0, locaY = 0;
		int locaX1 = 0, locaY1 = 0;
		int locaX2 = 0, locaY2 = 0;

		// Check win
		int isWin = Check_Win(filled, x, y, 16, 16);
		if (isWin == 1) {
			// Delete the mouse
			if (filled[x][y] == 'X') {
				TextColor(12);
				gotoXY(x, y);
				cout << filled[x][y] << endl;
			}
			else if (filled[x][y] == 'O') {
				TextColor(10);
				gotoXY(x, y);
				cout << filled[x][y] << endl;
			}
			// Win Animation
			if (step % 2 == 0) Win_Animation(0);		// You win
			else Lose_Animation();						// You lose :)))
			gotoXY(90, 15);
			cout << "Enter to return to menu";
			while (1) {
				int zz = _getch();
				Control Choose = move(zz);
				switch (Choose) {
				case UP: {
					// Choose option
					system("Color 7");
					break;
				}
				case DOWN: {
					// Choose option
					system("Color 7");
					break;
				}
				case ENTER: {
					system("Color 7");
					return 0;
				}
				}
			}
		}

		//	Player turn
		if (step % 2 != 0) {
			int z = _getch();
			Control Moving = move(z);
			switch (Moving)
			{
			case UP: {
				if (y == 1) y = 2 * n - 1;
				else y -= 2;
				break;
			}
			case DOWN: {
				if (y == 2 * n - 1) y = 1;
				else y += 2;
				break;
			}
			case LEFT: {
				if (x == 2) x = 4 * n - 2;
				else x -= 4;
				break;
			}
			case RIGHT: {
				if (x == 4 * n - 2) x = 2;
				else x += 4;
				break;
			}
			case X: {
				if (step % 2 != 0) {
					if (filled[x][y] == ' ') {
						TextColor(124);
						gotoXY(x, y);
						filled[x][y] = 'X';
						cout << filled[x][y] << endl;
						step++;
					}
				}
				break;
			}
			case SPACE: {
				if (step % 2 != 0) {
					if (filled[x][y] == ' ') {
						TextColor(124);
						gotoXY(x, y);
						filled[x][y] = 'X';
						cout << filled[x][y] << endl;
						step++;
					}
				}
				break;
			}
			case ESC: {
				return 0;
			}
			}
		}
		//	Computer turn
		else {
			// Choose max-score cell to enter
			int max1Score = 0;
			for (int i = 2; i < 64; i += 4)
				for (int j = 1; j < 32;j += 2)
					if (max1Score <= score[i][j]) {
						max1Score = score[i][j];
						locaX1 = i; locaY1 = j;
					}
			int max2Score = 0;
			for (int i = 2; i < 64; i += 4)
				for (int j = 1; j < 32;j += 2)
					if ((max2Score <= score[i][j]) && (max1Score >= score[i][j])) {
						max2Score = score[i][j];
						locaX2 = i; locaY2 = j;
					}
			// Find the better move to play
			int attempt1 = test_Move_High(locaX1, locaY1);
			int attempt2 = test_Move_High(locaX2, locaY2);
			if (attempt1 > attempt2) {
				locaX = locaX1; locaY = locaY1;
			}
			else {
				locaX = locaX2; locaY = locaY2;
			}
			if (step == 2) {
				locaX = CurX + 4;
				locaY = CurY + 2;
			}

			TextColor(122);
			gotoXY(locaX, locaY);
			filled[locaX][locaY] = 'O';
			cout << filled[locaX][locaY] << endl;
			step++;

			x = locaX; y = locaY;
		}
		Score_of_Cell(16);

		// change color previous step
		if (CurX != x || CurY != y) {
			if (filled[CurX][CurY] == 'X') color = 12;
			else if (filled[CurX][CurY] == 'O') color = 10;
			else color = 0;
			TextColor(color);
			gotoXY(CurX, CurY);
			cout << filled[CurX][CurY] << endl;
		}

		//change color present step
		if (filled[x][y] == 'X') color = 124;
		else if (filled[x][y] == 'O') color = 122;
		else color = 119;
		TextColor(color);
		gotoXY(x, y);
		cout << filled[x][y] << endl;
	}
	return 0;
}

int test_Move_High(int x, int y) {
	int mark = score[x][y];
	filled[x][y] = 'O';

	// Enemy score cell
	{
		int n = 16;
		// To evalue the score of each cell for the move
		int DefenseScore[5] = { 0, 2, 14, 98, 686 };
		int AttackScore[5] = { 0, 1, 8, 64, 512 };

		for (int i = 2; i < 64; i += 4)
			for (int j = 1; j < 32;j += 2) Enemyscore[i][j] = 0;

		// evaluate the empty cell
		for (int x = 2; x < n * 4; x += 4)
			for (int y = 1; y < n * 2; y += 2)
				if (filled[x][y] == ' ') {

					//Vertical 
					{
						//Determine how many block to check
						int LeftBorder_of_Block = y - 8;
						int begin = 1;
						while (LeftBorder_of_Block < 1) {
							begin++;
							LeftBorder_of_Block += 2;
						}
						int RightBorder_of_Block = y + 8;
						int end = 5;
						while ((RightBorder_of_Block > 2 * n - 1) && (end >= 1)) {
							end--;
							RightBorder_of_Block -= 2;
						}

						// Number of blocks had to check
						int blocks = end - begin + 1;
						int initial = y - 10 + begin * 2;		//
																//	Check DEFENSE for each block
						while (blocks > 0) {
							if ((filled[x][initial] != 'X') && (filled[x][initial + 2] != 'X') && (filled[x][initial + 4] != 'X') &&
								(filled[x][initial + 6] != 'X') && (filled[x][initial + 8] != 'X')) {
								int num = 0;
								for (int i = initial; i <= initial + 8; i += 2)
									if (filled[x][i] == 'O') num++;
								Enemyscore[x][y] += DefenseScore[num];
							}
							blocks--;
							initial += 2;
						}
						blocks = end - begin + 1;
						initial = y - 10 + begin * 2;
						//	Check ATTACK of each block
						while (blocks > 0) {
							if ((filled[x][initial] != 'O') && (filled[x][initial + 2] != 'O') && (filled[x][initial + 4] != 'O') &&
								(filled[x][initial + 6] != 'O') && (filled[x][initial + 8] != 'O')) {
								int num = 0;
								for (int i = initial; i <= initial + 8; i += 2)
									if (filled[x][i] == 'X') num++;
								Enemyscore[x][y] += AttackScore[num];
							}
							blocks--;
							initial += 2;
						}
					}
					// Horizontal
					{
						//Determine how many block to check
						int TopBorder_of_Block = x - 16;
						int begin = 1;
						while (TopBorder_of_Block < 2) {
							begin++;
							TopBorder_of_Block += 4;
						}
						int BottomBorder_of_Block = x + 16;
						int end = 5;
						while ((BottomBorder_of_Block > 4 * n - 2) && (end >= 1)) {
							end--;
							BottomBorder_of_Block -= 4;
						}

						// Number of blocks had to check
						int blocks = end - begin + 1;
						int initial = x - 20 + begin * 4;		//
																//	Check DEFENSE for each block
						while (blocks > 0) {
							if ((filled[initial][y] != 'X') && (filled[initial + 4][y] != 'X') && (filled[initial + 8][y] != 'X') &&
								(filled[initial + 12][y] != 'X') && (filled[initial + 16][y] != 'X')) {
								int num = 0;
								for (int i = initial; i <= initial + 16; i += 4)
									if (filled[i][y] == 'O') num++;
								Enemyscore[x][y] += DefenseScore[num];
							}
							blocks--;
							initial += 4;
						}
						blocks = end - begin + 1;
						initial = x - 20 + begin * 4;		//
															//	Check ATTACK for each block
						while (blocks > 0) {
							if ((filled[initial][y] != 'O') && (filled[initial + 4][y] != 'O') && (filled[initial + 8][y] != 'O') &&
								(filled[initial + 12][y] != 'O') && (filled[initial + 16][y] != 'O')) {
								int num = 0;
								for (int i = initial; i <= initial + 16; i++)
									if (filled[i][y] == 'X') num++;
								Enemyscore[x][y] += AttackScore[num];
							}
							blocks--;
							initial += 4;
						}
					}
					// Left_Right Diagonal 
					{
						//Determine how many block to check
						int TopBorder_of_Block = x - 16;
						int LeftBorder_of_Block = y - 8;
						int begin = 1;
						while ((TopBorder_of_Block < 2) && (LeftBorder_of_Block < 1)) {
							begin++;
							TopBorder_of_Block += 4;
							LeftBorder_of_Block += 2;
						}
						int BottomBorder_of_Block = x + 16;
						int RightBorder_of_Block = y + 8;
						int end = 5;
						while ((BottomBorder_of_Block > 4 * n - 2) && (RightBorder_of_Block > 2 * n - 1) && (end >= 1)) {
							end--;
							BottomBorder_of_Block -= 4;
							RightBorder_of_Block -= 2;
						}

						// Number of blocks had to check
						int blocks = end - begin + 1;
						int initial_x = x - 20 + begin * 4;
						int initial_y = y - 10 + begin * 2;
						// Check DEFENSE for each block
						while (blocks > 0) {
							if ((filled[initial_x][initial_y] != 'X') && (filled[initial_x + 4][initial_y + 2] != 'X') && (filled[initial_x + 8][initial_y + 4] != 'X') &&
								(filled[initial_x + 12][initial_y + 6] != 'X') && (filled[initial_x + 16][initial_y + 8] != 'X')) {
								int num = 0;
								for (int i = initial_x, j = initial_y; i <= initial_x + 16, j <= initial_y + 8; i += 4, j += 2)
									if (filled[i][j] == 'O') num++;
								Enemyscore[x][y] += DefenseScore[num];
							}
							blocks--;
							initial_x += 4;
							initial_y += 2;
						}
						blocks = end - begin + 1;
						initial_x = x - 20 + begin * 4;
						initial_y = y - 10 + begin * 2;
						// Check ATTACK for each block
						while (blocks > 0) {
							if ((filled[initial_x][initial_y] != 'O') && (filled[initial_x + 4][initial_y + 2] != 'O') && (filled[initial_x + 8][initial_y + 4] != 'O') &&
								(filled[initial_x + 12][initial_y + 6] != 'O') && (filled[initial_x + 16][initial_y + 8] != 'O')) {
								int num = 0;
								for (int i = initial_x, j = initial_y; i <= initial_x + 16, j <= initial_y + 8; i += 4, j += 2)
									if (filled[i][j] == 'X') num++;
								Enemyscore[x][y] += AttackScore[num];
							}
							blocks--;
							initial_x += 4;
							initial_y += 2;
						}
					}
					// Right_Left Diagonal
					{
						//Determine how many block to check
						int BottomBorder_of_Block = x + 16;
						int LeftBorder_of_Block = y - 8;
						int begin = 1;
						while ((BottomBorder_of_Block > 4 * n - 2) && (LeftBorder_of_Block < 1)) {
							begin++;
							BottomBorder_of_Block -= 4;
							LeftBorder_of_Block += 2;
						}
						int TopBorder_of_Block = x - 16;
						int RightBorder_of_Block = y + 8;
						int end = 5;
						while ((TopBorder_of_Block < 2) && (RightBorder_of_Block > 2 * n - 1) && (end >= 1)) {
							end--;
							TopBorder_of_Block += 4;
							RightBorder_of_Block -= 2;
						}

						// Number of blocks had to check
						int blocks = end - begin + 1;
						int initial_x = x + 20 - begin * 4;
						int initial_y = y - 10 + begin * 2;
						// Check DEFENSE for each block
						while (blocks > 0) {
							if ((filled[initial_x][initial_y] != 'X') && (filled[initial_x - 4][initial_y + 2] != 'X') && (filled[initial_x - 8][initial_y + 4] != 'X') &&
								(filled[initial_x - 12][initial_y + 6] != 'X') && (filled[initial_x - 16][initial_y + 8] != 'X')) {
								int num = 0;
								for (int i = initial_x, j = initial_y; i >= initial_x - 16, j <= initial_y + 8; i -= 4, j += 2)
									if (filled[i][j] == 'O') num++;
								Enemyscore[x][y] += DefenseScore[num];
							}
							blocks--;
							initial_x -= 4;
							initial_y += 2;
						}
						blocks = end - begin + 1;
						initial_x = x + 20 - begin * 4;
						initial_y = y - 10 + begin * 2;
						// Check ATTACK for each block
						while (blocks > 0) {
							if ((filled[initial_x][initial_y] != 'O') && (filled[initial_x - 4][initial_y + 2] != 'O') && (filled[initial_x - 8][initial_y + 4] != 'O') &&
								(filled[initial_x - 12][initial_y + 6] != 'O') && (filled[initial_x - 16][initial_y + 8] != 'O')) {
								int num = 0;
								for (int i = initial_x, j = initial_y; i >= initial_x - 16, j <= initial_y + 8; i -= 4, j += 2)
									if (filled[i][j] == 'X') num++;
								Enemyscore[x][y] += AttackScore[num];
							}
							blocks--;
							initial_x -= 4;
							initial_y += 2;
						}
					}
				}
	}
	// Enemy move
	int maxEnemyScore = 0;
	int locaX = 0, locaY = 0;
	for (int i = 2; i < 64; i += 4)
		for (int j = 1; j < 32;j += 2)
			if (maxEnemyScore <= Enemyscore[i][j]) {
				maxEnemyScore = Enemyscore[i][j];
				locaX = i; locaY = j;
			}
	// Minus the enemy score because enemy want to reduce the effective of computer move
	mark -= Enemyscore[locaX][locaY];
	Score_of_Cell(16);
	// Find the best cell in this move
	int maxScore = 0, max1Score = 0, max2Score = 0;
	int locaX1 = 0, locaY1 = 0;
	int locaX2 = 0, locaY2 = 0;
	for (int i = 2; i < 64; i += 4)
		for (int j = 1; j < 32;j += 2)
			if (max1Score <= score[i][j]) {
				max1Score = score[i][j];
				locaX1 = i; locaY1 = j;
			}
	for (int i = 2; i < 64; i += 4)
		for (int j = 1; j < 32;j += 2)
			if ((max2Score <= score[i][j]) && (max1Score>=score[i][j])) {
				max2Score = score[i][j];
				locaX2 = i; locaY2 = j;
			}
	// Find the better move to play
	int attempt1 = test_Move(locaX1, locaY1);
	int attempt2 = test_Move(locaX2, locaY2);
	if (attempt1 > attempt2) {
		locaX = locaX1; locaY = locaY1;
	}
	else {
		locaX = locaX2; locaY = locaY2;
	}
	// Plus cell score to determine how effective this test move is
	mark += score[locaX][locaY];
	filled[x][y] = ' ';
	return mark;
}
int test_Move(int x, int y) {
	int mark = score[x][y];
	filled[x][y] = 'O';

	// Enemy score cell
	{
		int n = 16;
		// To evalue the score of each cell for the move
		int DefenseScore[5] = { 0, 2, 14, 98, 686 };
		int AttackScore[5] = { 0, 1, 8, 64, 512 };

		for (int i = 2; i < 64; i += 4)
			for (int j = 1; j < 32;j += 2) Enemyscore[i][j] = 0;

		// evaluate the empty cell
		for (int x = 2; x < n * 4; x += 4)
			for (int y = 1; y < n * 2; y += 2)
				if (filled[x][y] == ' ') {

					//Vertical 
					{
						//Determine how many block to check
						int LeftBorder_of_Block = y - 8;
						int begin = 1;
						while (LeftBorder_of_Block < 1) {
							begin++;
							LeftBorder_of_Block += 2;
						}
						int RightBorder_of_Block = y + 8;
						int end = 5;
						while ((RightBorder_of_Block > 2 * n - 1) && (end >= 1)) {
							end--;
							RightBorder_of_Block -= 2;
						}

						// Number of blocks had to check
						int blocks = end - begin + 1;
						int initial = y - 10 + begin * 2;		//
						//	Check DEFENSE for each block
						while (blocks > 0) {
							if ((filled[x][initial] != 'X') && (filled[x][initial + 2] != 'X') && (filled[x][initial + 4] != 'X') &&
								(filled[x][initial + 6] != 'X') && (filled[x][initial + 8] != 'X')) {
								int num = 0;
								for (int i = initial; i <= initial + 8; i += 2)
									if (filled[x][i] == 'O') num++;
								Enemyscore[x][y] += DefenseScore[num];
							}
							blocks--;
							initial += 2;
						}
						blocks = end - begin + 1;
						initial = y - 10 + begin * 2;
						//	Check ATTACK of each block
						while (blocks > 0) {
							if ((filled[x][initial] != 'O') && (filled[x][initial + 2] != 'O') && (filled[x][initial + 4] != 'O') &&
								(filled[x][initial + 6] != 'O') && (filled[x][initial + 8] != 'O')) {
								int num = 0;
								for (int i = initial; i <= initial + 8; i += 2)
									if (filled[x][i] == 'X') num++;
								Enemyscore[x][y] += AttackScore[num];
							}
							blocks--;
							initial += 2;
						}
					}
					// Horizontal
					{
						//Determine how many block to check
						int TopBorder_of_Block = x - 16;
						int begin = 1;
						while (TopBorder_of_Block < 2) {
							begin++;
							TopBorder_of_Block += 4;
						}
						int BottomBorder_of_Block = x + 16;
						int end = 5;
						while ((BottomBorder_of_Block > 4 * n - 2) && (end >= 1)) {
							end--;
							BottomBorder_of_Block -= 4;
						}

						// Number of blocks had to check
						int blocks = end - begin + 1;
						int initial = x - 20 + begin * 4;		//
						//	Check DEFENSE for each block
						while (blocks > 0) {
							if ((filled[initial][y] != 'X') && (filled[initial + 4][y] != 'X') && (filled[initial + 8][y] != 'X') &&
								(filled[initial + 12][y] != 'X') && (filled[initial + 16][y] != 'X')) {
								int num = 0;
								for (int i = initial; i <= initial + 16; i += 4)
									if (filled[i][y] == 'O') num++;
								Enemyscore[x][y] += DefenseScore[num];
							}
							blocks--;
							initial += 4;
						}
						blocks = end - begin + 1;
						initial = x - 20 + begin * 4;		//
						//	Check ATTACK for each block
						while (blocks > 0) {
							if ((filled[initial][y] != 'O') && (filled[initial + 4][y] != 'O') && (filled[initial + 8][y] != 'O') &&
								(filled[initial + 12][y] != 'O') && (filled[initial + 16][y] != 'O')) {
								int num = 0;
								for (int i = initial; i <= initial + 16; i++)
									if (filled[i][y] == 'X') num++;
								Enemyscore[x][y] += AttackScore[num];
							}
							blocks--;
							initial += 4;
						}
					}
					// Left_Right Diagonal 
					{
						//Determine how many block to check
						int TopBorder_of_Block = x - 16;
						int LeftBorder_of_Block = y - 8;
						int begin = 1;
						while ((TopBorder_of_Block < 2) && (LeftBorder_of_Block < 1)) {
							begin++;
							TopBorder_of_Block += 4;
							LeftBorder_of_Block += 2;
						}
						int BottomBorder_of_Block = x + 16;
						int RightBorder_of_Block = y + 8;
						int end = 5;
						while ((BottomBorder_of_Block > 4 * n - 2) && (RightBorder_of_Block > 2 * n - 1) && (end >= 1)) {
							end--;
							BottomBorder_of_Block -= 4;
							RightBorder_of_Block -= 2;
						}

						// Number of blocks had to check
						int blocks = end - begin + 1;
						int initial_x = x - 20 + begin * 4;
						int initial_y = y - 10 + begin * 2;
						// Check DEFENSE for each block
						while (blocks > 0) {
							if ((filled[initial_x][initial_y] != 'X') && (filled[initial_x + 4][initial_y + 2] != 'X') && (filled[initial_x + 8][initial_y + 4] != 'X') &&
								(filled[initial_x + 12][initial_y + 6] != 'X') && (filled[initial_x + 16][initial_y + 8] != 'X')) {
								int num = 0;
								for (int i = initial_x, j = initial_y; i <= initial_x + 16, j <= initial_y + 8; i += 4, j += 2)
									if (filled[i][j] == 'O') num++;
								Enemyscore[x][y] += DefenseScore[num];
							}
							blocks--;
							initial_x += 4;
							initial_y += 2;
						}
						blocks = end - begin + 1;
						initial_x = x - 20 + begin * 4;
						initial_y = y - 10 + begin * 2;
						// Check ATTACK for each block
						while (blocks > 0) {
							if ((filled[initial_x][initial_y] != 'O') && (filled[initial_x + 4][initial_y + 2] != 'O') && (filled[initial_x + 8][initial_y + 4] != 'O') &&
								(filled[initial_x + 12][initial_y + 6] != 'O') && (filled[initial_x + 16][initial_y + 8] != 'O')) {
								int num = 0;
								for (int i = initial_x, j = initial_y; i <= initial_x + 16, j <= initial_y + 8; i += 4, j += 2)
									if (filled[i][j] == 'X') num++;
								Enemyscore[x][y] += AttackScore[num];
							}
							blocks--;
							initial_x += 4;
							initial_y += 2;
						}
					}
					// Right_Left Diagonal
					{
						//Determine how many block to check
						int BottomBorder_of_Block = x + 16;
						int LeftBorder_of_Block = y - 8;
						int begin = 1;
						while ((BottomBorder_of_Block > 4 * n - 2) && (LeftBorder_of_Block < 1)) {
							begin++;
							BottomBorder_of_Block -= 4;
							LeftBorder_of_Block += 2;
						}
						int TopBorder_of_Block = x - 16;
						int RightBorder_of_Block = y + 8;
						int end = 5;
						while ((TopBorder_of_Block < 2) && (RightBorder_of_Block > 2 * n - 1) && (end >= 1)) {
							end--;
							TopBorder_of_Block += 4;
							RightBorder_of_Block -= 2;
						}

						// Number of blocks had to check
						int blocks = end - begin + 1;
						int initial_x = x + 20 - begin * 4;
						int initial_y = y - 10 + begin * 2;
						// Check DEFENSE for each block
						while (blocks > 0) {
							if ((filled[initial_x][initial_y] != 'X') && (filled[initial_x - 4][initial_y + 2] != 'X') && (filled[initial_x - 8][initial_y + 4] != 'X') &&
								(filled[initial_x - 12][initial_y + 6] != 'X') && (filled[initial_x - 16][initial_y + 8] != 'X')) {
								int num = 0;
								for (int i = initial_x, j = initial_y; i >= initial_x - 16, j <= initial_y + 8; i -= 4, j += 2)
									if (filled[i][j] == 'O') num++;
								Enemyscore[x][y] += DefenseScore[num];
							}
							blocks--;
							initial_x -= 4;
							initial_y += 2;
						}
						blocks = end - begin + 1;
						initial_x = x + 20 - begin * 4;
						initial_y = y - 10 + begin * 2;
						// Check ATTACK for each block
						while (blocks > 0) {
							if ((filled[initial_x][initial_y] != 'O') && (filled[initial_x - 4][initial_y + 2] != 'O') && (filled[initial_x - 8][initial_y + 4] != 'O') &&
								(filled[initial_x - 12][initial_y + 6] != 'O') && (filled[initial_x - 16][initial_y + 8] != 'O')) {
								int num = 0;
								for (int i = initial_x, j = initial_y; i >= initial_x - 16, j <= initial_y + 8; i -= 4, j += 2)
									if (filled[i][j] == 'X') num++;
								Enemyscore[x][y] += AttackScore[num];
							}
							blocks--;
							initial_x -= 4;
							initial_y += 2;
						}
					}
				}
	}
	// Enemy move
	int maxEnemyScore = 0;
	int locaX = 0, locaY = 0;
	for (int i = 2; i < 64; i += 4)
		for (int j = 1; j < 32;j += 2)
			if (maxEnemyScore <= Enemyscore[i][j]) {
				maxEnemyScore = Enemyscore[i][j];
				locaX = i; locaY = j;
			}
	// Minus the enemy score because enemy want to reduce the effective of computer move
	mark -= Enemyscore[locaX][locaY];
	Score_of_Cell(16);
	// Find the best cell in this move
	int maxScore = 0;
	for (int i = 2; i < 64; i += 4)
		for (int j = 1; j < 32;j += 2)
			if (maxScore <= score[i][j]) {
				maxScore = score[i][j];
				locaX = i; locaY = j;
			}
	// Plus cell score to determine how effective this test move is
	mark += score[locaX][locaY];
	filled[x][y] = ' ';
	return mark;
}
void Score_of_Cell(int n) {
	// To evalue the score of each cell for the move
	int AttackScore[5] = { 0, 2, 18, 162, 1458 };
	int DefenseScore[5] = { 0, 1, 9, 81, 729 };

	for (int i = 2; i < 64; i += 4)
		for (int j = 1; j < 32;j += 2) score[i][j] = 0;

	// evaluate the empty cell
	for (int x = 2; x < n * 4; x += 4)
		for (int y = 1; y < n * 2; y += 2)
			if (filled[x][y] == ' ') {

				//Vertical 
				{
					//Determine how many block to check
					int LeftBorder_of_Block = y - 8;
					int begin = 1;
					while (LeftBorder_of_Block < 1) {
						begin++;
						LeftBorder_of_Block += 2;
					}
					int RightBorder_of_Block = y + 8;
					int end = 5;
					while ((RightBorder_of_Block > 2 * n - 1) && (end >= 1)) {
						end--;
						RightBorder_of_Block -= 2;
					}

					// Number of blocks had to check
					int blocks = end - begin + 1;
					int initial = y - 10 + begin * 2;		//
															//	Check ATTACK for each block
					while (blocks > 0) {
						if ((filled[x][initial] != 'X') && (filled[x][initial + 2] != 'X') && (filled[x][initial + 4] != 'X') &&
							(filled[x][initial + 6] != 'X') && (filled[x][initial + 8] != 'X')) {
							int num = 0;
							for (int i = initial; i <= initial + 8; i += 2)
								if (filled[x][i] == 'O') num++;
							score[x][y] += AttackScore[num];
						}
						blocks--;
						initial += 2;
					}
					blocks = end - begin + 1;
					initial = y - 10 + begin * 2;
					//	Check DEFENSE of each block
					while (blocks > 0) {
						if ((filled[x][initial] != 'O') && (filled[x][initial + 2] != 'O') && (filled[x][initial + 4] != 'O') &&
							(filled[x][initial + 6] != 'O') && (filled[x][initial + 8] != 'O')) {
							int num = 0;
							for (int i = initial; i <= initial + 8; i += 2)
								if (filled[x][i] == 'X') num++;
							score[x][y] += DefenseScore[num];
						}
						blocks--;
						initial += 2;
					}
				}
				// Horizontal
				{
					//Determine how many block to check
					int TopBorder_of_Block = x - 16;
					int begin = 1;
					while (TopBorder_of_Block < 2) {
						begin++;
						TopBorder_of_Block += 4;
					}
					int BottomBorder_of_Block = x + 16;
					int end = 5;
					while ((BottomBorder_of_Block > 4 * n - 2) && (end >= 1)) {
						end--;
						BottomBorder_of_Block -= 4;
					}

					// Number of blocks had to check
					int blocks = end - begin + 1;
					int initial = x - 20 + begin * 4;		//
															//	Check ATTACK for each block
					while (blocks > 0) {
						if ((filled[initial][y] != 'X') && (filled[initial + 4][y] != 'X') && (filled[initial + 8][y] != 'X') &&
							(filled[initial + 12][y] != 'X') && (filled[initial + 16][y] != 'X')) {
							int num = 0;
							for (int i = initial; i <= initial + 16; i += 4)
								if (filled[i][y] == 'O') num++;
							score[x][y] += AttackScore[num];
						}
						blocks--;
						initial += 4;
					}
					blocks = end - begin + 1;
					initial = x - 20 + begin * 4;		//
														//	Check DEFENSE for each block
					while (blocks > 0) {
						if ((filled[initial][y] != 'O') && (filled[initial + 4][y] != 'O') && (filled[initial + 8][y] != 'O') &&
							(filled[initial + 12][y] != 'O') && (filled[initial + 16][y] != 'O')) {
							int num = 0;
							for (int i = initial; i <= initial + 16; i++)
								if (filled[i][y] == 'X') num++;
							score[x][y] += DefenseScore[num];
						}
						blocks--;
						initial += 4;
					}
				}
				// Left_Right Diagonal 
				{
					//Determine how many block to check
					int TopBorder_of_Block = x - 16;
					int LeftBorder_of_Block = y - 8;
					int begin = 1;
					while ((TopBorder_of_Block < 2) && (LeftBorder_of_Block < 1)) {
						begin++;
						TopBorder_of_Block += 4;
						LeftBorder_of_Block += 2;
					}
					int BottomBorder_of_Block = x + 16;
					int RightBorder_of_Block = y + 8;
					int end = 5;
					while ((BottomBorder_of_Block > 4 * n - 2) && (RightBorder_of_Block > 2 * n - 1) && (end >= 1)) {
						end--;
						BottomBorder_of_Block -= 4;
						RightBorder_of_Block -= 2;
					}

					// Number of blocks had to check
					int blocks = end - begin + 1;
					int initial_x = x - 20 + begin * 4;
					int initial_y = y - 10 + begin * 2;
					// Check ATTACK for each block
					while (blocks > 0) {
						if ((filled[initial_x][initial_y] != 'X') && (filled[initial_x + 4][initial_y + 2] != 'X') && (filled[initial_x + 8][initial_y + 4] != 'X') &&
							(filled[initial_x + 12][initial_y + 6] != 'X') && (filled[initial_x + 16][initial_y + 8] != 'X')) {
							int num = 0;
							for (int i = initial_x, j = initial_y; i <= initial_x + 16, j <= initial_y + 8; i += 4, j += 2)
								if (filled[i][j] == 'O') num++;
							score[x][y] += AttackScore[num];
						}
						blocks--;
						initial_x += 4;
						initial_y += 2;
					}
					blocks = end - begin + 1;
					initial_x = x - 20 + begin * 4;
					initial_y = y - 10 + begin * 2;
					// Check DEFENSE for each block
					while (blocks > 0) {
						if ((filled[initial_x][initial_y] != 'O') && (filled[initial_x + 4][initial_y + 2] != 'O') && (filled[initial_x + 8][initial_y + 4] != 'O') &&
							(filled[initial_x + 12][initial_y + 6] != 'O') && (filled[initial_x + 16][initial_y + 8] != 'O')) {
							int num = 0;
							for (int i = initial_x, j = initial_y; i <= initial_x + 16, j <= initial_y + 8; i += 4, j += 2)
								if (filled[i][j] == 'X') num++;
							score[x][y] += DefenseScore[num];
						}
						blocks--;
						initial_x += 4;
						initial_y += 2;
					}
				}
				// Right_Left Diagonal
				{
					//Determine how many block to check
					int BottomBorder_of_Block = x + 16;
					int LeftBorder_of_Block = y - 8;
					int begin = 1;
					while ((BottomBorder_of_Block > 4 * n - 2) && (LeftBorder_of_Block < 1)) {
						begin++;
						BottomBorder_of_Block -= 4;
						LeftBorder_of_Block += 2;
					}
					int TopBorder_of_Block = x - 16;
					int RightBorder_of_Block = y + 8;
					int end = 5;
					while ((TopBorder_of_Block < 2) && (RightBorder_of_Block > 2 * n - 1) && (end >= 1)) {
						end--;
						TopBorder_of_Block += 4;
						RightBorder_of_Block -= 2;
					}

					// Number of blocks had to check
					int blocks = end - begin + 1;
					int initial_x = x + 20 - begin * 4;
					int initial_y = y - 10 + begin * 2;
					// Check ATTACK for each block
					while (blocks > 0) {
						if ((filled[initial_x][initial_y] != 'X') && (filled[initial_x - 4][initial_y + 2] != 'X') && (filled[initial_x - 8][initial_y + 4] != 'X') &&
							(filled[initial_x - 12][initial_y + 6] != 'X') && (filled[initial_x - 16][initial_y + 8] != 'X')) {
							int num = 0;
							for (int i = initial_x, j = initial_y; i >= initial_x - 16, j <= initial_y + 8; i -= 4, j += 2)
								if (filled[i][j] == 'O') num++;
							score[x][y] += AttackScore[num];
						}
						blocks--;
						initial_x -= 4;
						initial_y += 2;
					}
					blocks = end - begin + 1;
					initial_x = x + 20 - begin * 4;
					initial_y = y - 10 + begin * 2;
					// Check DEFENSE for each block
					while (blocks > 0) {
						if ((filled[initial_x][initial_y] != 'O') && (filled[initial_x - 4][initial_y + 2] != 'O') && (filled[initial_x - 8][initial_y + 4] != 'O') &&
							(filled[initial_x - 12][initial_y + 6] != 'O') && (filled[initial_x - 16][initial_y + 8] != 'O')) {
							int num = 0;
							for (int i = initial_x, j = initial_y; i >= initial_x - 16, j <= initial_y + 8; i -= 4, j += 2)
								if (filled[i][j] == 'X') num++;
							score[x][y] += DefenseScore[num];
						}
						blocks--;
						initial_x -= 4;
						initial_y += 2;
					}
				}
			}
}
int Check_Win(char a[][32], int x, int y, int n, int m) {
	int check, curX, curY, top, bottom, left, right;
	if (a[x][y] == 'X' || a[x][y] == 'O') {

		// Check Vertical
		{
			check = 1; top = y; bottom = y;
			curX = x; curY = y;
			while ((curY - 2) >= 1 && (a[x][curY - 2] == a[x][curY])) {
				check++;
				curY -= 2;
				if (curY - 2 >= 1) top = curY - 2;
			}
			curX = x; curY = y;
			while ((curY + 2) <= 2 * m - 1 && (a[x][curY + 2] == a[x][curY])) {
				check++;
				curY += 2;
				if (curY + 2 <= 2 * m - 1)bottom = curY + 2;
			}
			if (check == 5)
				if ((a[x][top] != ' ') && (a[x][top] != a[x][y]) && (a[x][bottom] != ' ') && (a[x][bottom] != a[x][y]))
					return 1;
		}

		// Check Horizontal
		{
			check = 1; left = x; right = x;
			curX = x; curY = y;
			while ((curX - 4) >= 2 && (a[curX - 4][y] == a[curX][y])) {
				check++;
				curX -= 4;
				if (curX - 4 >= 2) left = curX - 4;
			}
			curX = x; curY = y;
			while ((curX + 4) <= 4 * n - 2 && (a[curX + 4][y] == a[curX][y])) {
				check++;
				curX += 4;
				if (curX + 4 <= 4 * n - 2) right = curX + 4;
			}
			if (check == 5)
				if ((a[left][y] != ' ') && (a[left][y] != a[x][y]) && (a[right][y] != ' ') && (a[right][y] != a[x][y]))
					return 1;
		}

		// Check Left_Right Diagonal
		{
			check = 1;
			curX = x; curY = y;
			while ((curX - 4) >= 2 && (curY - 2) >= 1 && (a[curX - 4][curY - 2] == a[curX][curY])) {
				check++;
				curX -= 4;
				curY -= 2;
			}
			curX = x; curY = y;
			while ((curX + 4) <= 4 * n - 2 && (curY + 2) <= 2 * m - 1 && (a[curX + 4][curY + 2] == a[curX][curY])) {
				check++;
				curX += 4;
				curY += 2;
			}
			if (check == 5) return 1;
		}

		// Check Right_Left Diagonal
		{
			check = 1;
			curX = x; curY = y;
			while ((curX - 4) >= 2 && (curY + 2) <= 2 * m - 1 && (a[curX - 4][curY + 2] == a[curX][curY])) {
				check++;
				curX -= 4;
				curY += 2;
			}
			curX = x; curY = y;
			while ((curX + 4) <= 4 * n - 2 && (curY - 2) >= 1 && (a[curX + 4][curY - 2] == a[curX][curY])) {
				check++;
				curX += 4;
				curY -= 2;
			}
			if (check == 5) return 1;
		}
		if (check != 5) return 0;
	}
}


/*
Have not finish Check_Win yet
2 diagonals had not check for 2 heads intercepted

Need to upgrade the computer move

					Update 23h45 Tues 23.10.2018
*/