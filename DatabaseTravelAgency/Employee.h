#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <list>
#include <set>
#include <iterator>
#include "Menu.h"
#include "Post.h"
#include "Console.h"
#include "Types.h"
#include "Instrument.h"
using namespace std;
class Employee
{
private:
	string fild_items[11];
	list<Struct_employee> employees;
	set<string> post_names;
	Post post;
	Struct_employee TakeStr(string str)
	{
		Struct_employee term;
		string take;
		// код сотр 4
		take = str.substr(0, 4);
		term.code_employee = ConvertStrToInt(take);
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
		// возвраст 2
		take = str.substr(0, 2);
		take = DeleteUselessSpace(take);
		term.age = ConvertStrToInt(take);
		str.erase(0, 2);
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
		// код дожности 4
		take = str.substr(0, 4);
		term.code_post = ConvertStrToInt(take);
		str.erase(0, 4);
		return term;
	}
	void InitFildItems()
	{
		fild_items[0] = "Код работника:";
		fild_items[1] = "Фамелия:";
		fild_items[2] = "Имя:";
		fild_items[3] = "Отчество:";
		fild_items[4] = "Возвраст:";
		fild_items[5] = "Пол:";
		fild_items[6] = "Улица:";
		fild_items[7] = "Дом/Квартира:";
		fild_items[8] = "Телефон номер:";
		fild_items[9] = "Паспорт";
		fild_items[10] = "Код должности:";
		for (int i = 0; i<11; i++)
			ConvertIntoWIN1251ToDOS866(fild_items[i]);
	}
public:
	Employee(Post term, bool empty = false)
	{
		InitFildItems();
		if (!empty)
		{
			ReadFromFile("Сотрудники.txt");
			list<Struct_post> buf = term.GetPosts();
			list<Struct_post> ::iterator it_post;
			list<Struct_employee> ::iterator it_employee;
			for (it_employee = employees.begin(); it_employee != employees.end(); it_employee++)
				for (it_post = buf.begin(); it_post != buf.end(); it_post++)
					if (it_employee->code_post == it_post->code_post)
						it_employee->post = *it_post;
			for (it_post = buf.begin(); it_post != buf.end(); it_post++)
				post_names.insert(it_post->name);
		}
	}
	Employee()
	{
		InitFildItems();
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
			Struct_employee term = TakeStr(read);
			employees.push_back(term);
		}
		input.close();
		return;
	}
	void ShowItems(bool _l = true, bool _r = true)
	{
		SetColor(BRIGHTGREY, BLACK);
		if (_l)
		{
			for (int i = 0; i < 11; i++)
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
			for (int i = 0; i < 11; i++)
			{
				gotoXY(41, 3 + 2 * i);
				cout << fild_items[i];
			}
		}
	}
	void ShowData(Struct_employee term, short x, short y)
	{
		SetColor(BRIGHTGREY, BLACK);
		Point pos;
		pos.X = x;
		pos.Y = y;
		string str;
		//код сотр
		gotoXY(pos);
		str = ConvertIntToStr(term.code_employee, 4);
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
		//возвраст
		gotoXY(pos);
		str = ConvertIntToStr(term.age);
		str = StrSpace(2 - str.length()) + str;
		cout << str;
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
		pos.Y += 2;
		//код должности
		gotoXY(pos);
		str = ConvertIntToStr(term.code_post, 4);
		cout << str;
	}
	void DemonstrateType_0()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Сотрудники");
		string str1 = "";
		string str2 = "";
		string str_ = "";
		string str_mid = "";
		string str_down = "";
		string str_down2 = "";
		str1 = "Код                                                                         Код ";
		str2 += "cотр Фамелия  Имя      Отчество Age Пол Адрес    дом-кв. Сот.номер  Паспорт долж";
		str_down2 += " ";
		ConvertIntoWIN1251ToDOS866(str1);
		ConvertIntoWIN1251ToDOS866(str2);
		for (int i = 0; i < 80; i++)
			str_ += Hor;
		str_down2 = str_down = str_mid = str_;
		str1[4] = str1[13] = str1[22] = str1[31] = str1[35] = str1[39] = str1[48] = str1[56] = str1[67] = str1[75] = Ver;
		str2[4] = str2[13] = str2[22] = str2[31] = str2[35] = str2[39] = str2[48] = str2[56] = str2[67] = str2[75] = Ver;
		str_[4] = str_[13] = str_[22] = str_[31] = str_[35] = str_[39] = str_[48] = str_[56] = str_[67] = str_[75] = HorDown;
		str_mid[4] = str_mid[13] = str_mid[22] = str_mid[31] = str_mid[35] = str_mid[39] = str_mid[48] = Cross;
		str_mid[56] = str_mid[67] = str_mid[75] = Cross;
		str_down[4] = str_down[13] = str_down[22] = str_down[31] = str_down[35] = str_down[39] = str_down[48] = HorUp;
		str_down[56] = str_down[67] = str_down[75] = HorUp;
		str_down2[4] = str_down2[13] = str_down2[22] = str_down2[31] = str_down2[35] = str_down2[39] = str_down2[48] = Ver;
		str_down2[56] = str_down2[67] = str_down2[75] = Ver;
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
		for (list<Struct_employee> ::iterator it = employees.begin(); it != employees.end(); it++)
		{
			Struct_employee term = *it;
			item.text = "";
			item.text += ConvertIntToStr(term.code_employee, 4);
			item.text += Ver;
			item.text += term.fio.surname.substr(0, 8) + StrSpace(8 - term.fio.surname.length());
			item.text += Ver;
			item.text += term.fio.name.substr(0, 8) + StrSpace(8 -
				term.fio.name.length());
			item.text += Ver;
			item.text += term.fio.patronym.substr(0, 8) + StrSpace(8 - term.fio.patronym.length());
			item.text += Ver;
			item.text += " ";
			item.text += ConvertIntToStr(term.age);
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
			item.text += Ver;
			item.text += ConvertIntToStr(term.code_post, 4);
			table.AddItem(item, false);
		}
		table.Show();
		int i = 0;
		for (; (i<9) && (i < employees.size()); i++)
		{
			gotoXY(0, 6+i*2);
			cout << str_mid;
		}
		gotoXY(0, 6 + i * 2);
		if (employees.size()<8) cout << str_down;
		table.Use();
	}
	void DemonstrateType_1()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Сотрудники");
		bool clear = false;
		list<Struct_employee> ::iterator right;
		list<Struct_employee> ::iterator left;
		left = right = employees.begin();
		right++;
		ShowItems(true, right != employees.end());
		if (left != employees.end()) ShowData(*left, 14, 3);
		if (right != employees.end())ShowData(*right, 55, 3);
		TKey key = kNone;
		while (key != kEsc)
		{
			GetKey(key);
			if ((key == kRight) && (right != employees.end()) && (left != employees.end()))
			{
				if (right != employees.end())right++;
				if (right != employees.end())right++;
				if (left != employees.end())left++;
				if (left != employees.end())left++;
				if (left != employees.end()) ShowData(*left, 14, 3);
				if (right != employees.end())ShowData(*right, 55, 3);
				left++;
				if (left == employees.end())
				{
					ClearArea(BRIGHTGREY, 40, 3, 79, 23);
					clear = true;
				}
				left--;
			}
			if ((key == kLeft) && (right != employees.begin()) && (left != employees.begin()))
			{
				if (clear)
				{
					ShowItems(true, true);
					clear = false;
				}
				if ((right == left) && (left == employees.end()))
				{
					left--;
					left--;
					right--;
				}
				if (right != employees.begin())right--;
				if (right != employees.begin())right--;
				if (left != employees.begin())left--;
				if (left != employees.begin())left--;
				if (left != employees.end()) ShowData(*left, 14, 3);
				if (right != employees.end())ShowData(*right, 55, 3);
			}
		}
	}
	void Demonstrate()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Сотрудники");
		if (employees.empty())
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

	void Filters()
	{
		bool show = true;
		Menu filtr;
		Point pos;
		pos.X = 24;
		pos.Y = 4;
		Item item;
		item.checked = false;
		filtr.SetTypeMenu(2);
		filtr.SetNShow(6);
		filtr.SetChecked(true);
		filtr.SetPosition(pos);
		filtr.SetAddSpace(3);
		filtr.AddKey(kEnter);
		filtr.SetFrame(true);
		filtr.SetMenuColor(BLACK, BLACK, BLACK, BRIGHTGREY, YELLOY, YELLOY);
		for (set<string> ::iterator it = post_names.begin(); it != post_names.end();
			it++)
		{
			item.text = *it;
			filtr.AddItem(item, false);
		}
		item.text = "Далее";
		filtr.AddItem(item, true);
		item.text = "Назад";
		filtr.AddItem(item, true);
		bool isExit = false;
		while (!isExit)
		{
			if (show)
			{
				show = false;
				Clear(BRIGHTGREY);
				SetColor(BRIGHTGREY, BLACK);
				Title("Фильтры");
				gotoXY(34, 3);
				string name = "ДОЛЖНОСТИ";
				ConvertIntoWIN1251ToDOS866(name);
				cout << name;
			}
			filtr.Show();
			filtr.Use();
			int n = filtr.GetActiveItem();
			if ((n + 1) == filtr.GetSizeItems()) isExit = true;
			else if ((n + 2) == filtr.GetSizeItems())
			{
				filtr.SetItemsChecked(n, false);
				set<string> rule;
				vector<Item> term = filtr.GetItems();
				for (int i = 0; i < term.size(); i++)
				{
					if (term[i].checked) rule.insert(term[i].text);
				}
				if (rule.size() == 0) rule = post_names;
				DemonstrateWithRules(rule);
				show = true;
			}
		}
	}

	void DemonstrateWithRules_0(set<string> rule_post, list<Struct_employee> ::iterator now)
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Отдел кадров");
		string str1 = "";
		string str2 = "";
		string str_ = "";
		string str_mid = "";
		string str_down = "";
		string str_down2 = "";
		str1 = "Код                                                                         Код ";
		str2 += "cотр Фамелия  Имя      Отчество Age Пол Адрес    дом-кв. Сот.номер  Паспорт долж";
		str_down2 += " ";
		ConvertIntoWIN1251ToDOS866(str1);
		ConvertIntoWIN1251ToDOS866(str2);
		for (int i = 0; i < 80; i++)
			str_ += Hor;
		str_down2 = str_down = str_mid = str_;
		str1[4] = str1[13] = str1[22] = str1[31] = str1[35] = str1[39] = str1[48] = str1[56] = str1[67] = str1[75] = Ver;
		str2[4] = str2[13] = str2[22] = str2[31] = str2[35] = str2[39] = str2[48] = str2[56] = str2[67] = str2[75] = Ver;
		str_[4] = str_[13] = str_[22] = str_[31] = str_[35] = str_[39] = str_[48] = str_[56] = str_[67] = str_[75] = HorDown;
		str_mid[4] = str_mid[13] = str_mid[22] = str_mid[31] = str_mid[35] = str_mid[39] = str_mid[48] = Cross;
		str_mid[56] = str_mid[67] = str_mid[75] = Cross;
		str_down[4] = str_down[13] = str_down[22] = str_down[31] = str_down[35] = str_down[39] = str_down[48] = HorUp;
		str_down[56] = str_down[67] = str_down[75] = HorUp;
		str_down2[4] = str_down2[13] = str_down2[22] = str_down2[31] = str_down2[35] = str_down2[39] = str_down2[48] = Ver;
		str_down2[56] = str_down2[67] = str_down2[75] = Ver;
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
		for (list<Struct_employee> ::iterator it = now; it != employees.end(); it++)
		{
			if (rule_post.find(it->post.name) == rule_post.end()) continue;
			Struct_employee term = *it;
			item.text = "";
			item.text += ConvertIntToStr(term.code_employee, 4);
			item.text += Ver;
			item.text += term.fio.surname.substr(0, 8) + StrSpace(8 - term.fio.surname.length());
			item.text += Ver;
			item.text += term.fio.name.substr(0, 8) + StrSpace(8 -
				term.fio.name.length());
			item.text += Ver;
			item.text += term.fio.patronym.substr(0, 8) + StrSpace(8 - term.fio.patronym.length());
			item.text += Ver;
			item.text += " ";
			item.text += ConvertIntToStr(term.age);
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
			item.text += Ver;
			item.text += ConvertIntToStr(term.code_post, 4);
			table.AddItem(item, false);
		}
		SetColor(BRIGHTGREY, BLACK);
		gotoXY(0, 3);
		cout << str_;
		cout << str1;
		cout << str2;
		table.Show();
		int i = 0;
		for (; (i<9) && (i < table.GetSizeItems()); i++)
		{
			gotoXY(0, 6 + i * 2);
			cout << str_mid;
		}
		gotoXY(0, 6 + i * 2);
		if (table.GetSizeItems()<8) cout << str_down;
		table.Use();
	}
	void DemonstrateWithRules_1(set<string> rule_post, list<Struct_employee> ::iterator now, list<Struct_employee> ::iterator begin)
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Отдел кадров");
		bool isExit;
		Post term(true);
		ShowItems(true, false);
		term.ShowItems(false, true);
		ShowData(*now, 14, 3);
		term.ShowData(now->post, 55, 3);
		TKey key = kNone;
		bool l_border, r_border;
		l_border = true;
		r_border = false;
		while (key != kEsc)
		{
			GetKey(key);
			if ((key == kRight) && !r_border)
			{
				list<Struct_employee> ::iterator it = now;
				it++;
				isExit = false;
				while ((it != employees.end()) && !isExit)
				{
					if (rule_post.find(it->post.name) != rule_post.end())
						isExit = true;
					else it++;
				}
				if (!isExit) r_border = true;
				else
				{
					now = it;
					ShowData(*now, 14, 3);
					term.ShowData(now->post, 55, 3);
					l_border = false;
				}
			}
			if ((key == kLeft) && !l_border)
			{
				list<Struct_employee> ::iterator it = now;
				isExit = false;
				while ((it != begin) && !isExit)
				{
					it--;
					if (rule_post.find(it->post.name) != rule_post.end())
						isExit = true;
				}
				if (!isExit) l_border = true;
				else
				{
					now = it;
					ShowData(*now, 14, 3);
					term.ShowData(now->post, 55, 3);
					r_border = false;
				}
			}
		}
	}
	void DemonstrateWithRules(set<string> rule_post)
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Отдел кадров");
		bool isExit = false;
		list<Struct_employee> ::iterator now = employees.begin();
		list<Struct_employee> ::iterator begin = employees.begin();
		while ((now != employees.end()) && !isExit)
		{
			if (rule_post.find(now->post.name) != rule_post.end()) isExit = true;
			else ++now;
		}
		begin = now;
		if (!isExit)
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
		if (n == 0) DemonstrateWithRules_0(rule_post, now);
		else if (n == 1) DemonstrateWithRules_1(rule_post, now, begin);
	}
	list<Struct_employee> GetEmployees()
	{
		return employees;
	}
	~Employee()
	{
		employees.clear();
	}
};