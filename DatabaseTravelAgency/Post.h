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
class Post
{
private:
	string fild_items[5];
	list<Struct_post> posts;
	Struct_post TakeStr(string str)
	{
		Struct_post term;
		string take;
		// код должности 4
		take = str.substr(0, 4);
		term.code_post = ConvertStrToInt(take);
		str.erase(0, 4);
		// наимен 25
		take = str.substr(0, 25);
		term.name = DeleteUselessSpace(take);
		str.erase(0, 25);
		// оклад 9
		take = str.substr(0, 9);
		take = DeleteUselessSpace(take);
		term.payment = ConvertStrToInt(take);
		str.erase(0, 9);
		// описание 150 25*6
		take = str.substr(0, 150);
		term.duties = DeleteUselessSpace(take);
		str.erase(0, 150);
		// требования 150 25*6
		take = str.substr(0, 150);
		term.requirements = DeleteUselessSpace(take);
		str.erase(0, 150);
		return term;
	}
	void InitFildItems()
	{
		fild_items[0] = "Код должности:";
		fild_items[1] = "Наименование:";
		fild_items[2] = "Оклад:";
		fild_items[3] = "Обязаности:";
		fild_items[4] = "Требования:";
		for (int i = 0; i<5; i++)
			ConvertIntoWIN1251ToDOS866(fild_items[i]);
	}
public:
	Post(bool empty = false)
	{
		InitFildItems();
		if (!empty) ReadFromFile("Должности.txt");
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
			Struct_post term = TakeStr(read);
			posts.push_back(term);
		}
		input.close();
		return;
	}
	void ShowItems(bool _l = true, bool _r = true)
	{
		SetColor(BRIGHTGREY, BLACK);
		if (_l)
		{
			for (int i = 0; i < 4; i++)
			{
				gotoXY(0, 3 + i * 2);
				cout << fild_items[i];
			}
			gotoXY(0, 16);
			cout << fild_items[4];
		}
		for (int i = 3; i < 25; i++)
		{
			gotoXY(39, i);
			cout << Ver;
		}
		if (_r)
		{
			for (int i = 0; i < 4; i++)
			{
				gotoXY(41, 3 + i * 2);
				cout << fild_items[i];
			}
			gotoXY(41, 16);
			cout << fild_items[4];
		}
	}
	void ShowData(Struct_post term, short x, short y)
	{
		SetColor(BRIGHTGREY, BLACK);
		Point pos;
		pos.X = x;
		pos.Y = y;
		//код
		gotoXY(pos);
		string str = ConvertIntToStr(term.code_post, 4);
		cout << str;
		pos.Y += 2;
		//наим
		gotoXY(pos);
		str = term.name + StrSpace(25 - term.name.length());
		cout << str;
		pos.Y += 2;
		//оплата
		gotoXY(pos);
		str = ConvertIntToStr(term.payment);
		str += StrSpace(9 - str.length());
		cout << str;
		pos.Y += 2;
		//обязаности
		str = term.duties + StrSpace(150 - term.duties.length());
		for (int i = 0; i < 150; i++)
		{
			gotoXY(pos.X + (i % 25), pos.Y + (i / 25));
			cout << str[i];
		}
		pos.Y += 7;
		// требования
		str = term.requirements + StrSpace(150 - term.requirements.length());
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
		Title("Должности");
		string str1 = "";
		string str2 = "";
		string str_ = "";
		string str_mid = "";
		string str_down = "";
		string str_down2 = "";
		str1 += "Код                                                                         ";
		str2 += "долж Наименование              Оклад     Обязаности          Требования    ";
		str_down2 += " ";
		ConvertIntoWIN1251ToDOS866(str1);
		ConvertIntoWIN1251ToDOS866(str2);
		for (int i = 0; i < 80; i++)
			str_ += Hor;
		str_down2 = str_down = str_mid = str_;
		str1[4] = str1[30] = str1[40] = str1[60] = Ver;
		str2[4] = str2[30] = str2[40] = str2[60] = Ver;
		str_[4] = str_[30] = str_[40] = str_[60] = HorDown;
		str_mid[4] = str_mid[30] = str_mid[40] = str_mid[60] = Cross;
		str_down[4] = str_down[30] = str_down[40] = str_down[60] = HorUp;
		str_down2[4] = str_down2[30] = str_down2[40] = str_down2[60] = Ver;
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
		for (list<Struct_post> ::iterator it = posts.begin(); it != posts.end(); it++)
		{
			Struct_post term = *it;
			item.text = "";
			item.text += ConvertIntToStr(term.code_post, 4);
			item.text += Ver;
			item.text += term.name + StrSpace(25 - term.name.length());
			item.text += Ver;
			string pay = ConvertIntToStr(term.payment);
			item.text += StrSpace(9 - pay.length()) + pay;
			item.text += Ver;
			item.text += term.duties.substr(0, 19);
			item.text += Ver;
			item.text += term.requirements.substr(0, 19);
			table.AddItem(item, false);
		}
		table.Show();
		int i = 0;
		for (; (i<9) && (i < posts.size()); i++)
		{
			gotoXY(0, 6 + i * 2);
			cout << str_mid << endl;
		}
		gotoXY(0, 6 + i * 2);
		if (posts.size()<8) cout << str_down;
		table.Use();
	}
	void DemonstrateType_1()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Должности");
		bool clear = false;
		list<Struct_post> ::iterator right;
		list<Struct_post> ::iterator left;
		left = right = posts.begin();
		right++;
		ShowItems(true, right != posts.end());
		if (left != posts.end()) ShowData(*left, 14, 3);
		if (right != posts.end())ShowData(*right, 55, 3);
		TKey key = kNone;
		while (key != kEsc)
		{
			GetKey(key);
			if ((key == kRight) && (right != posts.end()) && (left != posts.end()))
			{
				if (right != posts.end())right++;
				if (right != posts.end())right++;
				if (left != posts.end())left++;
				if (left != posts.end())left++;
				if (left != posts.end()) ShowData(*left, 14, 3);
				if (right != posts.end())ShowData(*right, 55, 3);
				left++;
				if (left == posts.end())
				{
					ClearArea(BRIGHTGREY, 40, 3, 79, 23);
					clear = true;
				}
				left--;
			}
			if ((key == kLeft) && (right != posts.begin()) && (left !=
				posts.begin()))
			{
				if (clear)
				{
					ShowItems(true, true);
					clear = false;
				}
				if ((right == left) && (left == posts.end()))
				{
					left--;
					left--;
					right--;
				}
				if (right != posts.begin())right--;
				if (right != posts.begin())right--;
				if (left != posts.begin())left--;
				if (left != posts.begin())left--;
				if (left != posts.end()) ShowData(*left, 14, 3);
				if (right != posts.end())ShowData(*right, 55, 3);
			}
		}
	}
	void Demonstrate()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Должности");
		if (posts.empty())
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
	list<Struct_post> GetPosts()
	{
		return posts;
	}
	~Post()
	{
		posts.clear();
	}
};