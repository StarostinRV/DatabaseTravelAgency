#pragma once
#include <iostream>
#include <string>
#include "Types.h"
#include "Console.h"
using namespace std;
void ConvertIntoDOS866ToWIN1251(string &str)
{
	for (int i = 0; i<str.length(); i++)
	{
		unsigned char sign = str[i];
		if ((sign >= 128) && (sign <= 175)) sign += 64;
		else if ((sign >= 224) && (sign <= 239)) sign += 16;
		else if (sign == 240) sign = 168;
		else if (sign == 241) sign = 184;
		else if (sign == 252) sign = 185;
		str[i] = sign;
	}
}
void ConvertIntoWIN1251ToDOS866(string &str)
{
	for (int i = 0; i<str.length(); i++)
	{
		unsigned char sign = str[i];
		if ((sign >= 192) && (sign <= 239)) sign -= 64;
		else if ((sign >= 240) && (sign <= 255)) sign -= 16;
		else if (sign == 168) sign = 240;
		else if (sign == 184) sign = 241;
		else if (sign == 185) sign = 252;
		str[i] = sign;
	}
}
int ConvertStrToInt(string str)
{
	if (str.length() == 0) return -1;
	int ch = (int)str[0] - 48;
	int dec = 10;
	for (int i = 1; i<str.length(); i++)
		ch = ch * 10 + ((int)str[i] - 48);
	return ch;
}
string ConvertIntToStr(int ch, int min_len = 1)
{
	string str = "";
	if (ch == 0) return "0";
	while (ch>0)
	{
		str = char(48 + ch % 10) + str;
		ch /= 10;
	}
	while (min_len > str.length())
	{
		str = "0" + str;
	}
	return str;
}
string ConvertArrToStr(char str[], int N)
{
	string result = "";
	for (int i = 0; i < N; i++)
		result += str[i];
	return result;
}
string DeleteUselessSpace(string str)
{
	string result = "";
	int len = str.length();
	int begin = len;
	int end = 0;
	for (int i = 0; i < len; i++)
		if (str[i] != ' ')
		{
			begin = i;
			break;
		}
	for (int i = len - 1; i >= 0; i--)
		if (str[i] != ' ')
		{
			end = i;
			break;
		}
	if (begin <= end) result = str.substr(begin, end - begin + 1);
	return result;
}
string StrSpace(short N)
{
	string str;
	for (int i = 0; i<N; i++)
		str += ' ';
	return str;
}
void Title(string str)
{
	gotoXY(0, 0);
	cout << AngleLeftUp;
	gotoXY(79, 0);
	cout << AngleRightUp;
	gotoXY(0, 2);
	cout << AngleLeftDown;
	gotoXY(79, 2);
	cout << AngleRightDown;
	gotoXY(0, 1);
	cout << Ver;
	gotoXY(79, 1);
	cout << Ver;
	int len = 77 - str.length();
	int l = len / 2;
	gotoXY(l, 1);
	ConvertIntoWIN1251ToDOS866(str);
	cout << str;
	for (int i = 0; i < 78; i++)
	{
		gotoXY(1 + i, 0);
		cout << Hor;
		gotoXY(1 + i, 2);
		cout << Hor;
	}
}
string GetText(int x, int y, int width, int hight, string begin = "")
{
	ClearArea(YELLOY, x, y, x + width - 1, y + hight - 1);
	string result = StrSpace(width*hight);
	int index = 0;
	for (int i = 0; i < begin.length(); i++)
	{
		result[index] = begin[index];
		gotoXY(x + (index % width), y + (index / width));
		cout << result[i];
		index++;
	}
	TKey key = kNone;
	gotoXY(x + (index % width), y + (index / width));
	while (key != kEnter)
	{
		char ch = GetKey(key);
		if ((key == kChar) && (index < width*hight))
		{
			result[index] = ch;
			gotoXY(x + (index % width), y + (index / width));
			cout << result[index];
			index++;
			if (index != width*hight) gotoXY(x + (index % width), y + (index / width));
			else gotoXY(x + ((index - 1) % width), y + ((index - 1) / width));
		}
		if ((key == kBackspace) && (index > 0))
		{
			index--;
			result[index] = ' ';
			gotoXY(x + (index % width), y + (index / width));
			cout << " ";
			if (index != 0) gotoXY(x + ((index) % width), y + ((index) / width));
			else gotoXY(x, y);
		}
	}
	SetColor(BRIGHTGREY, BLACK);
	for (int i = 0; i < result.length(); i++)
	{
		gotoXY(x + (i % width), y + (i / width));
		cout << result[i];
	}
	return result;
}
string GetNumbers(int x, int y, int width, int hight, int begin, bool code)
{
	ClearArea(YELLOY, x, y, x + width - 1, y + hight - 1);
	string str;
	if (code) str = ConvertIntToStr(begin, width*hight);
	else
	{
		str = ConvertIntToStr(begin);
		str += StrSpace(width*hight - str.length());
	}
	string result = StrSpace(width*hight);
	int index = 0;
	for (int i = 0; i < str.length(); i++)
	{
		result[index] = str[index];
		gotoXY(x + (index % width), y + (index / width));
		cout << result[i];
		index++;
	}
	TKey key = kNone;
	gotoXY(x + (index % width), y + (index / width));
	while (key != kEnter)
	{
		char ch = GetKey(key);
		if ((key == kChar) && (index < width*hight) && (ch >= '0') && (ch <= '9'))
		{
			result[index] = ch;
			gotoXY(x + (index % width), y + (index / width));
			cout << result[index];
			index++;
			if (index != width*hight) gotoXY(x + (index % width), y + (index / width));
			else gotoXY(x + ((index - 1) % width), y + ((index - 1) / width));
		}
		if ((key == kBackspace) && (index > 0))
		{
			index--;
			result[index] = ' ';
			gotoXY(x + (index % width), y + (index / width));
			cout << " ";
			if (index != 0) gotoXY(x + ((index) % width), y + ((index) / width));
			else gotoXY(x, y);
		}
	}
	SetColor(BRIGHTGREY, BLACK);
	if (!code) result += StrSpace(width*hight - result.length());
	else
	{
		int n = ConvertStrToInt(result);
		result = ConvertIntToStr(n, width*hight);
	}
	for (int i = 0; i < result.length(); i++)
	{
		gotoXY(x + (i % width), y + (i / width));
		cout << result[i];
	}
	return result;
}