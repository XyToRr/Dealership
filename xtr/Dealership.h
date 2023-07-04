#pragma once

struct Date
{
	unsigned int day;
	unsigned int month;
	unsigned int year;
};

struct Name
{
	char name[20];
	char lastName[30];
	char middleName[20];
};

struct Worker
{
	Name Name;
	char position[20];
	char telephone[15];
	char Email[30];
};

struct Car
{
	char producer[20];
	char model[20];
	unsigned int releaseYear;
	unsigned int cost;
	unsigned int potentialPrice;

};

struct Sell
{
	Worker worker;
	Car car;
	Date date;
	unsigned int price;
};