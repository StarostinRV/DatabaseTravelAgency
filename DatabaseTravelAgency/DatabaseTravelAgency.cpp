// DatabaseTravelAgency.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string.h>
#include "Console.h"
#include "Types.h"
#include "Instrument.h"
#include "Menu.h"
#include "Employee.h"
#include "Post.h"
#include "Service.h"
#include "Hotel.h"
#include "Holiday.h"
#include "Client.h"
#include "Trip.h"

Post post;
Employee employee(post);
Service service;
Hotel hotel;
Holiday holiday;
Client client;
Trip trip(employee, service, hotel, holiday, client, false);
void Demonstrate()
{
	Menu show;
	Point pos;
	pos.X = 24;
	pos.Y = 3;
	Item item;
	show.SetTypeMenu(1);
	item.checked = false;
	show.SetPosition(pos);
	show.SetNShow(7);
	show.SetAddSpace(3);
	show.AddKey(kEnter);
	show.SetFrame(true);
	show.SetMenuColor(BRIGHTGREY, BLACK, BLACK, BRIGHTGREY, YELLOY, BRIGHTGREY);
	item.text = "Сотрудников";
	show.AddItem(item);
	item.text = "Должностей";
	show.AddItem(item);
	item.text = "Видов отдыха";
	show.AddItem(item);
	item.text = "Отелей";
	show.AddItem(item);
	item.text = "Дополнительных услуг";
	show.AddItem(item);
	item.text = "Клиентов";
	show.AddItem(item);
	item.text = "Путёвок";
	show.AddItem(item);
	item.text = "Назад";
	show.AddItem(item);
	bool isExite = false;
	while (!isExite)
	{
		Clear(BRIGHTGREY);
		Title("Демонстрация");
		show.Show();
		show.Use();
		int n = show.GetActiveItem();
		if (n == 0) employee.Demonstrate();
		else if (n == 1) post.Demonstrate();
		else if (n == 2) holiday.Demonstrate();
		else if (n == 3) hotel.Demonstrate();
		else if (n == 4) service.Demonstrate();
		else if (n == 5) client.Demonstrate();
		else if (n == 6) trip.Demonstrate();
		else if (n == 7) isExite = true;
	}
	Clear(BRIGHTGREY);
}
void Filters()
{
	Point pos;
	pos.X = 31;
	pos.Y = 5;
	Item item;
	item.checked = false;
	Menu filtr_menu;
	filtr_menu.SetTypeMenu(1);
	filtr_menu.SetPosition(pos);
	filtr_menu.SetAddSpace(3);
	filtr_menu.SetDistance(3);
	filtr_menu.AddKey(kEnter);
	filtr_menu.SetFrame(true);
	filtr_menu.SetMenuColor(BLACK, BLACK, BLACK, BRIGHTGREY, YELLOY, BRIGHTGREY);
	item.text = "Отдел кадров";
	filtr_menu.AddItem(item);
	item.text = "Список путёвок";
	filtr_menu.AddItem(item);
	item.text = "Назад";
	filtr_menu.AddItem(item);
	bool isExit = false;
	while (!isExit)
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
		string name = "Запросы";
		ConvertIntoWIN1251ToDOS866(name);
		cout << name;
		for (int i = 0; i < 78; i++)
		{
			gotoXY(1 + i, 0);
			cout << Hor;
			gotoXY(1 + i, 2);
			cout << Hor;
		}
		filtr_menu.Show();
		filtr_menu.Use();
		int n = filtr_menu.GetActiveItem();
		if (n == 0) employee.Filters();
		else if (n == 1) trip.Filters();
		else if (n == 2) isExit = true;
	}
}


int main()
{
		Point pos;
		pos.X = 31;
		pos.Y = 7;
		Item item;
		item.checked = false;
		Menu main_menu;
		main_menu.SetPosition(pos);
		main_menu.SetAddSpace(5);
		main_menu.SetDistance(2);
		main_menu.AddKey(kEnter);
		main_menu.SetFrame(true);
		main_menu.SetMenuColor(BLACK, BLACK, BLACK, BRIGHTGREY, YELLOY, BRIGHTGREY);
		item.text = "Показать";
		main_menu.AddItem(item);
		item.text = "Запросы";
		main_menu.AddItem(item);
		item.text = "Выход";
		main_menu.AddItem(item);
		bool isExit = false;
		while (!isExit)
		{
			Clear(BRIGHTGREY);
			Title("Главное меню");
			main_menu.Show();
			main_menu.Use();
			int n = main_menu.GetActiveItem();
			if (n == 0) Demonstrate();
			else if (n == 1) Filters();
			else if (n == 2) isExit = true;
		}
		return 0;
}

