// Logbook.cpp: implementation of the Logbook class.
//
//////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include "Logbook.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Logbook::Logbook()
{
	setCurrentTime();			 
	initEntry();				 
}

Logbook::~Logbook()
{

}

Logbook::Logbook(int month, int year)
{
	if (month >= 0 && month <= 11) {
		setCurrentTime();

		// pre - lab
		logMonth = month;
		logYear = year; //입력받은 month와 year 값을 반환한다.

		currentTime->tm_year = year - 1900;
		currentTime->tm_mon = month - 1;




		initEntry();
	}
	else {
		cout << "----invalid month value----\n";
	}
}

void Logbook::putEntry(int day, int value)
{
	// pre - lab
	entries[day - 1] = value; // 입력받은 value값을 entries 배열에 저장한다.
}

int Logbook::getEntry(int day) const
{
	// pre - lab
	return entries[day - 1]; // entries 배열의 값을 반환한다.
}

int Logbook::getMonth() const
{
	// pre - lab
	return logMonth; // logMonth 값을 반환한다.
}

int Logbook::getYear() const
{
	// pre - lab
	return logYear; // logYear 값을 반환한다.
}

int Logbook::getDaysInMonth() const	
{
	// pre - lab
	if (isLeapYear(logYear) == 1)
		return DaysOfMonth[1][logMonth - 1]; // 윤년이면 DaysOfMonth의 2행에서 일수를 반환한다.
	else return DaysOfMonth[0][logMonth - 1]; // 평년이면 DaysOfMonth의 1행에서 일수를 반환한다.
}

int Logbook::isLeapYear(int year) const
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return 1;		// Leap year
	else
		return 0;		// Normal years
}


void Logbook::putEntry(int value)		 
{
	entries[(currentTime->tm_mday - 1)] = value;
}

void Logbook::setCurrentTime()
{	
	// tm structure Used by asctime, gmtime, localtime, mktime, 
	// and strftime to store and retrieve time information.  

	// tm은 구조체로 시간 정보를 저장하고 불러오기 위해 asctime, gmtime, localtime, mktime,
	// 그리고 strftime 에 의해서 사용됩니다.

	time_t		now;
	time(&now);
	currentTime = localtime(&now);		

	logYear = currentTime->tm_year + 1900;
	logMonth = currentTime->tm_mon + 1;
}

void Logbook::initEntry()
{
	int iDays = getDaysInMonth();
	for (int i = 0; i < iDays; i++)
		entries[i] = 0;
}


void Logbook::displayCalendar() const
{
	if (currentTime->tm_year + 1900 >= MIN_YEAR && currentTime->tm_year + 1900 <= MAX_YEAR) {

		cout << "\t\t\t\t" << currentTime->tm_mon + 1 << " / " << currentTime->tm_year + 1900;
		cout << endl;

		cout << "\t Sun \t Mon \t Tue \t Wed \t Thu \t Fri \t Sat";
		cout << endl;

		int iDays = getDaysInMonth();

		int flag = getDayOfWeek(1) + 1; // 줄 넘김 확인 플래그
		// 해당 년/월의 1일의 요일 값을 플래그 값(0-6)으로 설정한다.

		if (flag != 1) {
			for (int p = 1; p < flag; p++)
				cout << "\t";
		}

		for (int i = 0; i < iDays; i++) {
			cout << "\t" << i + 1 << " " << entries[i];
			flag++;

			if (flag % 8 == 0) {
				flag = 1;
				cout << endl;
			}
		}
	}
}

int Logbook::getDayOfWeek(int day) const
{
	tm	when;
	time_t	result;

	when = *currentTime;
	when.tm_mday = day;

	if ((result = mktime(&when)) != (time_t)-1)
	{
		// In-lab
		return when.tm_wday;
		// tm을 time_t로 변환한 값과 (time_t)-1의 값을 비교해 해당 달의 시작값을 반환한다.
	}
	else
	{
		// In-lab
		return 0; //잘못된 값이 저장되면 0을 반환한다.
	}
}
