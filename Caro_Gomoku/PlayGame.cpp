#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "console.h"
#include "Animation.h"
#include "StartScreen.h"
#include "Option.h"

using namespace std;

#define ConsoleWidth  144
#define ConsoleHeight 62
#define Color 15

enum Control { UP, DOWN, LEFT, RIGHT, X, O, ENTER, ESC, SPACE, UNDO, SAVE };
Control control(int z) {
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
	else if (z == 85 || z == 117) return UNDO;		// U & u
	else if (z == 90 || z == 122) return SAVE;		// Z & z 
}

int Start_Game(char a[][42], int &row, int &column, char &charX, char &charO, int &PvP, int &PvC,
	int &Easy, int &wEasy, int &Medium, int &wMedium, int &Hard, int &wHard) {
	while (1) {
		Clear_Screen();
		int selected = Select_Mode();			// Choose which mode to play
		switch (selected) {
		case 1:
			clrscr();
			system("Color 7");
			Board(row, column);
			PP_Mode(a, row, column, 0, charX, charO, PvP);
			break;
		case 2:
			PC_Mode(a, row, column, charX, charO, PvC, Easy, wEasy, Medium, wMedium, Hard, wHard);
			break;
		case 3: return 0;						// Exit Start game
		}
	}
}
int Select_Mode() {
	int n = 4, tt = 0, mau[5];
	for (int i = 0; i < 5; i++) mau[i] = Color;
	while (1) {
		int x, y = 24;
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
		Control moving = control(z);
		switch (moving) {
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
int Difficulty() {
	int n = 5, tt = 0, mau[6];
	for (int i = 0; i < 6; i++) mau[i] = Color;
	while (1) {
		int x, y = 24;
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
		Control moving = control(z);
		switch (moving) {
		case UP:
			if (tt == 1 || tt == 0) tt = n - 1;
			else --tt;
			break;
		case DOWN:
			if (tt == n - 1) tt = 1;
			else ++tt;
			break;
		case ENTER:
			system("Color 7");
			clrscr();
			return tt;
		}
		for (int i = 0; i < n; i++) mau[i] = Color;
		mau[tt] = 124;
	}
}
int Player_turn(char a[][42], int &row, int &column, int &x, int &y, int n, int m, int &step, int mode,
	int &PlayerX, int &PlayerY, int &PcX, int &PcY, char &charX, char &charO, int score[][42], int Enemyscore[][42]) {
	// Function name and parameter names told everythings, so don't have anything to say about this
	int z = _getch();
	Control Moving = control(z);
	switch (Moving) {
	case UP:
		if (y == 1) y = m - 1;
		else y -= 2;
		break;
	case DOWN:
		if (y == m - 1) y = 1;
		else y += 2;
		break;
	case LEFT:
		if (x == 2) x = n - 2;
		else x -= 4;
		break;
	case RIGHT:
		if (x == n - 2) x = 2;
		else x += 4;
		break;
	case X:
		if (step % 2 != 0) {
			if (a[x][y] == ' ') {
				PlayerX = x; PlayerY = y;
				TextColor(124);
				gotoXY(x, y);
				a[x][y] = charX;
				cout << a[x][y] << endl;
				step++;
			}
		}
		break;
	case O:
		if (step % 2 == 0) {
			if (a[x][y] == ' ') {
				PlayerX = x; PlayerY = y;
				TextColor(122);
				gotoXY(x, y);
				a[x][y] = charO;
				cout << a[x][y] << endl;
				step++;
			}
		}
		break;
	case SPACE:
		if (step % 2 != 0) {
			if (a[x][y] == ' ') {
				PlayerX = x; PlayerY = y;
				TextColor(124);
				gotoXY(x, y);
				a[x][y] = charX;
				cout << a[x][y] << endl;
				step++;
			}
		}
		else {
			if (a[x][y] == ' ') {
				PlayerX = x; PlayerY = y;
				TextColor(122);
				gotoXY(x, y);
				a[x][y] = charO;
				cout << a[x][y] << endl;
				step++;
			}
		}
		break;
	case UNDO:
		Undo(a, row, column, mode, step, PlayerX, PlayerY, PcX, PcY, charX, charO, score, Enemyscore);
		break;
	case SAVE:
		Save_Game(a, row, column);
		break;
	case ESC:
		return 0;
	}
}
int PP_Mode(char a[][42], int &row, int &column, int load, char &charX, char &charO, int &PvP) {
	int n = 4 * column, m = 2 * row;
	int score[84][42], Enemyscore[84][42];
	int x, y, color, PlayerX, PlayerY, PcX, PcY;
	int isWin, CurX, CurY;

	for (int i = 2; i < n; i += 4)
		for (int j = 1; j < m; j += 2)
			a[i][j] = ' ';					// initialize the value of array before playing

	// load saved game
	// if this is a new game, so the block of lines 530-676 will not exercuted
	ifstream loadgame;
	if (load != 0) {
		switch (load) {
		case 1:
			loadgame.open("Game_1.txt");
			break;
		case 2:
			loadgame.open("Game_2.txt");
			break;
		case 3:
			loadgame.open("Game_3.txt");
			break;
		case 4:
			loadgame.open("Game_4.txt");
			break;
		case 5:
			loadgame.open("Game_5.txt");
			break;
		case 6:
			loadgame.open("Game_6.txt");
			break;
		case 7:
			loadgame.open("Game_7.txt");
			break;
		case 8:
			system("Color 7");
			return 0;
		}
		int ahi;
		loadgame >> ahi;
		char c;
		int i, j;
		while (!loadgame.eof()) {
			loadgame >> c >> i >> j;
			gotoXY(i, j);
			if (c == charX) {
				TextColor(12);
				cout << c << endl;
			}
			else if (c == charO) {
				TextColor(10);
				cout << c << endl;
			}
			a[i][j] = c;
		}
	}
	loadgame.close();

	// The initial position on board
	if (column % 2 == 0) {
		x = column * 2 - 2;
		y = row + 1;
	}
	else {
		x = column * 2;
		y = row;
	}
	int step = 1;						// count the ordinal of steps
	while (1) {
		CurX = x; CurY = y;
		// Check win
		isWin = Check_Win(a, x, y, row, column, charX, charO);
		if (isWin == 1) {
			if (load == 0) PvP++;
			EoBietCaiGiNua(0);
			// Delete the mouse
			if (a[x][y] == charX) {
				TextColor(12);
				gotoXY(x, y);
				cout << a[x][y] << endl;
			}
			else if (a[x][y] == charO) {
				TextColor(10);
				gotoXY(x, y);
				cout << a[x][y] << endl;
			}
			// Win Animation
			if (step % 2 != 0) Win_Animation(2);		// Player 2 win
			else Win_Animation(1);						// Player 1 win
			gotoXY(99, 18);
			cout << "Enter to return to menu";
			while (1) {
				int zz = _getch();
				Control Choose = control(zz);
				if (Choose == ENTER) {
					clrscr();
					isWin = 0;
					return 0;
				}
			}
		}
		EoBietCaiGiNua(1);
		// Playing Turn
		int esc = Player_turn(a, row, column, x, y, n, m, step, 0, PlayerX, PlayerY, PcX, PcY, charX, charO, score, Enemyscore);
		if (esc == 0) return 0;

		// change color previous step
		if (CurX != x || CurY != y) {
			if (a[CurX][CurY] == charX) color = 12;
			else if (a[CurX][CurY] == charO) color = 10;
			else color = 0;
			TextColor(color);
			gotoXY(CurX, CurY);
			cout << a[CurX][CurY] << endl;
		}
		//change color present step
		if (a[x][y] == charX) color = 124;
		else if (a[x][y] == charO) color = 122;
		else color = 119;
		TextColor(color);
		gotoXY(x, y);
		cout << a[x][y] << endl;

	}
}
int PC_Mode(char a[][42], int &row, int &column, char &charX, char &charO, int &PvC,
	int &Easy, int &wEasy, int &Medium, int &wMedium, int &Hard, int &wHard) {
	while (1) {
		int score[84][42];						// Score array for computer to evaluate 
		int Enemyscore[84][42];					// Score of player for computer to evaluate
		Clear_Screen();
		int choose = Difficulty();				// Choose the difficulty user want to play
		switch (choose) {
		case 1:
			system("Color 7");
			clrscr();
			Board(row, column);
			Easy_mode(a, row, column, score, Enemyscore, charX, charO, PvC, Easy, wEasy);
			break;
		case 2:
			system("Color 7");
			clrscr();
			Board(row, column);
			Medium_mode(a, row, column, score, Enemyscore, charX, charO, PvC, Medium, wMedium);
			break;
		case 3:
			system("Color 7");
			clrscr();
			Board(row, column);
			Hard_mode(a, row, column, score, Enemyscore, charX, charO, PvC, Hard, wHard);
			break;
		case 4:
			system("Color 7");
			return 0;
		}
	}
}
int Easy_mode(char a[][42], int &row, int &column, int score[][42], int Enemyscore[][42], char &charX, char &charO, int &PvC, int &Easy, int &wEasy) {
	int m = 2 * row, n = 4 * column;
	int x, y, color, PlayerX, PlayerY, PcX, PcY;
	int isWin, CurX, CurY;
	// The initial poisiton on board
	if (column % 2 == 0) {
		x = column * 2 - 2;
		y = row + 1;
	}
	else {
		x = column * 2;
		y = row;
	}
	for (int i = 2; i < n; i += 4)
		for (int j = 1; j < m; j += 2)
			a[i][j] = ' ';					// initialize the value of array before playing
	int step = 1;			// count the ordinal of steps
	while (1) {
		CurX = x; CurY = y;
		int locaX = 0, locaY = 0;			// Defined as a position that PC choose to play

											// Check win
		int isWin = Check_Win(a, x, y, row, column, charX, charO);
		if (isWin == 1) {
			PvC++; Easy++;
			EoBietCaiGiNua(0);
			// Delete the mouse
			if (a[x][y] == charX) {
				TextColor(12);
				gotoXY(x, y);
				cout << a[x][y] << endl;
			}
			else if (a[x][y] == charO) {
				TextColor(10);
				gotoXY(x, y);
				cout << a[x][y] << endl;
			}
			// Win Animation
			if (step % 2 == 0) {
				wEasy++;
				Win_Animation(0);
			}											// You win
			else Lose_Animation();						// You lose :)))
			gotoXY(97, 15);
			cout << "Enter to return to menu";
			while (1) {
				int zz = _getch();
				Control Choose = control(zz);
				if (Choose == ENTER) {
					clrscr();
					isWin = 0;
					return 0;
				}
			}
		}
		EoBietCaiGiNua(1);
		//	Player turn
		if (step % 2 != 0) {
			int esc = Player_turn(a, row, column, x, y, n, m, step, 1, PlayerX, PlayerY, PcX, PcY, charX, charO, score, Enemyscore);
			if (esc == 0) return 0;
		}
		//	Computer turn
		else {
			// Choose max-score cell to enter
			int maxScore = 0;
			for (int i = 2; i < n; i += 4)				// looking for the cell that has max-score and choose it :)
				for (int j = 1; j < m; j += 2)
					if (maxScore <= score[i][j]) {
						maxScore = score[i][j];
						locaX = i; locaY = j;
					}
			if (step == 2) {							// ahihi :))
				locaX = CurX + 4;
				locaY = CurY;
			}
			PcX = locaX; PcY = locaY;
			TextColor(122);
			gotoXY(locaX, locaY);
			a[locaX][locaY] = charO;
			cout << a[locaX][locaY] << endl;
			step++;
			x = locaX; y = locaY;
		}
		Score_of_Cell(a, row, column, charX, charO, score, Enemyscore);		// Evaluate the value of empty cell after each turn to prepare for next turn

																			// change color previous step
		if (CurX != x || CurY != y) {
			if (a[CurX][CurY] == charX) color = 12;
			else if (a[CurX][CurY] == charO) color = 10;
			else color = 0;
			TextColor(color);
			gotoXY(CurX, CurY);
			cout << a[CurX][CurY] << endl;
		}
		//change color present step
		if (a[x][y] == charX) color = 124;
		else if (a[x][y] == charO) color = 122;
		else color = 119;
		TextColor(color);
		gotoXY(x, y);
		cout << a[x][y] << endl;
	}
	return 0;
}
int Medium_mode(char a[][42], int &row, int &column, int score[][42], int Enemyscore[][42], char &charX, char &charO, int &PvC, int &Medium, int &wMedium) {
	int m = 2 * row, n = 4 * column;
	int x, y, color, PlayerX, PlayerY, PcX, PcY;
	int isWin, CurX, CurY;
	// The initial position on board
	if (column % 2 == 0) {
		x = column * 2 - 2;
		y = row + 1;
	}
	else {
		x = column * 2;
		y = row;
	}
	for (int i = 2; i < n; i += 4)
		for (int j = 1; j < m; j += 2)
			a[i][j] = ' ';				// initialize the value of array before playing
	int step = 1;				// count the ordinal of steps
	while (1) {
		CurX = x; CurY = y;
		int locaX = 0, locaY = 0;				// Defined as a position that PC choose to play
		int locaX1 = 0, locaY1 = 0;				// Choose 2 cells to check which is better
		int locaX2 = 0, locaY2 = 0;

		// Check win
		int isWin = Check_Win(a, x, y, row, column, charX, charO);
		if (isWin == 1) {
			PvC++; Medium++;
			EoBietCaiGiNua(0);
			// Delete the mouse
			if (a[x][y] == charX) {
				TextColor(12);
				gotoXY(x, y);
				cout << a[x][y] << endl;
			}
			else if (a[x][y] == charO) {
				TextColor(10);
				gotoXY(x, y);
				cout << a[x][y] << endl;
			}
			// Win Animation
			if (step % 2 == 0) {
				wMedium++;
				Win_Animation(0);
			}											// You win
			else Lose_Animation();						// You lose :)))
			gotoXY(97, 15);
			cout << "Enter to return to menu";
			while (1) {
				int zz = _getch();
				Control Choose = control(zz);
				if (Choose == ENTER) {
					clrscr();
					isWin = 0;
					return 0;
				}
			}
		}
		EoBietCaiGiNua(1);
		//	Player turn
		if (step % 2 != 0) {
			int esc = Player_turn(a, row, column, x, y, n, m, step, 1, PlayerX, PlayerY, PcX, PcY, charX, charO, score, Enemyscore);
			if (esc == 0) return 0;
		}
		//	Computer turn
		else {
			// Choose max-score cell to enter
			int max1Score = 0;						// Find the first cell
			for (int i = 2; i < n; i += 4)
				for (int j = 1; j < m;j += 2)
					if (max1Score <= score[i][j]) {
						max1Score = score[i][j];
						locaX1 = i; locaY1 = j;
					}
			int max2Score = 0;						// Find the second cell
			for (int i = 2; i < n; i += 4)
				for (int j = 1; j < m;j += 2)
					if ((max2Score <= score[i][j]) && (max1Score >= score[i][j])) {
						max2Score = score[i][j];
						locaX2 = i; locaY2 = j;
					}
			// Find the better control to play
			// Appreciate 2 cells to play by assume the user's control in next turn
			int attempt1 = test_Move(a, locaX1, locaY1, row, column, score, Enemyscore, charX, charO);
			int attempt2 = test_Move(a, locaX2, locaY2, row, column, score, Enemyscore, charX, charO);
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
			PcX = locaX; PcY = locaY;
			TextColor(122);
			gotoXY(locaX, locaY);
			a[locaX][locaY] = charO;
			cout << a[locaX][locaY] << endl;
			step++;
			x = locaX; y = locaY;
		}
		Score_of_Cell(a, row, column, charX, charO, score, Enemyscore);			// Evaluate the score of empty cells in order to prepare for next turn

																				// change color previous step
		if (CurX != x || CurY != y) {
			if (a[CurX][CurY] == charX) color = 12;
			else if (a[CurX][CurY] == charO) color = 10;
			else color = 0;
			TextColor(color);
			gotoXY(CurX, CurY);
			cout << a[CurX][CurY] << endl;
		}
		//change color present step
		if (a[x][y] == charX) color = 124;
		else if (a[x][y] == charO) color = 122;
		else color = 119;
		TextColor(color);
		gotoXY(x, y);
		cout << a[x][y] << endl;
	}
	return 0;
}
int Hard_mode(char a[][42], int &row, int &column, int score[][42], int Enemyscore[][42], char &charX, char &charO, int &PvC, int &Hard, int &wHard) {
	int m = 2 * row, n = 4 * column;
	int x, y, color, PlayerX, PlayerY, PcX, PcY;
	int isWin, CurX, CurY;
	// The initial position on board
	if (column % 2 == 0) {
		x = column * 2 - 2;
		y = row + 1;
	}
	else {
		x = column * 2;
		y = row;
	}
	for (int i = 2; i < n; i += 4)
		for (int j = 1; j < m; j += 2)
			a[i][j] = ' ';						// Initialize the value of array before playing

	int step = 1;				// count the ordinal of steps
	while (1) {
		CurX = x; CurY = y;
		int locaX = 0, locaY = 0;				// Defined as a position that PC choose to play
		int locaX1 = 0, locaY1 = 0;				// Choose 2 cells to check which is better
		int locaX2 = 0, locaY2 = 0;

		// Check win
		int isWin = Check_Win(a, x, y, row, column, charX, charO);
		if (isWin == 1) {
			PvC++; Hard++;
			EoBietCaiGiNua(0);
			// Delete the mouse
			if (a[x][y] == charX) {
				TextColor(12);
				gotoXY(x, y);
				cout << a[x][y] << endl;
			}
			else if (a[x][y] == charO) {
				TextColor(10);
				gotoXY(x, y);
				cout << a[x][y] << endl;
			}
			// Win Animation
			if (step % 2 == 0) {
				wHard++;
				Win_Animation(0);
			}											// You win
			else Lose_Animation();						// You lose :)))
			gotoXY(97, 18);
			cout << "Enter to return to menu";
			while (1) {
				int zz = _getch();
				Control Choose = control(zz);
				if (Choose == ENTER) {
					clrscr();
					isWin = 0;
					return 0;
				}
			}
		}
		EoBietCaiGiNua(1);
		//	Player turn
		if (step % 2 != 0) {
			int esc = Player_turn(a, row, column, x, y, n, m, step, 1, PlayerX, PlayerY, PcX, PcY, charX, charO, score, Enemyscore);
			if (esc == 0) return 0;
		}
		//	Computer turn
		else {
			// Choose max-score cell to enter
			int max1Score = 0;						// Find the first cell
			for (int i = 2; i < n; i += 4)
				for (int j = 1; j < m;j += 2)
					if (max1Score <= score[i][j]) {
						max1Score = score[i][j];
						locaX1 = i; locaY1 = j;
					}
			int max2Score = 0;						// Find the second cell
			for (int i = 2; i < n; i += 4)
				for (int j = 1; j < m;j += 2)
					if ((max2Score <= score[i][j]) && (max1Score >= score[i][j])) {
						max2Score = score[i][j];
						locaX2 = i; locaY2 = j;
					}
			// Find the better control to play
			// Appreciate 2 cells to play by assume the user's control in next turn then the best score at folloeing turn
			// Then add in all of score in these turn to evaluate the score for the cells that are checked
			int attempt1 = test_Move_High(a, locaX1, locaY1, row, column, score, Enemyscore, charX, charO);
			int attempt2 = test_Move_High(a, locaX2, locaY2, row, column, score, Enemyscore, charX, charO);
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
			PcX = locaX; PcY = locaY;
			TextColor(122);
			gotoXY(locaX, locaY);
			a[locaX][locaY] = charO;
			cout << a[locaX][locaY] << endl;
			step++;
			x = locaX; y = locaY;
		}
		Score_of_Cell(a, row, column, charX, charO, score, Enemyscore);			// Evaluate the score of empty cells in order to prepare for next turn

																				// change color previous step
		if (CurX != x || CurY != y) {
			if (a[CurX][CurY] == charX) color = 12;
			else if (a[CurX][CurY] == charO) color = 10;
			else color = 0;
			TextColor(color);
			gotoXY(CurX, CurY);
			cout << a[CurX][CurY] << endl;
		}

		//change color present step
		if (a[x][y] == charX) color = 124;
		else if (a[x][y] == charO) color = 122;
		else color = 119;
		TextColor(color);
		gotoXY(x, y);
		cout << a[x][y] << endl;
	}
	return 0;
}
int test_Move_High(char a[][42], int x, int y, int &row, int &column, int score[][42], int Enemyscore[][42], char &charX, char &charO) {
	int mark = score[x][y];
	a[x][y] = charO;
	// Enemy score cell
	Score_of_Enemy_Cell(a, row, column, charX, charO, score, Enemyscore);
	// Enemy control
	int maxEnemyScore = 0;
	int locaX = 0, locaY = 0;
	for (int i = 2; i < 4 * column; i += 4)
		for (int j = 1; j < 2 * row;j += 2)
			if (maxEnemyScore <= Enemyscore[i][j]) {
				maxEnemyScore = Enemyscore[i][j];
				locaX = i; locaY = j;
			}
	// Minus the enemy score because enemy want to reduce the effective of computer control
	mark -= Enemyscore[locaX][locaY];
	Score_of_Cell(a, row, column, charX, charO, score, Enemyscore);
	// Find the best cell in this control
	int maxScore = 0, max1Score = 0, max2Score = 0;
	int locaX1 = 0, locaY1 = 0;
	int locaX2 = 0, locaY2 = 0;
	for (int i = 2; i < 4 * column; i += 4)
		for (int j = 1; j < 2 * row;j += 2)
			if (max1Score <= score[i][j]) {
				max1Score = score[i][j];
				locaX1 = i; locaY1 = j;
			}
	for (int i = 2; i < 4 * column; i += 4)
		for (int j = 1; j < 2 * row;j += 2)
			if ((max2Score <= score[i][j]) && (max1Score >= score[i][j])) {
				max2Score = score[i][j];
				locaX2 = i; locaY2 = j;
			}
	// Find the better control to play
	int attempt1 = test_Move(a, locaX1, locaY1, row, column, score, Enemyscore, charX, charO);
	int attempt2 = test_Move(a, locaX2, locaY2, row, column, score, Enemyscore, charX, charO);
	if (attempt1 > attempt2) {
		locaX = locaX1; locaY = locaY1;
	}
	else {
		locaX = locaX2; locaY = locaY2;
	}
	// Plus cell score to determine how effective this test control is
	mark += score[locaX][locaY];
	a[x][y] = ' ';
	return mark;
}
int test_Move(char a[][42], int x, int y, int &row, int &column, int score[][42], int Enemyscore[][42], char &charX, char &charO) {
	int mark = score[x][y];
	a[x][y] = charO;

	// Enemy score cell
	Score_of_Enemy_Cell(a, row, column, charX, charO, score, Enemyscore);
	// Enemy control
	int maxEnemyScore = 0;
	int locaX = 0, locaY = 0;
	for (int i = 2; i < 4 * column; i += 4)
		for (int j = 1; j < 2 * row; j += 2)
			if (maxEnemyScore <= Enemyscore[i][j]) {
				maxEnemyScore = Enemyscore[i][j];
				locaX = i; locaY = j;
			}
	// Minus the enemy score because enemy want to reduce the effective of computer control
	mark -= Enemyscore[locaX][locaY];
	Score_of_Cell(a, row, column, charX, charO, score, Enemyscore);
	// Find the best cell in this control
	int maxScore = 0;
	for (int i = 2; i < 4 * column; i += 4)
		for (int j = 1; j < 2 * row;j += 2)
			if (maxScore <= score[i][j]) {
				maxScore = score[i][j];
				locaX = i; locaY = j;
			}
	// Plus cell score to determine how effective this test control is
	mark += score[locaX][locaY];
	a[x][y] = ' ';
	return mark;
}
void Score_of_Cell(char a[][42], int &row, int &column, char &charX, char &charO, int score[][42], int Enemyscore[][42]) {
	// To evaluate the score of each cell for the control
	int AttackScore[5] = { 0, 2, 18, 162, 1458 };
	int DefenseScore[5] = { 0, 1, 9, 81, 729 };
	for (int i = 2; i < column * 4; i += 4)
		for (int j = 1; j < row * 2;j += 2) score[i][j] = 0;

	// evaluate the empty cell
	for (int x = 2; x < column * 4; x += 4)
		for (int y = 1; y < row * 2; y += 2)
			if (a[x][y] == ' ') {
				//Vertical 
				{
					//Determine how many block to check
					int LeftBorder_of_Block = y - 8, RightBorder_of_Block = y + 8;
					int begin = 1, end = 5;
					while (LeftBorder_of_Block < 1) {
						begin++;
						LeftBorder_of_Block += 2;
					}
					while ((RightBorder_of_Block > 2 * row - 1) && (end >= 1)) {
						end--;
						RightBorder_of_Block -= 2;
					}

					// Number of blocks had to check
					int blocks = end - begin + 1;
					int initial = y - 10 + begin * 2;
					//	Check ATTACK for each block
					while (blocks > 0) {
						if ((a[x][initial] != charX) && (a[x][initial + 2] != charX) && (a[x][initial + 4] != charX) &&
							(a[x][initial + 6] != charX) && (a[x][initial + 8] != charX)) {
							int num = 0;
							for (int i = initial; i <= initial + 8; i += 2)
								if (a[x][i] == charO) num++;
							score[x][y] += AttackScore[num];
						}
						blocks--;
						initial += 2;
					}
					blocks = end - begin + 1;
					initial = y - 10 + begin * 2;
					//	Check DEFENSE of each block
					while (blocks > 0) {
						if ((a[x][initial] != charO) && (a[x][initial + 2] != charO) && (a[x][initial + 4] != charO) &&
							(a[x][initial + 6] != charO) && (a[x][initial + 8] != charO)) {
							int num = 0;
							for (int i = initial; i <= initial + 8; i += 2)
								if (a[x][i] == charX) num++;
							score[x][y] += DefenseScore[num];
						}
						blocks--;
						initial += 2;
					}
				}
				// Horizontal
				{
					//Determine how many block to check
					int TopBorder_of_Block = x - 16, BottomBorder_of_Block = x + 16;
					int begin = 1, end = 5;
					while (TopBorder_of_Block < 2) {
						begin++;
						TopBorder_of_Block += 4;
					}
					while ((BottomBorder_of_Block > 4 * column - 2) && (end >= 1)) {
						end--;
						BottomBorder_of_Block -= 4;
					}

					// Number of blocks had to check
					int blocks = end - begin + 1;
					int initial = x - 20 + begin * 4;
					//	Check ATTACK for each block
					while (blocks > 0) {
						if ((a[initial][y] != charX) && (a[initial + 4][y] != charX) && (a[initial + 8][y] != charX) &&
							(a[initial + 12][y] != charX) && (a[initial + 16][y] != charX)) {
							int num = 0;
							for (int i = initial; i <= initial + 16; i += 4)
								if (a[i][y] == charO) num++;
							score[x][y] += AttackScore[num];
						}
						blocks--;
						initial += 4;
					}
					blocks = end - begin + 1;
					initial = x - 20 + begin * 4;		//
														//	Check DEFENSE for each block
					while (blocks > 0) {
						if ((a[initial][y] != charO) && (a[initial + 4][y] != charO) && (a[initial + 8][y] != charO) &&
							(a[initial + 12][y] != charO) && (a[initial + 16][y] != charO)) {
							int num = 0;
							for (int i = initial; i <= initial + 16; i++)
								if (a[i][y] == charX) num++;
							score[x][y] += DefenseScore[num];
						}
						blocks--;
						initial += 4;
					}
				}
				// Left_Right Diagonal 
				{
					//Determine how many block to check
					int TopBorder_of_Block = x - 16, BottomBorder_of_Block = x + 16;
					int LeftBorder_of_Block = y - 8, RightBorder_of_Block = y + 8;
					int begin = 1, end = 5;
					while ((TopBorder_of_Block < 2) && (LeftBorder_of_Block < 1)) {
						begin++;
						TopBorder_of_Block += 4;
						LeftBorder_of_Block += 2;
					}
					while ((BottomBorder_of_Block > 4 * column - 2) && (RightBorder_of_Block > 2 * row - 1) && (end >= 1)) {
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
						if ((a[initial_x][initial_y] != charX) && (a[initial_x + 4][initial_y + 2] != charX) && (a[initial_x + 8][initial_y + 4] != charX) &&
							(a[initial_x + 12][initial_y + 6] != charX) && (a[initial_x + 16][initial_y + 8] != charX)) {
							int num = 0;
							for (int i = initial_x, j = initial_y; i <= initial_x + 16, j <= initial_y + 8; i += 4, j += 2)
								if (a[i][j] == charO) num++;
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
						if ((a[initial_x][initial_y] != charO) && (a[initial_x + 4][initial_y + 2] != charO) && (a[initial_x + 8][initial_y + 4] != charO) &&
							(a[initial_x + 12][initial_y + 6] != charO) && (a[initial_x + 16][initial_y + 8] != charO)) {
							int num = 0;
							for (int i = initial_x, j = initial_y; i <= initial_x + 16, j <= initial_y + 8; i += 4, j += 2)
								if (a[i][j] == charX) num++;
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
					int BottomBorder_of_Block = x + 16, TopBorder_of_Block = x - 16;
					int LeftBorder_of_Block = y - 8, RightBorder_of_Block = y + 8;
					int begin = 1, end = 5;
					while ((BottomBorder_of_Block > 4 * column - 2) && (LeftBorder_of_Block < 1)) {
						begin++;
						BottomBorder_of_Block -= 4;
						LeftBorder_of_Block += 2;
					}
					while ((TopBorder_of_Block < 2) && (RightBorder_of_Block > 2 * row - 1) && (end >= 1)) {
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
						if ((a[initial_x][initial_y] != charX) && (a[initial_x - 4][initial_y + 2] != charX) && (a[initial_x - 8][initial_y + 4] != charX) &&
							(a[initial_x - 12][initial_y + 6] != charX) && (a[initial_x - 16][initial_y + 8] != charX)) {
							int num = 0;
							for (int i = initial_x, j = initial_y; i >= initial_x - 16, j <= initial_y + 8; i -= 4, j += 2)
								if (a[i][j] == charO) num++;
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
						if ((a[initial_x][initial_y] != charO) && (a[initial_x - 4][initial_y + 2] != charO) && (a[initial_x - 8][initial_y + 4] != charO) &&
							(a[initial_x - 12][initial_y + 6] != charO) && (a[initial_x - 16][initial_y + 8] != charO)) {
							int num = 0;
							for (int i = initial_x, j = initial_y; i >= initial_x - 16, j <= initial_y + 8; i -= 4, j += 2)
								if (a[i][j] == charX) num++;
							score[x][y] += DefenseScore[num];
						}
						blocks--;
						initial_x -= 4;
						initial_y += 2;
					}
				}
			}
}
void Score_of_Enemy_Cell(char a[][42], int &row, int &column, char &charX, char &charO, int score[][42], int Enemyscore[][42]) {
	// To evalue the score of each cell for the control
	int DefenseScore[5] = { 0, 2, 14, 98, 686 };
	int AttackScore[5] = { 0, 1, 8, 64, 512 };

	for (int i = 2; i < 4 * column; i += 4)
		for (int j = 1; j < 2 * row;j += 2) Enemyscore[i][j] = 0;
	// evaluate the empty cell
	for (int x = 2; x < column * 4; x += 4)
		for (int y = 1; y < row * 2; y += 2)
			if (a[x][y] == ' ') {
				//Vertical 
				{
					//Determine how many block to check
					int LeftBorder_of_Block = y - 8, RightBorder_of_Block = y + 8;
					int begin = 1, end = 5;
					while (LeftBorder_of_Block < 1) {
						begin++;
						LeftBorder_of_Block += 2;
					}
					while ((RightBorder_of_Block > 2 * row - 1) && (end >= 1)) {
						end--;
						RightBorder_of_Block -= 2;
					}

					// Number of blocks had to check
					int blocks = end - begin + 1;
					int initial = y - 10 + begin * 2;		//
															//	Check DEFENSE for each block
					while (blocks > 0) {
						if ((a[x][initial] != charX) && (a[x][initial + 2] != charX) && (a[x][initial + 4] != charX) &&
							(a[x][initial + 6] != charX) && (a[x][initial + 8] != charX)) {
							int num = 0;
							for (int i = initial; i <= initial + 8; i += 2)
								if (a[x][i] == charO) num++;
							Enemyscore[x][y] += DefenseScore[num];
						}
						blocks--;
						initial += 2;
					}
					blocks = end - begin + 1;
					initial = y - 10 + begin * 2;
					//	Check ATTACK of each block
					while (blocks > 0) {
						if ((a[x][initial] != charO) && (a[x][initial + 2] != charO) && (a[x][initial + 4] != charO) &&
							(a[x][initial + 6] != charO) && (a[x][initial + 8] != charO)) {
							int num = 0;
							for (int i = initial; i <= initial + 8; i += 2)
								if (a[x][i] == charX) num++;
							Enemyscore[x][y] += AttackScore[num];
						}
						blocks--;
						initial += 2;
					}
				}
				// Horizontal
				{
					//Determine how many block to check
					int TopBorder_of_Block = x - 16, BottomBorder_of_Block = x + 16;
					int begin = 1, end = 5;
					while (TopBorder_of_Block < 2) {
						begin++;
						TopBorder_of_Block += 4;
					}
					while ((BottomBorder_of_Block > 4 * column - 2) && (end >= 1)) {
						end--;
						BottomBorder_of_Block -= 4;
					}

					// Number of blocks had to check
					int blocks = end - begin + 1;
					int initial = x - 20 + begin * 4;		//
															//	Check DEFENSE for each block
					while (blocks > 0) {
						if ((a[initial][y] != charX) && (a[initial + 4][y] != charX) && (a[initial + 8][y] != charX) &&
							(a[initial + 12][y] != charX) && (a[initial + 16][y] != charX)) {
							int num = 0;
							for (int i = initial; i <= initial + 16; i += 4)
								if (a[i][y] == charO) num++;
							Enemyscore[x][y] += DefenseScore[num];
						}
						blocks--;
						initial += 4;
					}
					blocks = end - begin + 1;
					initial = x - 20 + begin * 4;		//
														//	Check ATTACK for each block
					while (blocks > 0) {
						if ((a[initial][y] != charO) && (a[initial + 4][y] != charO) && (a[initial + 8][y] != charO) &&
							(a[initial + 12][y] != charO) && (a[initial + 16][y] != charO)) {
							int num = 0;
							for (int i = initial; i <= initial + 16; i++)
								if (a[i][y] == charX) num++;
							Enemyscore[x][y] += AttackScore[num];
						}
						blocks--;
						initial += 4;
					}
				}
				// Left_Right Diagonal 
				{
					//Determine how many block to check
					int TopBorder_of_Block = x - 16, BottomBorder_of_Block = x + 16;
					int LeftBorder_of_Block = y - 8, RightBorder_of_Block = y + 8;
					int begin = 1, end = 5;
					while ((TopBorder_of_Block < 2) && (LeftBorder_of_Block < 1)) {
						begin++;
						TopBorder_of_Block += 4;
						LeftBorder_of_Block += 2;
					}
					while ((BottomBorder_of_Block > 4 * column - 2) && (RightBorder_of_Block > 2 * row - 1) && (end >= 1)) {
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
						if ((a[initial_x][initial_y] != charX) && (a[initial_x + 4][initial_y + 2] != charX) && (a[initial_x + 8][initial_y + 4] != charX) &&
							(a[initial_x + 12][initial_y + 6] != charX) && (a[initial_x + 16][initial_y + 8] != charX)) {
							int num = 0;
							for (int i = initial_x, j = initial_y; i <= initial_x + 16, j <= initial_y + 8; i += 4, j += 2)
								if (a[i][j] == charO) num++;
							Enemyscore[x][y] += DefenseScore[num];
						}
						blocks--;
						initial_x += 4; initial_y += 2;
					}
					blocks = end - begin + 1;
					initial_x = x - 20 + begin * 4;
					initial_y = y - 10 + begin * 2;
					// Check ATTACK for each block
					while (blocks > 0) {
						if ((a[initial_x][initial_y] != charO) && (a[initial_x + 4][initial_y + 2] != charO) && (a[initial_x + 8][initial_y + 4] != charO) &&
							(a[initial_x + 12][initial_y + 6] != charO) && (a[initial_x + 16][initial_y + 8] != charO)) {
							int num = 0;
							for (int i = initial_x, j = initial_y; i <= initial_x + 16, j <= initial_y + 8; i += 4, j += 2)
								if (a[i][j] == charX) num++;
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
					int BottomBorder_of_Block = x + 16, TopBorder_of_Block = x - 16;
					int LeftBorder_of_Block = y - 8, RightBorder_of_Block = y + 8;
					int begin = 1, end = 5;
					while ((BottomBorder_of_Block > 4 * column - 2) && (LeftBorder_of_Block < 1)) {
						begin++;
						BottomBorder_of_Block -= 4;
						LeftBorder_of_Block += 2;
					}
					while ((TopBorder_of_Block < 2) && (RightBorder_of_Block > 2 * row - 1) && (end >= 1)) {
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
						if ((a[initial_x][initial_y] != charX) && (a[initial_x - 4][initial_y + 2] != charX) && (a[initial_x - 8][initial_y + 4] != charX) &&
							(a[initial_x - 12][initial_y + 6] != charX) && (a[initial_x - 16][initial_y + 8] != charX)) {
							int num = 0;
							for (int i = initial_x, j = initial_y; i >= initial_x - 16, j <= initial_y + 8; i -= 4, j += 2)
								if (a[i][j] == charO) num++;
							Enemyscore[x][y] += DefenseScore[num];
						}
						blocks--;
						initial_x -= 4; initial_y += 2;
					}
					blocks = end - begin + 1;
					initial_x = x + 20 - begin * 4;
					initial_y = y - 10 + begin * 2;
					// Check ATTACK for each block
					while (blocks > 0) {
						if ((a[initial_x][initial_y] != charO) && (a[initial_x - 4][initial_y + 2] != charO) && (a[initial_x - 8][initial_y + 4] != charO) &&
							(a[initial_x - 12][initial_y + 6] != charO) && (a[initial_x - 16][initial_y + 8] != charO)) {
							int num = 0;
							for (int i = initial_x, j = initial_y; i >= initial_x - 16, j <= initial_y + 8; i -= 4, j += 2)
								if (a[i][j] == charX) num++;
							Enemyscore[x][y] += AttackScore[num];
						}
						blocks--;
						initial_x -= 4; initial_y += 2;
					}
				}
			}
}
int Check_Win(char a[][42], int x, int y, int &row, int &column, char &charX, char &charO) {
	//	0 nothing happen
	//	1 win
	//	-1 blocked 2 sides -> do not choose this control
	int check, curX, curY, top, bottom, left, right;
	if (a[x][y] == charX || a[x][y] == charO) {
		// Check Vertical
		{
			check = 1; top = y; bottom = y;
			curX = x; curY = y;
			while ((curY - 2) >= 1 && (a[x][curY - 2] == a[x][y])) {
				check++;
				curY -= 2;
			}
			if ((a[x][curY - 2] != ' ') && (a[x][curY - 2] != a[x][y]))	//	Block the top side
				top = curY - 2;

			curX = x; curY = y;
			while ((curY + 2) <= 2 * row - 1 && (a[x][curY + 2] == a[x][y])) {
				check++;
				curY += 2;
				if (curY + 2 <= 2 * row - 1) bottom = curY + 2;
			}
			if ((a[x][curY + 2] != ' ') && (a[x][curY + 2] != a[x][y]))	//	Block the bottom side
				bottom = curY + 2;

			if (check == 5)
				if ((a[x][top] != ' ') && (a[x][top] != a[x][y]) && (a[x][bottom] != ' ') && (a[x][bottom] != a[x][y]))
					return -1;
				else return 1;
		}
		// Check Horizontal
		{
			check = 1; left = x; right = x;
			curX = x; curY = y;
			while ((curX - 4) >= 2 && (a[curX - 4][y] == a[x][y])) {
				check++;
				curX -= 4;
			}
			if ((a[curX - 4][y] != ' ') && (a[curX - 4][y] != a[x][y])) // Blocked the left side
				left = curX - 4;

			curX = x; curY = y;
			while ((curX + 4) <= 4 * column - 2 && (a[curX + 4][y] == a[x][y])) {
				check++;
				curX += 4;
			}
			if ((a[curX + 4][y] != ' ') && (a[curX + 4][y] != a[x][y]))	//	Blocked the right side
				right = curX + 4;

			if (check == 5)
				if ((a[left][y] != ' ') && (a[left][y] != a[x][y]) && (a[right][y] != ' ') && (a[right][y] != a[x][y]))
					return -1;
				else return 1;
		}
		// Check Left_Right Diagonal
		{
			check = 1;
			left = x; right = x; top = y; bottom = y;
			curX = x; curY = y;
			while ((curX - 4) >= 2 && (curY - 2) >= 1 && (a[curX - 4][curY - 2] == a[x][y])) {
				check++;
				curX -= 4;
				curY -= 2;
			}
			if ((a[curX - 4][curY - 2] != ' ') && (a[curX - 4][curY - 2] != a[x][y])) {  // Blocked the left -top side 
				left = curX - 4;
				top = curY - 2;
			}

			curX = x; curY = y;
			while ((curX + 4) <= 4 * column - 2 && (curY + 2) <= 2 * row - 1 && (a[curX + 4][curY + 2] == a[x][y])) {
				check++;
				curX += 4;
				curY += 2;
			}
			if ((a[curX + 4][curY + 2] != ' ') && (a[curX + 4][curY + 2] != a[x][y])) {	//	Blocked the right-bottom side
				right = curX + 4;
				bottom = curY + 2;
			}

			if (check == 5)
				if ((a[left][top] != ' ') && (a[left][top] != a[x][y]) && (a[right][bottom] != ' ') && (a[right][bottom] != a[x][y]))
					return -1;
				else return 1;
		}
		// Check Right_Left Diagonal
		{
			check = 1;
			left = x; right = x; top = y; bottom = y;
			curX = x; curY = y;
			while ((curX - 4) >= 2 && (curY + 2) <= 2 * row - 1 && (a[curX - 4][curY + 2] == a[curX][curY])) {
				check++;
				curX -= 4;
				curY += 2;
			}
			if ((a[curX - 4][curY + 2] != ' ') && (a[curX - 4][curY + 2] != a[x][y])) { // Blocked the left-bottom side
				left = curX - 4;
				bottom = curY + 2;
			}

			curX = x; curY = y;
			while ((curX + 4) <= 4 * column - 2 && (curY - 2) >= 1 && (a[curX + 4][curY - 2] == a[curX][curY])) {
				check++;
				curX += 4;
				curY -= 2;
			}
			if ((a[curX + 4][curY - 2] != ' ') && (a[curX + 4][curY - 2] != a[x][y])) {	//	Blocked the right-top side
				right = curX + 4;
				top = curY - 2;
			}

			if (check == 5)
				if ((a[right][top] != ' ') && (a[right][top] != a[x][y]) && (a[left][bottom] != ' ') && (a[left][bottom] != a[x][y]))
					return -1;
				else return 1;
		}

		if (check != 5) return 0;
	}
}
void Undo(char a[][42], int &row, int &column, int n, int &step, int x, int y, int curX, int curY, char &charX, char &charO, int score[][42], int Enemyscore[][42]) {
	if (n == 0) {
		step--;
		TextColor(7);
		a[x][y] = ' ';
		gotoXY(x, y);
		cout << a[x][y] << endl;
	}
	else {
		step -= 2;
		TextColor(7);
		a[x][y] = ' ';
		gotoXY(x, y);
		cout << a[x][y] << endl;
		TextColor(7);
		a[curX][curY] = ' ';
		gotoXY(curX, curY);
		cout << a[curX][curY] << endl;
		// Reset the scoring array
		for (int i = 2; i < column * 4; i += 4)
			for (int j = 1; j < row * 2;j += 2) {
				score[i][j] = 0;
				Enemyscore[i][j] = 0;
			}
		Score_of_Cell(a, row, column, charX, charO, score, Enemyscore);

	}
}

int Load(char a[][42], int &Row, char &charX, char &charO) {
	int number = 0, mau[9];
	for (int i = 0; i < 9; i++) mau[i] = Color;
	string ListofGame[9] = { "","Game 1", "Game 2","Game 3", "Game 4", "Game 5", "Game 6", "Game 7", "Back" };
	while (1) {
		int x = 88, y = 14;
		for (int i = 0; i < 9; i++) {
			gotoXY(x, y);
			TextColor(mau[i]);
			cout << ListofGame[i] << endl;
			y++;
		}
		int z = _getch();
		Control Game = control(z);
		switch (Game) {
		case UP:
			if (number == 1 || number == 0) number = 8;
			else --number;
			break;
		case DOWN:
			if (number == 8) number = 1;
			else ++number;
			break;
		case ENTER:
			clrscr();
			system("Color 7");
			return number;
		}

		/*
		Choose the file user want to open the saved game
		User may review the board of saved game
		*/
		ifstream loadgame;
		if (number != 8) {
			switch (number) {
			case 1:
				loadgame.open("Game_1.txt");
				break;
			case 2:
				loadgame.open("Game_2.txt");
				break;
			case 3:
				loadgame.open("Game_3.txt");
				break;
			case 4:
				loadgame.open("Game_4.txt");
				break;
			case 5:
				loadgame.open("Game_5.txt");
				break;
			case 6:
				loadgame.open("Game_6.txt");
				break;
			case 7:
				loadgame.open("Game_7.txt");
				break;
			}
			loadgame >> Row;
			clrscr();
			gotoXY(0, 0);
			Board(Row, Row);
			char c;
			int i, j;
			while (!loadgame.eof()) {
				loadgame >> c >> i >> j;
				gotoXY(i, j);
				if (c == charX) {
					TextColor(12);
					cout << c << endl;
				}
				else if (c == charO) {
					TextColor(10);
					cout << c << endl;
				}
				a[i][j] = c;
			}
			loadgame.close();
		}
		else {
			clrscr();
			system("Color 7");
		}
		for (int i = 0; i < 9; i++) mau[i] = Color;
		mau[number] = 124;
	}
	return 0;
}
int Load_Game(char a[][42], int &row, int &column, char &charX, char &charO, int &PvP) {
	int Row = 0;
	int x = Load(a, Row, charX, charO);
	if (x == 8) return 0;
	Board(Row, Row);
	PP_Mode(a, row, column, 0, charX, charO, PvP);
}
int Save_Game(char a[][42], int &row, int &column) {
	int number = 0, mau[9];
	int temp = 0;
	for (int i = 0; i < 9; i++) mau[i] = Color;
	while (temp == 0) {
		int x = 90, y = 17;
		string ListofGame[9] = { "","Game 1", "Game 2","Game 3", "Game 4", "Game 5", "Game 6", "Game 7", "Back" };
		for (int i = 0; i < 9; i++) {
			gotoXY(x, y);
			TextColor(mau[i]);
			cout << ListofGame[i] << endl;
			y++;
		}
		int z = _getch();
		Control Game = control(z);
		switch (Game) {
		case UP:
			if (number == 1 || number == 0) number = 8;
			else --number;
			break;
		case DOWN:
			if (number == 8) number = 1;
			else ++number;
			break;
		case ENTER:
			if (number != 8) 	Clear_Screen();
			temp = 1;
			break;
		}
		for (int i = 0; i < 9; i++) mau[i] = Color;
		mau[number] = 124;
	}

	ofstream savegame;
	switch (number) {
	case 1:
		savegame.open("Game_1.txt");
		break;
	case 2:
		savegame.open("Game_2.txt");
		break;
	case 3:
		savegame.open("Game_3.txt");
		break;
	case 4:
		savegame.open("Game_3.txt");
		break;
	case 5:
		savegame.open("Game_3.txt");
		break;
	case 6:
		savegame.open("Game_3.txt");
		break;
	case 7:
		savegame.open("Game_3.txt");
		break;
	case 8: return 0;
	}
	savegame << row << endl;
	for (int j = 1; j < 2 * row; j += 2) {
		for (int i = 2; i < 4 * column; i += 4)
			if (a[i][j] != ' ')
				savegame << a[i][j] << ' ' << i << ' ' << j << endl;
	}
	savegame.close();
	return 0;
}