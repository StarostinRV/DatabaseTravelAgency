#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <list>
#include <set>
#include <iterator>
#include "Menu.h"
#include "Console.h"
#include "Types.h"
#include "Instrument.h"
using namespace std;
class Holiday
{
private:
	string fild_items[4];
	list<Struct_holiday> holidays;
	Struct_holiday TakeStr(string str)
	{
		Struct_holiday term;
		string take;
		// код вида 4
		take = str.substr(0, 4);
		term.code_holiday = ConvertStrToInt(take);
		str.erase(0, 4);
		// наимен 25
		take = str.substr(0, 25);
		term.title = DeleteUselessSpace(take);
		str.erase(0, 25);
		// описание 150 25*6
		take = str.substr(0, 150);
		term.description = DeleteUselessSpace(take);
		str.erase(0, 150);
		// ограничения 150 25*6
		take = str.substr(0, 150);
		term.limit = DeleteUselessSpace(take);
		str.erase(0, 150);
		return term;
	}
	void InitFildItems()
	{
		fild_items[0] = "Код вида:";
		fild_items[1] = "Наименование:";
		fild_items[2] = "Описание:";
		fild_items[3] = "Ограничения:";
		for (int i = 0; i < 4; i++)
			ConvertIntoWIN1251ToDOS866(fild_items[i]);
	}
public:
	Holiday(bool empty = false)
	{
		InitFildItems();
		if (!empty) ReadFromFile("Виды отдыха.txt");
	}
	void ReadFromFile(string name)
	{
		fstream input;
		input.open(name.c_str(), ios_base::in);
		if (!input.is_open())
		{
			input.close();
			input.open(name.c_str(), ios_base::out);
			input.close();
			return;
		}
		while (input.peek() != EOF)
		{
			string read;
			getline(input, read);
			ConvertIntoWIN1251ToDOS866(read);
			Struct_holiday term = TakeStr(read);
			holidays.push_back(term);
		}
		input.close();
		return;
	}
	void ShowItems(bool _l = true, bool _r = true)
	{
		SetColor(BRIGHTGREY, BLACK);
		if (_l)
		{
			for (int i = 0; i < 3; i++)
			{
				gotoXY(0, 3 + i * 2);
				cout << fild_items[i];
			}
			gotoXY(0, 14);
			cout << fild_items[3];
		}
		for (int i = 3; i < 25; i++)
		{
			gotoXY(39, i);
			cout << Ver;
		}
		if (_r)
		{
			for (int i = 0; i < 3; i++)
			{
				gotoXY(41, 3 + i * 2);
				cout << fild_items[i];
			}
			gotoXY(41, 14);
			cout << fild_items[3];
		}
	}
	void ShowData(Struct_holiday term, short x, short y)
	{
		SetColor(BRIGHTGREY, BLACK);
		Point pos;
		pos.X = x;
		pos.Y = y;
		//код
		gotoXY(pos);
		string str = ConvertIntToStr(term.code_holiday, 4);
		cout << str;
		pos.Y += 2;
		//наим
		gotoXY(pos);
		str = term.title + StrSpace(25 - term.title.length());
		cout << str;
		pos.Y += 2;
		//опис
		str = term.description + StrSpace(150 - term.description.length());
		for (int i = 0; i < 150; i++)
		{
			gotoXY(pos.X + (i % 25), pos.Y + (i / 25));
			cout << str[i];
		}
		pos.Y += 7;
		// требования
		str = term.limit + StrSpace(150 - term.limit.length());
		for (int i = 0; i < 150; i++)
		{
			gotoXY(pos.X + (i % 25), pos.Y + (i / 25));
			cout << str[i];
		}
	}
	void DemonstrateType_0()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Виды отдыха");
		string str1 = "";
		string str2 = "";
		string str_ = "";
		string str_mid = "";
		string str_down = "";
		string str_down2 = "";
		str1 += "Код                                                               ";
		str2 += "вида Наименование              Обязаности               Требования";
		str_down2 += " ";
		ConvertIntoWIN1251ToDOS866(str1);
		ConvertIntoWIN1251ToDOS866(str2);
		for (int i = 0; i < 80; i++)
			str_ += Hor;
		str_down2 = str_down = str_mid = str_;
		str1[4] = str1[30] = str1[55] = Ver;
		str2[4] = str2[30] = str2[55] = Ver;
		str_[4] = str_[30] = str_[55] = HorDown;
		str_mid[4] = str_mid[30] = str_mid[55] = Cross;
		str_down[4] = str_down[30] = str_down[55] = HorUp;
		str_down2[4] = str_down2[30] = str_down2[55] = Ver;
		SetColor(BRIGHTGREY, BLACK);
		gotoXY(0, 3);
		cout << str_;
		cout << str1 << endl;
		cout << str2 << endl;
		Menu table;
		Point pos;
		pos.X = 0;
		pos.Y = 7;
		Item item;
		table.SetAlignment(_Left);
		table.SetDistance(1);
		table.SetTypeMenu(1);
		item.checked = false;
		table.SetPosition(pos);
		table.SetNShow(9);
		table.AddKey(kEsc);
		table.SetFrame(false);
		table.SetMenuColor(BRIGHTGREY, BLACK, BLACK, BRIGHTGREY, YELLOY, BRIGHTGREY);
		for (list<Struct_holiday> ::iterator it = holidays.begin(); it != holidays.end();
			it++)
		{
			Struct_holiday term = *it;
			item.text = "";
			item.text += ConvertIntToStr(term.code_holiday, 4);
			item.text += Ver;
			item.text += term.title + StrSpace(25 - term.title.length());
			item.text += Ver;
			item.text += term.description.substr(0, 24);
			item.text += Ver;
			item.text += term.limit.substr(0, 24);
			table.AddItem(item, false);
		}
		table.Show();
		int i = 0;
		for (; (i<9) && (i < holidays.size()); i++)
		{
			gotoXY(0, 6 + i * 2);
			cout << str_mid << endl;
		}
		gotoXY(0, 6 + i * 2);
		if (holidays.size()<8) cout << str_down;
		table.Use();
	}
	void DemonstrateType_1()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Виды отдыха");
		bool clear = false;
		list<Struct_holiday> ::iterator right;
		list<Struct_holiday> ::iterator left;
		left = right = holidays.begin();
		right++;
		ShowItems(true, right != holidays.end());
		if (left != holidays.end()) ShowData(*left, 14, 3);
		if (right != holidays.end())ShowData(*right, 55, 3);
		TKey key = kNone;
		while (key != kEsc)
		{
			GetKey(key);
			if ((key == kRight) && (right != holidays.end()) && (left != holidays.end()))
			{
				if (right != holidays.end())right++;
				if (right != holidays.end())right++;
				if (left != holidays.end())left++;
				if (left != holidays.end())left++;
				if (left != holidays.end()) ShowData(*left, 14, 3);
				if (right != holidays.end())ShowData(*right, 55, 3);
				left++;
				if (left == holidays.end())
				{
					ClearArea(BRIGHTGREY, 40, 3, 79, 23);
					clear = true;
				}
				left--;
			}
			if ((key == kLeft) && (right != holidays.begin()) && (left != holidays.begin()))
			{
				if (clear)
				{
					ShowItems(true, true);
					clear = false;
				}
				if ((right == left) && (left == holidays.end()))
				{
					left--;
					left--;
					right--;
				}
				if (right != holidays.begin())right--;
				if (right != holidays.begin())right--;
				if (left != holidays.begin())left--;
				if (left != holidays.begin())left--;
				if (left != holidays.end()) ShowData(*left, 14, 3);
				if (right != holidays.end())ShowData(*right, 55, 3);
			}
		}
	}
	void Demonstrate()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Виды отдыха");
		if (holidays.empty())
		{
			string str = "Нет элементов";
			ConvertIntoWIN1251ToDOS866(str);
			gotoXY(33, 12);
			cout << str;
			TKey key;
			GetKey(key);
			while (key != kEsc)
			{
				GetKey(key);
			}
			return;
		}
		string str = "ОТОБРАЖЕНИЕ";
		ConvertIntoWIN1251ToDOS866(str);
		gotoXY(35, 5);
		cout << str;
		Point pos;
		pos.X = 31;
		pos.Y = 7;
		Item item;
		item.checked = false;
		Menu menu;
		menu.SetPosition(pos);
		menu.SetAddSpace(5);
		menu.SetDistance(2);
		menu.AddKey(kEnter);
		menu.SetFrame(true);
		menu.SetMenuColor(BLACK, BLACK, BLACK, BRIGHTGREY, YELLOY, BRIGHTGREY);
		item.text = "Таблица";
		menu.AddItem(item);
		item.text = "Список";
		menu.AddItem(item);
		item.text = "Назад";
		menu.AddItem(item);
		menu.Show();
		menu.Use();
		int n = menu.GetActiveItem();
		if (n == 0) DemonstrateType_0();
		else if (n == 1) DemonstrateType_1();
	}
	list<Struct_holiday> GetHolidays()
	{
		return holidays;
	}
	~Holiday()
	{
		holidays.clear();
	}
};