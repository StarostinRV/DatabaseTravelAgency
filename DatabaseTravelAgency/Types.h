#pragma once

#include<iostream>

#include<list>

#include<iterator>

using namespace std;

//Pseudographics_Const DOS866
const unsigned char ArrowRight = 16;
const unsigned char ArrowLeft = 17;
const unsigned char AngleRightUp = 187;
const unsigned char AngleRightDown = 188;
const unsigned char AngleLeftDown = 200;
const unsigned char AngleLeftUp = 201;
const unsigned char Hor = 205;
const unsigned char HorUp = 202;
const unsigned char HorDown = 203;
const unsigned char Ver = 186;
const unsigned char VerRight = 204;
const unsigned char VerLeft = 185;
const unsigned char Cross = 206;
struct Point
{
	short X;
	short Y;
};
struct Item
{
	bool checked;
	string text;
};
struct FIO
{
	string surname;
	string name;
	string patronym;
};
struct Adress
{
	string street;
	short home;
	short flat;
};
struct Struct_post
{
	short code_post;
	string name;
	int payment;
	string duties;
	string requirements;
};
struct Struct_employee
{
	short code_employee;
	FIO fio;
	short age;
	string gender;
	Adress adress;
	string phone_number;
	string passport;
	short code_post;
	Struct_post post;
};
struct Struct_holiday
{
	short code_holiday;
	string title;
	string description;
	string limit;
};
struct Struct_hotel
{
	short code_hotel;
	string title;
	string country;
	string town;
	Adress adress;
	string phone_number;
	short rating_star;
	string contact_person;
};
struct Struct_service
{
	short code_service;
	string title;
	string description;
	int price;
};
struct Struct_client
{
	short code_client;
	FIO fio;
	string date_born;
	string gender;
	Adress adress;
	string phone_number;
	string passport;
};
struct Struct_trip
{
	string date_begin;
	string date_end;
	short duration;
	short code_hotel;
	short code_holiday;
	short code_service_1;
	short code_service_2;
	short code_service_3;
	short code_client;
	short code_employee;
	bool checked_reservation;
	bool checked_payment;
	Struct_hotel hotel;
	Struct_holiday holiday;
	Struct_service service_1;
	Struct_service service_2;
	Struct_service service_3;
	Struct_client client;
	Struct_employee employee;
};
enum Color
{
	BLACK = 0x00,
	BLUE = 0x01,
	GREEN = 0x02,
	CYAN = 0x03,
	RED = 0x04,
	MAGENTA = 0x05,
	YELLOY = 0x06,
	BRIGHTGREY = 0x07,
	GREY = 0x08,
	BRIGHTBLUE = 0x09,
	BRIGHTGREEN = 0x0A,
	BRIGHTCYAN = 0x0B,
	BRIGHTRED = 0x0C,
	BRIGHTMAGENTA = 0x0D,
	BRIGHTYELLOY = 0x0E,
	WHITE = 0x0F
};
enum TAlignment { _Right, _Left, _Mid };
enum TKey { kNone, kUp, kDown, kLeft, kRight, kEnter, kEsc, kBackspace, kChar };
enum TDir { _Vertical, _Horizontal };