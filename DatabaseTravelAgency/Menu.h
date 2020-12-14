#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "Console.h"
#include "Types.h"
#include "Instrument.h"
using namespace std;
class Menu
{
private:
	struct Frame
	{
		string _up;
		string _mid;
		string _down;
	};
	struct MenuElement
	{
		Item info;
		Frame frame;
	};
	bool first_show;
	short width;
	Point position;
	TKey stop_key;
	short distance;
	set<TKey> keys_break;
	vector<MenuElement> items;
	Color color_text;
	Color color_active_text;
	Color color_checked_text;
	Color color_back;
	Color color_active_back;
	Color color_checked_back;
	bool IsShow;
	bool IsFrame;
	short begin_show;
	short type_menu;
	TDir dir;
	TAlignment alignment;
	bool visible_checked;
	bool set_n_show;
	short n_show;
	short add_space;
	short active_item;
	void InitMenuElement()
	{
		for (short i = 0; i < items.size(); i++)
			items[i].frame = InitFrame(items[i].info);
	}
	Frame InitFrame(Item item)
	{
		Frame result;
		short len = width + add_space - item.text.length();
		if (alignment == _Right)
		{
			string s = StrSpace(len);
			result._mid = s + item.text;
		}
		else if (alignment == _Left)
		{
			string s = StrSpace(len);
			result._mid = item.text + s;
		}
		else if (alignment == _Mid)
		{
			int l = len / 2;
			int r = (len + 1) / 2;
			string s_l = StrSpace(l);
			string s_r = StrSpace(r);
			result._mid = s_l + item.text + s_r;
		}
		len += item.text.length();
		if (IsFrame)
		{
			for (int i = 0; i < len; i++)
				result._up = result._down += Hor;
			result._up += AngleRightUp;
			result._mid += Ver;
			result._down += AngleRightDown;
			string s;
			s = AngleLeftUp;
			result._up = s + result._up;
			s = Ver;
			result._mid = s + result._mid;
			s = AngleLeftDown;
			result._down = s + result._down;
		}
		return result;
	}
	void InitFirstShow()
	{
		if (n_show > items.size()) n_show = items.size();
		if (active_item > items.size()) active_item = items.size();
		if (active_item > (items.size() - n_show)) begin_show = items.size() -
			n_show;
		else begin_show = active_item;
		if (alignment == _Mid) add_space *= 2;
		if ((dir == _Horizontal) && (type_menu == 2)) distance += 3;
		if ((dir == _Horizontal) && (IsFrame)) distance += 2;
		if (dir == _Horizontal) distance += (width + add_space);
		InitMenuElement();
	}
	void NextItem()
	{
		active_item++;
		if (active_item == begin_show + n_show) begin_show++;
		if (active_item == items.size()) begin_show = active_item -= items.size();
	}
	void PrevItem()
	{
		active_item--;
		if (active_item < begin_show) begin_show--;
		if (active_item == -1)
		{
			begin_show = active_item += items.size();
			begin_show -= (n_show - 1);
		}
	}
public:
	Menu()
	{
		first_show = true;
		dir = _Vertical;
		width = 0;
		position.X = position.Y = 0;
		stop_key = kNone;
		IsShow = false;
		IsFrame = false;
		begin_show = 0;
		type_menu = 1;
		alignment = _Mid;
		visible_checked = false;
		n_show = 0;
		set_n_show = false;
		distance = 0;
		add_space = 0;
		active_item = 0;
		color_checked_text = color_text = color_active_text = BLACK;
		color_back = GREY;
		color_checked_back = color_active_back = YELLOY;
	}
	void SetMenuColor(Color text_checked, Color text_active, Color text, Color back,
		Color back_active, Color back_checked)
	{
		color_text = text;
		color_active_text = text_active;
		color_checked_text = text_checked;
		color_back = back;
		color_active_back = back_active;
		color_checked_back = back_checked;
	}
	void SetChecked(bool visible)
	{
		visible_checked = visible;
	}
	void SetItemsChecked(int N, bool check)
	{
		if (N >= items.size()) return;
		items[N].info.checked = check;
	}
	void SetDir(TDir _dir)
	{
		dir = _dir;
		first_show = true;
	}
	void SetPosition(Point pos)
	{
		position = pos;
	}
	void SetFrame(bool frame)
	{
		IsFrame = frame;
		first_show = true;
	}
	void SetNShow(short N)
	{
		if (N < 0) return;
		n_show = N;
		set_n_show = true;
		first_show = true;
	}
	void SetWidth(short len)
	{
		width = len;
	}
	void SetAddSpace(short N)
	{
		if (N < 0) return;
		add_space = N;
		first_show = true;
	}
	void SetActiveItem(short _active_item)
	{
		if (_active_item < 0) return;
		active_item = _active_item;
	}
	void SetTypeMenu(short N)
	{
		if (N < 1) return;
		if (N > 2) return;
		type_menu = N;
	}
	void SetDistance(short _distance)
	{
		if (_distance < 0) return;
		distance = _distance;
	}
	void SetAlignment(TAlignment _alignment)
	{
		alignment = _alignment;
	}
	vector<Item> GetItems()
	{
		vector<Item> result;
		for (int i = 0; i < items.size(); i++)
		{
			result.push_back(items[i].info);
		}
		return result;
	}
	short GetActiveItem()
	{
		return active_item;
	}
	TKey GetStopKey()
	{
		return stop_key;
	}
	int GetSizeItems()
	{
		return items.size();
	}
	void AddItem(Item item, bool convert = true)
	{
		if (convert) ConvertIntoWIN1251ToDOS866(item.text);
		MenuElement term;
		term.info = item;
		items.push_back(term);
		short i = 0;
		if (item.text.length() > width) width = item.text.length();
		if (!set_n_show) n_show = items.size();
	}
	void AddKey(TKey key)
	{
		keys_break.insert(key);
	}
	void Hide()
	{
		Color text = color_text;
		Color text_active = color_active_text;
		Color text_checked = color_checked_text;
		Color back = color_back;
		Color back_active = color_active_back;
		Color back_checked = color_checked_back;
		SetMenuColor(BRIGHTGREY, BRIGHTGREY, BRIGHTGREY, BRIGHTGREY, BRIGHTGREY, BRIGHTGREY);
		Show();
		SetMenuColor(text_checked, text_active, text, back, back_active, back_checked);
	}
	void Show()
	{
		if (first_show)
		{
			InitFirstShow();
			first_show = false;
		}
		IsShow = true;
		Point pos = position;
		short end_show = begin_show + n_show;
		for (short i = begin_show; i < end_show; i++)
		{
			if ((active_item == i) && type_menu == 1) SetColor(color_active_back, color_active_text);
			else if ((visible_checked) && (items[i].info.checked))
				SetColor(color_checked_back, color_checked_text);
			else SetColor(color_back, color_text);
			if (IsFrame)
			{
				if (type_menu == 2) gotoXY(pos.X + 2, pos.Y);
				else gotoXY(pos);
				cout << items[i].frame._up;
				pos.Y++;
				if (type_menu == 2)
				{
					if (active_item == i) SetColor(color_active_back, color_active_text);
					else SetColor(color_back, color_text);
					gotoXY(pos);
					cout << " ";
					gotoXY(pos.X + 2, pos.Y);
					if ((visible_checked) && (items[i].info.checked))
						SetColor(color_checked_back, color_checked_text);
					else SetColor(color_back, color_text);
				}
				else gotoXY(pos);
				cout << items[i].frame._mid;
				pos.Y++;
				if (type_menu == 2) gotoXY(pos.X + 2, pos.Y);
				else gotoXY(pos);
				cout << items[i].frame._down;
				if (dir == _Horizontal) pos.Y -= 2;
			}
			else if (type_menu == 2)
			{
				if (active_item == i) SetColor(color_active_back, color_active_text);
				else SetColor(color_back, color_text);
				gotoXY(pos);
				cout << " ";
				gotoXY(pos.X + 2, pos.Y);
				if ((visible_checked) && (items[i].info.checked))
					SetColor(color_checked_back, color_checked_text);
				else SetColor(color_back, color_text);
				cout << items[i].frame._mid;
			}
			else
			{
				gotoXY(pos);
				cout << items[i].frame._mid;
			}
			if (dir == _Horizontal) pos.X += (distance);
			else pos.Y += (distance + 1);
		}
	}
	void Use()
	{
		if (items.size() == 0) return;
		if (!IsShow) return;
		bool isExit = false;
		while (!isExit)
		{
			TKey key;
			GetKey(key);
			bool next = ((dir == _Vertical) && (key == kDown)) || ((dir == _Horizontal) && (key == kRight));
			bool prev = ((dir == _Vertical) && (key == kUp)) || ((dir == _Horizontal) && (key == kLeft));
			if (next)
			{
				NextItem();
				Show();
			}
			if (prev)
			{
				PrevItem();
				Show();
			}
			if ((key == kEnter) && visible_checked)
			{
				items[active_item].info.checked = !items[active_item].info.checked;
				Show();
			}
			if (keys_break.find(key) != keys_break.end())
			{
				stop_key = key;
				isExit = true;
			}
		}
	}
	~Menu()
	{
		items.clear();
		keys_break.clear();
	}
};
