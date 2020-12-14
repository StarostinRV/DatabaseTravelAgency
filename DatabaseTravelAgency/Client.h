#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>
#include <iterator>
#include "Menu.h"
#include "Console.h"
#include "Types.h"
#include "Instrument.h"
using namespace std;
class Client
{
private:
	string fild_items[10];
	list<Struct_client> clients;
	Struct_client TakeStr(string str)
	{
		Struct_client term;
		string take;
		// код сотр 4
		take = str.substr(0, 4);
		term.code_client = ConvertStrToInt(take);
		str.erase(0, 4);
		// фамелия 25
		take = str.substr(0, 25);
		term.fio.surname = DeleteUselessSpace(take);
		str.erase(0, 25);
		// имя 25
		take = str.substr(0, 25);
		term.fio.name = DeleteUselessSpace(take);
		str.erase(0, 25);
		// отчество 25
		take = str.substr(0, 25);
		term.fio.patronym = DeleteUselessSpace(take);
		str.erase(0, 25);
		//дата 10
		take = str.substr(0, 10);
		term.date_born = take;
		str.erase(0, 10);
		// пол 3
		take = str.substr(0, 3);
		term.gender = take;
		str.erase(0, 3);
		// улица 25
		take = str.substr(0, 25);
		term.adress.street = DeleteUselessSpace(take);
		str.erase(0, 25);
		// дом 3
		take = str.substr(0, 3);
		take = DeleteUselessSpace(take);
		term.adress.home = ConvertStrToInt(take);
		str.erase(0, 3);
		// квартира 3
		take = str.substr(0, 3);
		take = DeleteUselessSpace(take);
		term.adress.flat = ConvertStrToInt(take);
		str.erase(0, 3);
		// телефон 11
		take = str.substr(0, 11);
		term.phone_number = DeleteUselessSpace(take);
		str.erase(0, 11);
		// паспорт 10
		take = str.substr(0, 10);
		term.passport = take;
		str.erase(0, 10);
		return term;
	}
	void InitFildItems()
	{
		fild_items[0] = "Код клиента:";
		fild_items[1] = "Фамелия:";
		fild_items[2] = "Имя:";
		fild_items[3] = "Отчество:";
		fild_items[4] = "Дата рождения:";
		fild_items[5] = "Пол:";
		fild_items[6] = "Улица:";
		fild_items[7] = "Дом/Квартира:";
		fild_items[8] = "Телефон номер:";
		fild_items[9] = "Паспорт";
		for (int i = 0; i < 10; i++)
			ConvertIntoWIN1251ToDOS866(fild_items[i]);
	}
public:
	Client(bool empty = false)
	{
		InitFildItems();
		if (!empty) ReadFromFile("Клиенты.txt");
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
			Struct_client term = TakeStr(read);
			clients.push_back(term);
		}
		input.close();
		return;
	}
	void ShowItems(bool _l = true, bool _r = true)
	{
		SetColor(BRIGHTGREY, BLACK);
		if (_l)
		{
			for (int i = 0; i < 10; i++)
			{
				gotoXY(0, 3 + 2 * i);
				cout << fild_items[i];
			}
		}
		for (int i = 3; i < 25; i++)
		{
			gotoXY(39, i);
			cout << Ver;
		}
		if (_r)
		{
			for (int i = 0; i < 10; i++)
			{
				gotoXY(41, 3 + 2 * i);
				cout << fild_items[i];
			}
		}
	}
	void ShowData(Struct_client term, short x, short y)
	{
		SetColor(BRIGHTGREY, BLACK);
		Point pos;
		pos.X = x;
		pos.Y = y;
		string str;
		// код клиента
		gotoXY(pos);
		str = ConvertIntToStr(term.code_client, 4);
		cout << str;
		pos.Y += 2;
		//фам
		gotoXY(pos);
		str = term.fio.surname + StrSpace(25 - term.fio.surname.length());
		cout << str;
		pos.Y += 2;
		//имя
		gotoXY(pos);
		str = term.fio.name + StrSpace(25 - term.fio.name.length());
		cout << str;
		pos.Y += 2;
		//отчество
		gotoXY(pos);
		str = term.fio.patronym + StrSpace(25 - term.fio.patronym.length());
		cout << str;
		pos.Y += 2;
		//дата рож
		gotoXY(pos);
		cout << term.date_born;
		pos.Y += 2;
		//пол
		gotoXY(pos);
		cout << term.gender;
		pos.Y += 2;
		//улица
		gotoXY(pos);
		str = term.adress.street + StrSpace(25 - term.adress.street.length());
		cout << str;
		pos.Y += 2;
		//дом-кв
		gotoXY(pos);
		str = ConvertIntToStr(term.adress.home) + " - " + ConvertIntToStr(term.adress.flat);
		str += StrSpace(9 - str.length());
		cout << str;
		pos.Y += 2;
		//тел
		gotoXY(pos);
		cout << term.phone_number;
		pos.Y += 2;
		//паспорт
		gotoXY(pos);
		str = term.passport.substr(0, 4);
		cout << str << " ";
		str = term.passport.substr(4, 6);
		cout << str;
	}
	void DemonstrateType_0()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Клиенты");
		string str1 = "";
		string str2 = "";
		string str_ = "";
		string str_mid = "";
		string str_down = "";
		string str_down2 = "";
		str1 += "Код                             Дата                                            ";
		str2 += "закз Фамелия  Имя      Отчество рождения Пол Адрес    дом-кв. Сот.номер  Паспорт";
			str_down2 += " ";
		ConvertIntoWIN1251ToDOS866(str1);
		ConvertIntoWIN1251ToDOS866(str2);
		for (int i = 0; i < 80; i++)
			str_ += Hor;
		str_down2 = str_down = str_mid = str_;
		str1[4] = str1[13] = str1[22] = str1[31] = str1[40] = str1[44] = str1[53] = str1[61] = str1[72] = Ver;
		str2[4] = str2[13] = str2[22] = str2[31] = str2[40] = str2[44] = str2[53] = str2[61] = str2[72] = Ver;
		str_[4] = str_[13] = str_[22] = str_[31] = str_[40] = str_[44] = str_[53] = str_[61] = str_[72] =
			HorDown;
		str_mid[4] = str_mid[13] = str_mid[22] = str_mid[31] = str_mid[40] = str_mid[44] = str_mid[53] = Cross;
		str_mid[61] = str_mid[72] = Cross;
		str_down[4] = str_down[13] = str_down[22] = str_down[31] = str_down[40] = str_down[44] =
			str_down[53] = HorUp;
		str_down[61] = str_down[72] = HorUp;
		str_down2[4] = str_down2[13] = str_down2[22] = str_down2[31] = str_down2[40] = str_down2[44] = str_down2[53] = Ver;
		str_down2[61] = str_down2[72] = Ver;
		SetColor(BRIGHTGREY, BLACK);
		gotoXY(0, 3);
		cout << str_;
		cout << str1;
		cout << str2;
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
		for (list<Struct_client> ::iterator it = clients.begin(); it != clients.end(); it++)
		{
			Struct_client term = *it;
			item.text = "";
			item.text += ConvertIntToStr(term.code_client, 4);
			item.text += Ver;
			item.text += term.fio.surname.substr(0, 8) + StrSpace(8 - term.fio.surname.length());
			item.text += Ver;
			item.text += term.fio.name.substr(0, 8) + StrSpace(8 -
				term.fio.name.length());
			item.text += Ver;
			item.text += term.fio.patronym.substr(0, 8) + StrSpace(8 - term.fio.patronym.length());
			item.text += Ver;
			item.text += term.date_born.substr(0, 6);
			item.text += term.date_born.substr(8, 2);
			item.text += Ver;
			item.text += term.gender;
			item.text += Ver;
			item.text += term.adress.street.substr(0, 8) + StrSpace(8 -
				term.adress.street.length());
			item.text += Ver;
			item.text += (ConvertIntToStr(term.adress.home, 3) + "-" + ConvertIntToStr(term.adress.flat, 3));
			item.text += Ver;
			item.text += term.phone_number.substr(1, 10);
			item.text += Ver;
			item.text += " ";
			item.text += term.passport.substr(4, 6);
			table.AddItem(item, false);
		}
		table.Show();
		int i = 0;
		for (; (i<9) && (i < clients.size()); i++)
		{
			gotoXY(0, 6 + i * 2);
			cout << str_mid << endl;
		}
		gotoXY(0, 6 + i * 2);
		if (clients.size()<8) cout << str_down;
		table.Use();
	}
	void DemonstrateType_1()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Клиенты");
		bool clear = false;
		list<Struct_client> ::iterator right;
		list<Struct_client> ::iterator left;
		left = right = clients.begin();
		right++;
		ShowItems(true, right != clients.end());
		if (left != clients.end()) ShowData(*left, 14, 3);
		if (right != clients.end())ShowData(*right, 55, 3);
		TKey key = kNone;
		while (key != kEsc)
		{
			GetKey(key);
			if ((key == kRight) && (right != clients.end()) && (left != clients.end()))
			{
				if (right != clients.end())right++;
				if (right != clients.end())right++;
				if (left != clients.end())left++;
				if (left != clients.end())left++;
				if (left != clients.end()) ShowData(*left, 14, 3);
				if (right != clients.end())ShowData(*right, 55, 3);
				left++;
				if (left == clients.end())
				{
					ClearArea(BRIGHTGREY, 40, 3, 79, 23);
					clear = true;
				}
				left--;
			}
			if ((key == kLeft) && (right != clients.begin()) && (left != clients.begin()))
			{
				if (clear)
				{
					ShowItems(true, true);
					clear = false;
				}
				if ((right == left) && (left == clients.end()))
				{
					left--;
					left--;
					right--;
				}
				if (right != clients.begin())right--;
				if (right != clients.begin())right--;
				if (left != clients.begin())left--;
				if (left != clients.begin())left--;
				if (left != clients.end()) ShowData(*left, 14, 3);
				if (right != clients.end())ShowData(*right, 55, 3);
			}
		}
	}
	void Demonstrate()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Клиенты");
		if (clients.empty())
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
	list<Struct_client> GetClients()
	{
		return clients;
	}
	~Client()
	{
		clients.clear();
	}
};