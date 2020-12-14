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
class Hotel
{
private:
	string fild_items[9];
	list<Struct_hotel> hotels;
	Struct_hotel TakeStr(string str)
	{
		Struct_hotel term;
		string take;
		// код отеля 4
		take = str.substr(0, 4);
		term.code_hotel = ConvertStrToInt(take);
		str.erase(0, 4);
		// наимен 25
		take = str.substr(0, 25);
		term.title = DeleteUselessSpace(take);
		str.erase(0, 25);
		// Старана 25
		take = str.substr(0, 25);
		term.country = DeleteUselessSpace(take);
		str.erase(0, 25);
		// Город 25
		take = str.substr(0, 25);
		term.town = DeleteUselessSpace(take);
		str.erase(0, 25);
		// улица 25
		take = str.substr(0, 25);
		term.adress.street = DeleteUselessSpace(take);
		str.erase(0, 25);
		// дом 3
		take = str.substr(0, 3);
		take = DeleteUselessSpace(take);
		term.adress.home = ConvertStrToInt(take);
		str.erase(0, 3);
		// телефон 11
		take = str.substr(0, 11);
		term.phone_number = take;
		str.erase(0, 11);
		// звёзды 1
		take = str.substr(0, 1);
		term.rating_star = ConvertStrToInt(take);
		str.erase(0, 1);
		// контакт. 25
		take = str.substr(0, 25);
		term.contact_person = DeleteUselessSpace(take);
		str.erase(0, 25);
		return term;
	}
	void InitFildItems()
	{
		fild_items[0] = "Код отеля:";
		fild_items[1] = "Наименование:";
		fild_items[2] = "Страна:";
		fild_items[3] = "Город:";
		fild_items[4] = "Улица:";
		fild_items[5] = "Дом:";
		fild_items[6] = "Телефон:";
		fild_items[7] = "Кол-во звёзд:";
		fild_items[8] = "Администратор:";
		for (int i = 0; i < 9; i++)
			ConvertIntoWIN1251ToDOS866(fild_items[i]);
	}
public:
	Hotel(bool empty = false)
	{
		InitFildItems();
		if (!empty) ReadFromFile("Отели.txt");
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
			Struct_hotel term = TakeStr(read);
			hotels.push_back(term);
		}
		input.close();
		return;
	}
	void ShowItems(bool _l = true, bool _r = true)
	{
		SetColor(BRIGHTGREY, BLACK);
		if (_l)
		{
			for (int i = 0; i < 9; i++)
			{
				gotoXY(0, 3 + i * 2);
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
			for (int i = 0; i < 9; i++)
			{
				gotoXY(41, 3 + i * 2);
				cout << fild_items[i];
			}
		}
	}
	void ShowData(Struct_hotel term, short x, short y)
	{
		SetColor(BRIGHTGREY, BLACK);
		Point pos;
		pos.X = x;
		pos.Y = y;
		//код
		gotoXY(pos);
		string str = ConvertIntToStr(term.code_hotel, 4);
		cout << str;
		pos.Y += 2;
		//наим
		gotoXY(pos);
		str = term.title + StrSpace(25 - term.title.length());
		cout << str;
		pos.Y += 2;
		//страна
		gotoXY(pos);
		str = term.country + StrSpace(25 - term.country.length());
		cout << str;
		pos.Y += 2;
		//город
		gotoXY(pos);
		str = term.town + StrSpace(25 - term.town.length());
		cout << str;
		pos.Y += 2;
		//Улица
		gotoXY(pos);
		str = term.adress.street + StrSpace(25 - term.adress.street.length());
		cout << str;
		pos.Y += 2;
		//дом
		gotoXY(pos);
		str = ConvertIntToStr(term.adress.home);
		str += StrSpace(3 - str.length());
		cout << str;
		pos.Y += 2;
		//тел
		gotoXY(pos);
		cout << term.phone_number;
		pos.Y += 2;
		//звезды
		gotoXY(pos);
		cout << term.rating_star;
		pos.Y += 2;
		//админ
		gotoXY(pos);
		str = term.contact_person + StrSpace(25 - term.contact_person.length());
		cout << str;
	}
	void DemonstrateType_0()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Отели");
		string str1 = "";
		string str2 = "";
		string str_ = "";
		string str_mid = "";
		string str_down = "";
		string str_down2 = "";
		str1 += "Код                                                                             ";
		str2 += "Отел Наименование           Страна   Город    Адрес    Дом Сот. номер * Админ   ";
			str_down2 += " ";
		ConvertIntoWIN1251ToDOS866(str1);
		ConvertIntoWIN1251ToDOS866(str2);
		for (int i = 0; i < 80; i++)
			str_ += Hor;
		str_down2 = str_down = str_mid = str_;
		str1[4] = str1[27] = str1[36] = str1[45] = str1[54] = str1[58] = str1[69] = str1[71] = Ver;
		str2[4] = str2[27] = str2[36] = str2[45] = str2[54] = str2[58] = str2[69] = str2[71] = Ver;
		str_[4] = str_[27] = str_[36] = str_[45] = str_[54] = str_[58] = str_[69] = str_[71] = HorDown;
		str_mid[4] = str_mid[27] = str_mid[36] = str_mid[45] = str_mid[54] = str_mid[58] = str_mid[69] = str_mid[71] = Cross;
		str_down[4] = str_down[27] = str_down[36] = str_down[45] = str_down[54] = str_down[58] = str_down[69] = str_down[71] = HorUp;
		str_down2[4] = str_down2[27] = str_down2[36] = str_down2[45] = str_down2[54] = str_down2[58] = str_down2[69] = str_down2[71] = Ver;
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
		for (list<Struct_hotel> ::iterator it = hotels.begin(); it != hotels.end(); it++)
		{
			Struct_hotel term = *it;
			item.text = "";
			item.text += ConvertIntToStr(term.code_hotel, 4);
			item.text += Ver;
			item.text += term.title.substr(0, 22) + StrSpace(22 - term.title.length());
			item.text += Ver;
			item.text += term.country.substr(0, 8) + StrSpace(8 - term.country.length());
			item.text += Ver;
			item.text += term.town.substr(0, 8) + StrSpace(8 - term.town.length());
			item.text += Ver;
			item.text += term.adress.street.substr(0, 8) + StrSpace(8 -
				term.adress.street.length());
			item.text += Ver;
			item.text += ConvertIntToStr(term.adress.home, 3);
			item.text += Ver;
			item.text += term.phone_number.substr(1, 10);
			item.text += Ver;
			item.text += ConvertIntToStr(term.rating_star);
			item.text += Ver;
			item.text += term.contact_person.substr(0, 8) + StrSpace(8 - term.contact_person.length());
			table.AddItem(item, false);
		}
		table.Show();
		int i = 0;
		for (; (i<9) && (i < hotels.size()); i++)
		{
			gotoXY(0, 6 + i * 2);
			cout << str_mid << endl;
		}
		gotoXY(0, 6 + i * 2);
		if (hotels.size()<8) cout << str_down;
		table.Use();
	}
	void DemonstrateType_1()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Отели");
		bool clear = false;
		list<Struct_hotel> ::iterator right;
		list<Struct_hotel> ::iterator left;
		left = right = hotels.begin();
		right++;
		ShowItems(true, right != hotels.end());
		if (left != hotels.end()) ShowData(*left, 14, 3);
		if (right != hotels.end())ShowData(*right, 55, 3);
		TKey key = kNone;
		while (key != kEsc)
		{
			GetKey(key);
			if ((key == kRight) && (right != hotels.end()) && (left != hotels.end()))
			{
				if (right != hotels.end())right++;
				if (right != hotels.end())right++;
				if (left != hotels.end())left++;
				if (left != hotels.end())left++;
				if (left != hotels.end()) ShowData(*left, 14, 3);
				if (right != hotels.end())ShowData(*right, 55, 3);
				left++;
				if (left == hotels.end())
				{
					ClearArea(BRIGHTGREY, 40, 3, 79, 23);
					clear = true;
				}
				left--;
			}
			if ((key == kLeft) && (right != hotels.begin()) && (left != hotels.begin()))
			{
				if (clear)
				{
					ShowItems(true, true);
					clear = false;
				}
				if ((right == left) && (left == hotels.end()))
				{
					left--;
					left--;
					right--;
				}
				if (right != hotels.begin())right--;
				if (right != hotels.begin())right--;
				if (left != hotels.begin())left--;
				if (left != hotels.begin())left--;
				if (left != hotels.end()) ShowData(*left, 14, 3);
				if (right != hotels.end())ShowData(*right, 55, 3);
			}
		}
	}
	void Demonstrate()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Отели");
		if (hotels.empty())
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
	list<Struct_hotel> GetHotels()
	{
		return hotels;
	}
	~Hotel()
	{
		hotels.clear();
	}
};