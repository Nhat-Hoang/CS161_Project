#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "console.h"
#include <string>
#include "StartScreen.h"

using namespace std;
enum TBack { menu };
TBack str;
void Back(TBack str) {
	switch (str)
	{
	case menu: {
		Clear_Menu();
		Menu();
	}
	}

}
