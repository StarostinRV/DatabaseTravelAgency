#pragma once
#include <iostream>
#include <fstream>
#include <string.h> 
#include <list>
#include <set>
#include <iterator>
#include "Menu.h"
#include "Employee.h"
#include "Post.h"
#include "Service.h"
#include "Hotel.h"
#include "Holiday.h"
#include "Client.h"
#include "Console.h"
#include "Types.h"
#include "Instrument.h"
using namespace std;
class Trip
{
private:
	string fild_items[11];
	list<Struct_trip> trips;
	set<string> holiday_title;
	set<string> hotel_country;
	set<string> hotel_title;
	Struct_trip TakeStr(string str)
	{
		Struct_trip term;
		string take;
		// дата 10
		take = str.substr(0, 10);
		term.date_begin = take;
		str.erase(0, 10);
		// дата 10
		take = str.substr(0, 10);
		term.date_end = take;
		str.erase(0, 10);
		// длительность 4
		take = str.substr(0, 4);
		take = DeleteUselessSpace(take);
		term.duration = ConvertStrToInt(take);
		str.erase(0, 4);
		// код отеля 4
		take = str.substr(0, 4);
		term.code_hotel = ConvertStrToInt(take);
		str.erase(0, 4);
		// код вида 4
		take = str.substr(0, 4);
		term.code_holiday = ConvertStrToInt(take);
		str.erase(0, 4);
		// код услуги1 4
		take = str.substr(0, 4);
		term.code_service_1 = -1;
		if (take != " ") term.code_service_1 = ConvertStrToInt(take);
		str.erase(0, 4);
		// код услуги2 4
		take = str.substr(0, 4);
		term.code_service_2 = -1;
		if (take != " ") term.code_service_2 = ConvertStrToInt(take);
		str.erase(0, 4);
		// код услуги3 4
		take = str.substr(0, 4);
		term.code_service_3 = -1;
		if (take != " ") term.code_service_3 = ConvertStrToInt(take);
		str.erase(0, 4);
		// код клиента 4
		take = str.substr(0, 4);
		term.code_client = -1;
		if (take != " ") term.code_client = ConvertStrToInt(take);
		str.erase(0, 4);
		// код сотрудника 4
		take = str.substr(0, 4);
		term.code_employee = ConvertStrToInt(take);
		str.erase(0, 4);
		// бронь 1
		take = str.substr(0, 1);
		term.checked_reservation = (take == "+");
		str.erase(0, 1);
		// оплата 1
		take = str.substr(0, 1);
		term.checked_payment = (take == "+");
		str.erase(0, 1);
		return term;
	}
	void InitFildItems()
	{
		fild_items[0] = "Даты:";
		fild_items[1] = "Длительность:";
		fild_items[2] = "Код отеля:";
		fild_items[3] = "Код отдыха:";
		fild_items[4] = "Код услуги 1:";
		fild_items[5] = "Код услуги 2:";
		fild_items[6] = "Код услуги 3:";
		fild_items[7] = "Код клиента:";
		fild_items[8] = "Код работника:";
		fild_items[9] = "Бронирование:";
		fild_items[10] = "Оплата:";
		for (int i = 0; i<11; i++)
			ConvertIntoWIN1251ToDOS866(fild_items[i]);
	}
public:
	Trip(Employee t_emp, Service t_ser, Hotel t_hot, Holiday t_hol, Client t_client,
		bool empty = false)
	{
		InitFildItems();
		if (!empty)
		{
			ReadFromFile("Путевки.txt");
			list<Struct_employee> buf_emp = t_emp.GetEmployees();
			list<Struct_service> buf_ser = t_ser.GetServices();
			list<Struct_hotel> buf_hot = t_hot.GetHotels();
			list<Struct_holiday> buf_hol = t_hol.GetHolidays();
			list<Struct_client> buf_client = t_client.GetClients();
			list<Struct_employee> ::iterator it_emp;
			list<Struct_service> ::iterator it_ser;
			list<Struct_hotel> ::iterator it_hot;
			list<Struct_holiday> ::iterator it_hol;
			list<Struct_client> ::iterator it_client;
			list<Struct_trip> ::iterator it_trip;
			for (it_trip = trips.begin(); it_trip != trips.end(); it_trip++)
			{
				for (it_emp = buf_emp.begin(); it_emp != buf_emp.end();
					it_emp++)
					if (it_trip->code_employee == it_emp->code_employee)
						it_trip->employee = *it_emp;
				for (it_ser = buf_ser.begin(); it_ser != buf_ser.end(); it_ser++)
				{
					if (it_trip->code_service_1 == it_ser->code_service)
						it_trip->service_1 = *it_ser;
					if (it_trip->code_service_2 == it_ser->code_service)
						it_trip->service_2 = *it_ser;
					if (it_trip->code_service_3 == it_ser->code_service)
						it_trip->service_3 = *it_ser;
				}
				for (it_hot = buf_hot.begin(); it_hot != buf_hot.end(); it_hot++)
					if (it_trip->code_hotel == it_hot->code_hotel) it_trip ->hotel = *it_hot;
				for (it_hol = buf_hol.begin(); it_hol != buf_hol.end(); it_hol++)
					if (it_trip->code_holiday == it_hol->code_holiday)
						it_trip->holiday = *it_hol;
				for (it_client = buf_client.begin(); it_client != buf_client.end();
					it_client++)
					if (it_trip->code_client == it_client->code_client) it_trip ->client = *it_client;
				for (it_hol = buf_hol.begin(); it_hol != buf_hol.end(); it_hol++)
					holiday_title.insert(it_hol->title);
				for (it_hot = buf_hot.begin(); it_hot != buf_hot.end(); it_hot++)
				{
					hotel_country.insert(it_hot->country);
					hotel_title.insert(it_hot->title);
				}
			}
		}
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
			Struct_trip term = TakeStr(read);
			trips.push_back(term);
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
	void ShowData(Struct_trip term, short x, short y)
	{
		SetColor(BRIGHTGREY, BLACK);
		Point pos;
		pos.X = x;
		pos.Y = y;
		string str;
		//даты
		gotoXY(pos);
		str = term.date_begin + " - " + term.date_end;
		cout << str;
		pos.Y += 2;
		//длительность
		gotoXY(pos);
		str = ConvertIntToStr(term.duration);
		str += StrSpace(4 - str.length());
		cout << str;
		pos.Y += 2;
		//код отеля
		gotoXY(pos);
		str = ConvertIntToStr(term.code_hotel, 4);
		cout << str;
		pos.Y += 2;
		//код отдых
		gotoXY(pos);
		str = ConvertIntToStr(term.code_holiday, 4);
		cout << str;
		pos.Y += 2;
		//код услуги 1
		gotoXY(pos);
		str = " ";
		if (term.code_service_1 != -1) str = ConvertIntToStr(term.code_service_1, 4);
		cout << str;
		pos.Y += 2;
		//код услуги 2
		gotoXY(pos);
		str = " ";
		if (term.code_service_2 != -1) str = ConvertIntToStr(term.code_service_2, 4);
		cout << str;
		pos.Y += 2;
		//код услуги 3
		gotoXY(pos);
		str = " ";
		if (term.code_service_3 != -1) str = ConvertIntToStr(term.code_service_3, 4);
		cout << str;
		pos.Y += 2;
		//код клиента
		gotoXY(pos);
		str = " ";
		if (term.code_client != -1) str = ConvertIntToStr(term.code_client, 4);
		cout << str;
		pos.Y += 2;
		//код сотрудника
		gotoXY(pos);
		str = ConvertIntToStr(term.code_employee, 4);
		cout << str;
		pos.Y += 2;
		// брони
		gotoXY(pos);
		if (term.checked_reservation) str = "+";
		else str = "-";
		cout << str;
		pos.Y += 2;
		// брони
		gotoXY(pos);
		if (term.checked_payment) str = "+";
		else str = "-";
		cout << str;
		pos.Y += 2;
	}
	void DemonstrateType_0()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Путёвки");
		string str1 = "";
		string str2 = "";
		string str_ = "";
		string str_mid = "";
		string str_down = "";
		string str_down2 = "";
		str1 += "Дата       Дата       Код  Код  Код  Код  Код  Код  Код       Отм       Отм     ";
		str2 += "начала     конца      Длит отел вида усл1 усл2 усл3 закз сотр брони     оплате  ";
		str_down2 += " ";
		ConvertIntoWIN1251ToDOS866(str1);
		ConvertIntoWIN1251ToDOS866(str2);
		for (int i = 0; i < 80; i++)
			str_ += Hor;
		str_down2 = str_down = str_mid = str_;
		str1[10] = str1[21] = str1[26] = str1[31] = str1[36] = str1[41] = str1[46] = str1[51] = str1[56] = str1[61] = str1[71] = Ver;
		str2[10] = str2[21] = str2[26] = str2[31] = str2[36] = str2[41] = str2[46] = str2[51] = str2[56] = str2[61] = str2[71] = Ver;
		str_[10] = str_[21] = str_[26] = str_[31] = str_[36] = str_[41] = str_[46] = str_[51] = str_[56] = str_[61] = str_[71] = HorDown;
		str_mid[10] = str_mid[21] = str_mid[26] = str_mid[31] = str_mid[36] = str_mid[41] = str_mid[46] = Cross;
		str_mid[51] = str_mid[56] = str_mid[61] = str_mid[71] = Cross;
		str_down[10] = str_down[21] = str_down[26] = str_down[31] = str_down[36] = str_down[41]= str_down[46] = HorUp;
		str_down[51] = str_down[56] = str_down[61] = str_down[71] = HorUp;
		str_down2[10] = str_down2[21] = str_down2[26] = str_down2[31] = str_down2[36] = str_down2[41] = str_down2[46] = Ver;
		str_down2[51] = str_down2[56] = str_down2[61] = str_down2[71] = Ver;
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
		for (list<Struct_trip> ::iterator it = trips.begin(); it != trips.end(); it++)
		{
			Struct_trip term = *it;
			item.text = "";
			item.text += term.date_begin;
			item.text += Ver;
			item.text += term.date_end;
			item.text += Ver;
			string dur = ConvertIntToStr(term.duration);
			item.text += StrSpace(4 - dur.length()) + dur;
			item.text += Ver;
			if (term.code_hotel != -1) item.text += ConvertIntToStr(term.code_client, 4);
			else item.text += " ";
			item.text += Ver;
			if (term.code_holiday != -1) item.text += ConvertIntToStr(term.code_holiday, 4);
			else item.text += " ";
			item.text += Ver;
			if (term.code_service_1 != -1) item.text += ConvertIntToStr(term.code_service_1, 4);
			else item.text += " ";
			item.text += Ver;
			if (term.code_service_2 != -1) item.text += ConvertIntToStr(term.code_service_2, 4);
			else item.text += " ";
			item.text += Ver;
			if (term.code_service_3 != -1) item.text += ConvertIntToStr(term.code_service_3, 4);
			else item.text += " ";
			item.text += Ver;
			if (term.code_client != -1) item.text += ConvertIntToStr(term.code_client, 4);
			else item.text += " ";
			item.text += Ver;
			if (term.code_employee != -1) item.text += ConvertIntToStr(term.code_employee, 4);
			else item.text += " ";
			item.text += Ver;
			item.text += StrSpace(8) + (term.checked_reservation ? "+" : "-");
			item.text += Ver;
			item.text += StrSpace(7) + (term.checked_payment ? "+" : "-");
			table.AddItem(item, false);
		}
		table.Show();
		int i = 0;
		for (; (i<9) && (i < trips.size()); i++)
		{
			gotoXY(0, 6 + i * 2);
			cout << str_mid << endl;
		}
		gotoXY(0, 6 + i * 2);
		if (trips.size()<8) cout << str_down;
		table.Use();
	}

	void DemonstrateType_1()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Путёвки");
		bool clear = false;
		list<Struct_trip> ::iterator right;
		list<Struct_trip> ::iterator left;
		left = right = trips.begin();
		right++;
		ShowItems(true, right != trips.end());
		if (left != trips.end()) ShowData(*left, 14, 3);
		if (right != trips.end())ShowData(*right, 55, 3);
		TKey key = kNone;
		while (key != kEsc)
		{
			GetKey(key);
			if ((key == kRight) && (right != trips.end()) && (left != trips.end()))
			{
				if (right != trips.end())right++;
				if (right != trips.end())right++;
				if (left != trips.end())left++;
				if (left != trips.end())left++;
				if (left != trips.end()) ShowData(*left, 14, 3);
				if (right != trips.end())ShowData(*right, 55, 3);
				left++;
				if (left == trips.end())
				{
					ClearArea(BRIGHTGREY, 40, 3, 79, 23);
					clear = true;
				}
				left--;
			}
			if ((key == kLeft) && (right != trips.begin()) && (left != trips.begin()))
			{
				if (clear)
				{
					ShowItems(true, true);
					clear = false;
				}
				if ((right == left) && (left == trips.end()))
				{
					left--;
					left--;
					right--;
				}
				if (right != trips.begin())right--;
				if (right != trips.begin())right--;
				if (left != trips.begin())left--;
				if (left != trips.begin())left--;
				if (left != trips.end()) ShowData(*left, 14, 3);
				if (right != trips.end())ShowData(*right, 55, 3);
			}
		}
	}
	void Demonstrate()
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
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
		gotoXY(34, 1);
		string name = "Путёвки";
		ConvertIntoWIN1251ToDOS866(name);
		cout << name;
		for (int i = 0; i < 78; i++)
		{
			gotoXY(1 + i, 0);
			cout << Hor;
			gotoXY(1 + i, 2);
			cout << Hor;
		}
		if (trips.empty())
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
		Menu main_filtr;
		Point pos;
		pos.X = 4;
		pos.Y = 3;
		Item item;
		item.checked = false;
		main_filtr.SetTypeMenu(1);
		main_filtr.SetNShow(7);
		main_filtr.SetPosition(pos);
		main_filtr.SetAddSpace(3);
		main_filtr.AddKey(kEnter);
		main_filtr.AddKey(kRight);
		main_filtr.AddKey(kUp);
		main_filtr.AddKey(kDown);
		main_filtr.SetFrame(true);
		main_filtr.SetMenuColor(BLACK, BLACK, BLACK, BRIGHTGREY, YELLOY, BRIGHTGREY);
		item.text = "Виды отдыха";
		main_filtr.AddItem(item, true);
		item.text = "Страны";
		main_filtr.AddItem(item, true);
		item.text = "Отели";
		main_filtr.AddItem(item, true);
		item.text = "Отметка о брони";
		main_filtr.AddItem(item, true);
		item.text = "Отметка об оплате";
		main_filtr.AddItem(item, true);
		item.text = "Заказанные";
		main_filtr.AddItem(item, true);
		item.text = "Далее";
		main_filtr.AddItem(item, true);
		item.text = "Назад";
		main_filtr.AddItem(item, true);
		pos.X = 45;
		pos.Y = 3;
		Menu menu_holiday;
		item.checked = false;
		menu_holiday.SetNShow(7);
		menu_holiday.SetChecked(true);
		menu_holiday.SetWidth(25);
		menu_holiday.SetTypeMenu(2);
		menu_holiday.SetPosition(pos);
		menu_holiday.SetAlignment(_Left);
		menu_holiday.AddKey(kEsc);
		menu_holiday.AddKey(kLeft);
		menu_holiday.SetFrame(true);
		menu_holiday.SetMenuColor(BLACK, BLACK, BLACK, BRIGHTGREY, RED, BRIGHTRED);
		for (set<string> ::iterator it = holiday_title.begin(); it != holiday_title.end();
			it++)
		{
			item.text = *it;
			menu_holiday.AddItem(item, false);
		}
		Menu menu_country;
		item.checked = false;
		menu_country.SetNShow(7);
		menu_country.SetChecked(true);
		menu_country.SetWidth(25);
		menu_country.SetTypeMenu(2);
		menu_country.SetPosition(pos);
		menu_country.SetAlignment(_Left);
		menu_country.AddKey(kEsc);
		menu_country.AddKey(kLeft);
		menu_country.SetFrame(true);
		menu_country.SetMenuColor(BLACK, BLACK, BLACK, BRIGHTGREY, RED, BRIGHTRED);
		for (set<string> ::iterator it = hotel_country.begin(); it != hotel_country.end(); it++)
		{
			item.text = *it;
			menu_country.AddItem(item, false);
		}
		Menu menu_hotel;
		item.checked = false;
		menu_hotel.SetNShow(7);
		menu_hotel.SetChecked(true);
		menu_hotel.SetWidth(25);
		menu_hotel.SetTypeMenu(2);
		menu_hotel.SetPosition(pos);
		menu_hotel.SetAlignment(_Left);
		menu_hotel.AddKey(kEsc);
		menu_hotel.AddKey(kLeft);
		menu_hotel.SetFrame(true);
		menu_hotel.SetMenuColor(BLACK, BLACK, BLACK, BRIGHTGREY, RED, BRIGHTRED);
		for (set<string> ::iterator it = hotel_title.begin(); it != hotel_title.end(); it++)
		{
			item.text = *it;
			menu_hotel.AddItem(item, false);
		}
		Menu menu_reserv;
		item.checked = false;
		menu_reserv.SetNShow(7);
		menu_reserv.SetChecked(true);
		menu_reserv.SetWidth(25);
		menu_reserv.SetTypeMenu(2);
		menu_reserv.SetPosition(pos);
		menu_reserv.SetAlignment(_Left);
		menu_reserv.AddKey(kEsc);
		menu_reserv.AddKey(kLeft);
		menu_reserv.SetFrame(true);
		menu_reserv.SetMenuColor(BLACK, BLACK, BLACK, BRIGHTGREY, RED, BRIGHTRED);
		item.text = "+";
		menu_reserv.AddItem(item, true);
		item.text = "-";
		menu_reserv.AddItem(item, true);
		Menu menu_payment;
		item.checked = false;
		menu_payment.SetNShow(7);
		menu_payment.SetChecked(true);
		menu_payment.SetWidth(25);
		menu_payment.SetTypeMenu(2);
		menu_payment.SetPosition(pos);
		menu_payment.SetAlignment(_Left);
		menu_payment.AddKey(kEsc);
		menu_payment.AddKey(kLeft);
		menu_payment.SetFrame(true);
		menu_payment.SetMenuColor(BLACK, BLACK, BLACK, BRIGHTGREY, RED, BRIGHTRED);
		item.text = "+";
		menu_payment.AddItem(item, true);
		item.text = "-";
		menu_payment.AddItem(item, true);
		Menu menu_booking;
		item.checked = false;
		menu_booking.SetNShow(7);
		menu_booking.SetChecked(true);
		menu_booking.SetWidth(25);
		menu_booking.SetTypeMenu(2);
		menu_booking.SetPosition(pos);
		menu_booking.SetAlignment(_Left);
		menu_booking.AddKey(kEsc);
		menu_booking.AddKey(kLeft);
		menu_booking.SetFrame(true);
		menu_booking.SetMenuColor(BLACK, BLACK, BLACK, BRIGHTGREY, RED, BRIGHTRED);
		item.text = "+";
		menu_booking.AddItem(item, true);
		item.text = "-";
		menu_booking.AddItem(item, true);
		bool isExit = false;
		while (!isExit)
		{
			if (show)
			{
				show = false;
				Clear(BRIGHTGREY);
				SetColor(BRIGHTGREY, BLACK);
				Title("Список путёвок");
				ShowItems(false, false);
				if (main_filtr.GetActiveItem() == 0) menu_holiday.Show();
			}
			main_filtr.Show();
			main_filtr.Use();
			TKey key = main_filtr.GetStopKey();
			int n = main_filtr.GetActiveItem();
			if (n == 0)
			{
				menu_holiday.Show();
				if ((key == kEnter) || (key == kRight)) menu_holiday.Use();
			}
			else if (n == 1)
			{
				menu_holiday.Hide();
				menu_hotel.Hide();
				menu_country.Show();
				if ((key == kEnter) || (key == kRight)) menu_country.Use();
			}
			else if (n == 2)
			{
				menu_country.Hide();
				menu_reserv.Hide();
				menu_hotel.Show();
				if ((key == kEnter) || (key == kRight)) menu_hotel.Use();
			}
			else if (n == 3)
			{
				menu_hotel.Hide();
				menu_reserv.Show();
				if ((key == kEnter) || (key == kRight)) menu_reserv.Use();
			}
			else if (n == 4)
			{
				menu_payment.Show();
				if ((key == kEnter) || (key == kRight)) menu_payment.Use();
			}
			else if (n == 5)
			{
				menu_booking.Show();
				if ((key == kEnter) || (key == kRight)) menu_booking.Use();
			}
			else if (n == 6)
			{
				menu_booking.Hide();
				if (key == kEnter)
				{
					show = true;
					set<string> rule_holiday;
					set<string> rule_country;
					set<string> rule_hotel;
					set<string> rule_payment;
					set<string> rule_reserv;
					set<string> rule_booking;
					vector<Item> item_holiday = menu_holiday.GetItems();
					vector<Item> item_country = menu_country.GetItems();
					vector<Item> item_hotel = menu_hotel.GetItems();
					vector<Item> item_payment = menu_payment.GetItems();
					vector<Item> item_reserv = menu_reserv.GetItems();
					vector<Item> item_booking = menu_booking.GetItems();
					for (int i = 0; i < item_holiday.size(); i++)
						if (item_holiday[i].checked) rule_holiday.insert(item_holiday[i].text);
					for (int i = 0; i < item_country.size(); i++)
						if (item_country[i].checked) rule_country.insert(item_country[i].text);
					for (int i = 0; i < item_hotel.size(); i++)
						if (item_hotel[i].checked) rule_hotel.insert(item_hotel[i].text);
					for (int i = 0; i < item_payment.size(); i++)
						if (item_payment[i].checked) rule_payment.insert(item_payment[i].text);
					for (int i = 0; i < item_reserv.size(); i++)
						if (item_reserv[i].checked) rule_reserv.insert(item_reserv[i].text);
					for (int i = 0; i < item_booking.size(); i++)
						if (item_booking[i].checked) rule_booking.insert(item_booking[i].text);
					if (rule_holiday.size() == 0) rule_holiday = holiday_title;
					if (rule_country.size() == 0) rule_country = hotel_country;
					if (rule_hotel.size() == 0) rule_hotel = hotel_title;
					if (rule_payment.size() == 0)
					{
						rule_payment.insert("+");
						rule_payment.insert("-");
					}
					if (rule_reserv.size() == 0)
					{
						rule_reserv.insert("+");
						rule_reserv.insert("-");
					}
					if (rule_booking.size() == 0)
					{
						rule_booking.insert("+");
						rule_booking.insert("-");
					}
					DemonstrateWithRules(rule_holiday, rule_country, rule_hotel, rule_payment, rule_reserv, rule_booking);
				}
			}
			else if (n == 7)
			{
				menu_holiday.Hide();
				if (key == kEnter) isExit = true;
			}
		}
	}
	void DemonstrateWithRules_0(set<string> rule_holiday, set<string> rule_country, set<string> rule_hotel, set<string> rule_payment, set<string> rule_reserv, set<string>
		rule_booking, list<Struct_trip> ::iterator now)
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Список путевок");
		string str1 = "";
		string str2 = "";
		string str_ = "";
		string str_mid = "";
		string str_down = "";
		string str_down2 = "";
		str1 += "Дата       Дата       Код  Код  Код  Код  Код  Код  Код       Отм       Отм     ";
		str2 += "начала     конца      Длит отел вида усл1 усл2 усл3 закз сотр брони     оплате  ";
		str_down2 += " ";
		ConvertIntoWIN1251ToDOS866(str1);
		ConvertIntoWIN1251ToDOS866(str2);
		for (int i = 0; i < 80; i++)
			str_ += Hor;
		str_down2 = str_down = str_mid = str_;
		str1[10] = str1[21] = str1[26] = str1[31] = str1[36] = str1[41] = str1[46] = str1[51] = str1[56] = str1[61] = str1[71] = Ver;
		str2[10] = str2[21] = str2[26] = str2[31] = str2[36] = str2[41] = str2[46] = str2[51] = str2[56] = str2[61] = str2[71] = Ver;
		str_[10] = str_[21] = str_[26] = str_[31] = str_[36] = str_[41] = str_[46] = str_[51] = str_[56] = str_[61] = str_[71] = HorDown;
		str_mid[10] = str_mid[21] = str_mid[26] = str_mid[31] = str_mid[36] = str_mid[41] = str_mid[46] = Cross;
		str_mid[51] = str_mid[56] = str_mid[61] = str_mid[71] = Cross;
		str_down[10] = str_down[21] = str_down[26] = str_down[31] = str_down[36] = str_down[41] = str_down[46] = HorUp;
		str_down[51] = str_down[56] = str_down[61] = str_down[71] = HorUp;
		str_down2[10] = str_down2[21] = str_down2[26] = str_down2[31] = str_down2[36] = str_down2[41] = str_down2[46] = Ver;
		str_down2[51] = str_down2[56] = str_down2[61] = str_down2[71] = Ver;
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
		for (list<Struct_trip> ::iterator it = now; it != trips.end(); it++)
		{
			Struct_trip term = *it;
			item.text = "";
			bool b1, b2, b3, b4, b5, b6;
			b1 = b2 = b3 = b4 = b5 = b6 = false;
			b1 = (rule_holiday.find(term.holiday.title) != rule_holiday.end());
			b2 = (rule_country.find(term.hotel.country) != rule_country.end());
			b3 = (rule_hotel.find(term.hotel.title) != rule_hotel.end());
			b4 = (term.checked_payment && (rule_payment.find("+") != rule_payment.end()));
			b4 = (b4 || (!term.checked_payment && (rule_payment.find("-") != rule_payment.end())));
			b5 = (term.checked_reservation && (rule_reserv.find("+") != rule_reserv.end()));
			b5 = (b5 || (!term.checked_reservation && (rule_reserv.find("-") != rule_reserv.end())));
			b6 = ((term.code_client != -1) && (rule_booking.find("+") != rule_booking.end()));
			b6 = (b6 || ((term.code_client == -1) && (rule_booking.find("-") != rule_booking.end())));
			if (!(b1 && b2 && b3 && b4 && b5 && b6)) continue;
			item.text += term.date_begin;
			item.text += Ver;
			item.text += term.date_end;
			item.text += Ver;
			string dur = ConvertIntToStr(term.duration);
			item.text += StrSpace(4 - dur.length()) + dur;
			item.text += Ver;
			if (term.code_hotel != -1) item.text += ConvertIntToStr(term.code_client, 4);
			else item.text += " ";
			item.text += Ver;
			if (term.code_holiday != -1) item.text += ConvertIntToStr(term.code_holiday, 4);
			else item.text += " ";
			item.text += Ver;
			if (term.code_service_1 != -1) item.text += ConvertIntToStr(term.code_service_1, 4);
			else item.text += " ";
			item.text += Ver;
			if (term.code_service_2 != -1) item.text += ConvertIntToStr(term.code_service_2, 4);
			else item.text += " ";
			item.text += Ver;
			if (term.code_service_3 != -1) item.text += ConvertIntToStr(term.code_service_3, 4);
			else item.text += " ";
			item.text += Ver;
			if (term.code_client != -1) item.text += ConvertIntToStr(term.code_client, 4);
			else item.text += " ";
			item.text += Ver;
			if (term.code_employee != -1) item.text += ConvertIntToStr(term.code_employee, 4);
			else item.text += " ";
			item.text += Ver;
			item.text += StrSpace(8) + (term.checked_reservation ? "+" : "-");
			item.text += Ver;
			item.text += StrSpace(7) + (term.checked_payment ? "+" : "-");
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
			cout << str_mid << endl;
		}
		gotoXY(0, 6 + i * 2);
		if (table.GetSizeItems()<8) cout << str_down;
		table.Use();
	}

	void DemonstrateWithRules_1(set<string> rule_holiday, set<string> rule_country, set<string> rule_hotel, set<string> rule_payment, set<string> rule_reserv, set<string>
		rule_booking, list<Struct_trip> ::iterator now, list<Struct_trip> ::iterator begin)
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Список путевок");
		bool isExit;
		Menu menu;
		Point pos;
		pos.X = 0;
		pos.Y = 7;
		Item item;
		item.checked = false;
		menu.SetPosition(pos);
		menu.SetDistance(1);
		menu.SetAlignment(_Left);
		menu.AddKey(kEsc);
		menu.AddKey(kLeft);
		menu.AddKey(kRight);
		menu.AddKey(kUp);
		menu.AddKey(kDown);
		menu.SetFrame(false);
		menu.SetMenuColor(BLACK, BLACK, BLACK, BRIGHTGREY, YELLOY, BRIGHTGREY);
		for (int i = 2; i <= 8; i++)
		{
			item.text = fild_items[i];
			menu.AddItem(item, false);
		}
		Employee employee;
		Service service;
		Hotel hotel;
		Holiday holiday;
		Client client;
		ShowItems(true, false);
		hotel.ShowItems(false, true);
		ShowData(*now, 14, 3);
		hotel.ShowData(now->hotel, 55, 3);
		TKey key = kNone;
		bool l_border, r_border;
		l_border = true;
		r_border = false;
		while (key != kEsc)
		{
			menu.Show();
			menu.Use();
			key = menu.GetStopKey();
			if ((key == kUp) || (key == kDown))
			{
				ClearArea(BRIGHTGREY, 40, 3, 79, 23);
				int n = menu.GetActiveItem();
				if (n == 0) {
					hotel.ShowItems(false, true); hotel.ShowData(now ->hotel, 55, 3);
				}
				else if (n == 1) { holiday.ShowItems(false, true); holiday.ShowData(now->holiday, 55, 3); }
				else if ((n == 2) && (now->code_service_1 != -1)) { service.ShowItems(false, true); service.ShowData(now->service_1, 55, 3); }
				else if ((n == 3) && (now->code_service_2 != -1)) { service.ShowItems(false, true); service.ShowData(now->service_2, 55, 3); }
				else if ((n == 4) && (now->code_service_3 != -1)) { service.ShowItems(false, true); service.ShowData(now->service_3, 55, 3); }
				else if ((n == 5) && (now->code_client != -1)) { client.ShowItems(false, true); client.ShowData(now->client, 55, 3); }
				else if (n == 6) { employee.ShowItems(false, true); employee.ShowData(now->employee, 55, 3); }
			}
			if ((key == kRight) && !r_border)
			{
				list<Struct_trip> ::iterator it = now;
				it++;
				isExit = false;
				while ((it != trips.end()) && !isExit)
				{
					bool b1, b2, b3, b4, b5, b6;
					b1 = b2 = b3 = b4 = b5 = b6 = false;
					Struct_trip term = *it;
					b1 = (rule_holiday.find(term.holiday.title) != rule_holiday.end());
					b2 = (rule_country.find(term.hotel.country) !=
						rule_country.end());
					b3 = (rule_hotel.find(term.hotel.title) != rule_hotel.end());
					b4 = (term.checked_payment && (rule_payment.find("+") != rule_payment.end()));
					b4 = (b4 || (!term.checked_payment && (rule_payment.find("-") != rule_payment.end())));
					b5 = (term.checked_reservation &&
						(rule_reserv.find("+") != rule_reserv.end()));
					b5 = (b5 || (!term.checked_reservation &&
						(rule_reserv.find("-") != rule_reserv.end())));
					b6 = ((term.code_client != -1) && (rule_booking.find("+") != rule_booking.end()));
					b6 = (b6 || ((term.code_client == -1) && (rule_booking.find("-") != rule_booking.end())));
					if (b1 && b2 && b3 && b4 && b5 && b6) isExit = true;
					else ++it;
				}
				if (!isExit) r_border = true;
				else
				{
					now = it;
					ShowData(*now, 14, 3);
					int n = menu.GetActiveItem();
					switch (n)
					{
					case 0:
					{
						hotel.ShowItems(false, true);
						hotel.ShowData(now->hotel, 55, 3);
						break;
					}
					case 1:
					{
						holiday.ShowItems(false, true);
						holiday.ShowData(now->holiday, 55, 3);
						break;
					}
					case 2:
					{
						if (now->code_service_1 == -1)
							ClearArea(BRIGHTGREY, 40, 3, 79, 23);
						else
						{
							service.ShowItems(false, true);
							service.ShowData(now->service_1, 55, 3);
						}
						break;
					}
					case 3:
					{
						if (now->code_service_2 == -1)
							ClearArea(BRIGHTGREY, 40, 3, 79, 23);
						else
						{
							service.ShowItems(false, true);
							service.ShowData(now->service_2, 55, 3);
						}
						break;
					}
					case 4:
					{
						if (now->code_service_3 == -1)
							ClearArea(BRIGHTGREY, 40, 3, 79, 23);
						else
						{
							service.ShowItems(false, true);
							service.ShowData(now->service_3, 55, 3);
						}
						break;
					}
					case 5:
					{
						if (now->code_client == -1)
							ClearArea(BRIGHTGREY, 40, 3, 79, 23);
						else
						{
							client.ShowItems(false, true);
							client.ShowData(now->client, 55, 3);
						}
						break;
					}
					case 6:
					{
						employee.ShowItems(false, true);
						employee.ShowData(now->employee, 55, 3);
						break;
					}
					}
					l_border = false;
				}
			}
			if ((key == kLeft) && !l_border)
			{
				list<Struct_trip> ::iterator it = now;
				isExit = false;
				while ((it != begin) && !isExit)
				{
					--it;
					bool b1, b2, b3, b4, b5, b6;
					b1 = b2 = b3 = b4 = b5 = b6 = false;
					Struct_trip term = *it;
					b1 = (rule_holiday.find(term.holiday.title) != rule_holiday.end());
					b2 = (rule_country.find(term.hotel.country) !=
						rule_country.end());
					b3 = (rule_hotel.find(term.hotel.title) != rule_hotel.end());
					b4 = (term.checked_payment && (rule_payment.find("+") != rule_payment.end()));
					b4 = (b4 || (!term.checked_payment && (rule_payment.find("-") != rule_payment.end())));
					b5 = (term.checked_reservation &&
						(rule_reserv.find("+") != rule_reserv.end()));
					b5 = (b5 || (!term.checked_reservation &&
						(rule_reserv.find("-") != rule_reserv.end())));
					b6 = ((term.code_client != -1) && (rule_booking.find("+") != rule_booking.end()));
					b6 = (b6 || ((term.code_client == -1) && (rule_booking.find("-") != rule_booking.end())));
					if (b1 && b2 && b3 && b4 && b5 && b6) isExit = true;
				}
				if (!isExit) l_border = true;
				else
				{
					now = it;
					ShowData(*now, 14, 3);
					int n = menu.GetActiveItem();
					switch (n)
					{
					case 0:
					{
						hotel.ShowItems(false, true);
						hotel.ShowData(now->hotel, 55, 3);
						break;
					}
					case 1:
					{
						holiday.ShowItems(false, true);
						holiday.ShowData(now->holiday, 55, 3);
						break;
					}
					case 2:
					{
						if (now->code_service_1 == -1)
							ClearArea(BRIGHTGREY, 40, 3, 79, 23);
						else
						{
							service.ShowItems(false, true);
							service.ShowData(now->service_1, 55, 3);
						}
						break;
					}
					case 3:
					{
						if (now->code_service_2 == -1)
							ClearArea(BRIGHTGREY, 40, 3, 79, 23);
						else
						{
							service.ShowItems(false, true);
							service.ShowData(now->service_2, 55, 3);
						}
						break;
					}
					case 4:
					{
						if (now->code_service_3 == -1)
							ClearArea(BRIGHTGREY, 40, 3, 79, 23);
						else
						{
							service.ShowItems(false, true);
							service.ShowData(now->service_3, 55, 3);
						}
						break;
					}
					case 5:
					{
						if (now->code_client == -1)
							ClearArea(BRIGHTGREY, 40, 3, 79, 23);
						else
						{
							client.ShowItems(false, true);
							client.ShowData(now->client, 55, 3);
						}
						break;
					}
					case 6:
					{
						employee.ShowItems(false, true);
						employee.ShowData(now->employee, 55, 3);
						break;
					}
					}
					r_border = false;
				}
			}
		}
	}

	void DemonstrateWithRules(set<string> rule_holiday, set<string> rule_country,
		set<string> rule_hotel, set<string> rule_payment, set<string> rule_reserv, set<string>
		rule_booking)
	{
		Clear(BRIGHTGREY);
		SetColor(BRIGHTGREY, BLACK);
		Title("Список путёвок");
		bool isExit = false;
		list<Struct_trip> ::iterator now = trips.begin();
		list<Struct_trip> ::iterator begin = trips.begin();
		while ((now != trips.end()) && !isExit)
		{
			bool b1, b2, b3, b4, b5, b6;
			b1 = b2 = b3 = b4 = b5 = b6 = false;
			Struct_trip term = *now;
			b1 = (rule_holiday.find(term.holiday.title) != rule_holiday.end());
			b2 = (rule_country.find(term.hotel.country) != rule_country.end());
			b3 = (rule_hotel.find(term.hotel.title) != rule_hotel.end());
			b4 = (term.checked_payment && (rule_payment.find("+") !=
				rule_payment.end()));
			b4 = (b4 || (!term.checked_payment && (rule_payment.find("-") !=
				rule_payment.end())));
			b5 = (term.checked_reservation && (rule_reserv.find("+") !=
				rule_reserv.end()));
			b5 = (b5 || (!term.checked_reservation && (rule_reserv.find("-") !=
				rule_reserv.end())));
			b6 = ((term.code_client != -1) && (rule_booking.find("+") !=
				rule_booking.end()));
			b6 = (b6 || ((term.code_client == -1) && (rule_booking.find("-") !=
				rule_booking.end())));
			if (b1 && b2 && b3 && b4 && b5 && b6) isExit = true;
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
		if (n == 0) DemonstrateWithRules_0(rule_holiday, rule_country, rule_hotel, rule_payment, rule_reserv, rule_booking, now);
		else if (n == 1) DemonstrateWithRules_1(rule_holiday, rule_country, rule_hotel, rule_payment, rule_reserv, rule_booking, now, begin);
	}

	list<Struct_trip> GetTrip()
	{
		return trips;
	}

	~Trip()
	{
		trips.clear();
	}
};