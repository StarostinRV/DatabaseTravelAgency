#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Types.h"
using namespace std;
void gotoXY(short x, short y)
{
	if ((x>79) || (y>24)) return;
	if ((x == 79) && (y == 24)) return;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void gotoXY(Point point)
{
	if ((point.X>79) || (point.Y>24)) return;
	if ((point.X == 79) && (point.Y == 24)) return;
	COORD coord;
	coord.X = point.X;
	coord.Y = point.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Clear()
{
	system("CLS");
}
void ClearArea(Color color, short x1, short y1, short x2, short y2)
{
	HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h_out, color << 4 | BLACK);
	for (short j = y1; j <= y2; j++)
		for (short i = x1; i <= x2; i++)
		{
			gotoXY(i, j);
			cout << " ";
		}
}
void Clear(Color color)
{
	HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h_out, color << 4);
	system("CLS");
}
void SetColor(Color back, Color text)
{
	HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h_out, (back << 4) | text);
}
short GetKey(TKey &key)
{
	key = kNone;
	int key_pressed = _kbhit();
	short key_read = 0;
	if (key_pressed)
	{
		key_read = _getch();
		bool function_key = (((key_read == 224) || (key_read == 0)) && _kbhit());
		if (function_key) key_read = _getch();
		if (function_key)
		{
			switch (key_read)
			{
			case 72:
			{
				key = kUp;
				break;
			}
			case 75:
			{
				key = kLeft;
				break;
			}
			case 77:
			{
				key = kRight;
				break;
			}
			case 80:
			{
				key = kDown;
				break;
			}
			}
		}
		else if (key_read == 27) key = kEsc;
		else if (key_read == 13) key = kEnter;
		else if (key_read == 8) key = kBackspace;
		bool sign = false;
		sign = sign || ((key_read >= 32) && (key_read <= 126));
		sign = sign || ((key_read >= 128) && (key_read <= 175));
		sign = sign || ((key_read >= 224) && (key_read <= 241));
		sign = sign || (key_read == 252);
		if (sign && !function_key) key = kChar;
		while (_kbhit())
		{
			key_read = _getch();
			function_key = (((key_read == 224) || (key_read == 0)) && _kbhit());
			if (function_key) key_read = _getch();
		}
	}
	return key_read;
}