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
		logYear = year; //�Է¹��� month�� year ���� ��ȯ�Ѵ�.

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
	entries[day - 1] = value; // �Է¹��� value���� entries �迭�� �����Ѵ�.
}

int Logbook::getEntry(int day) const
{
	// pre - lab
	return entries[day - 1]; // entries �迭�� ���� ��ȯ�Ѵ�.
}

int Logbook::getMonth() const
{
	// pre - lab
	return logMonth; // logMonth ���� ��ȯ�Ѵ�.
}

int Logbook::getYear() const
{
	// pre - lab
	return logYear; // logYear ���� ��ȯ�Ѵ�.
}

int Logbook::getDaysInMonth() const	
{
	// pre - lab
	if (isLeapYear(logYear) == 1)
		return DaysOfMonth[1][logMonth - 1]; // �����̸� DaysOfMonth�� 2�࿡�� �ϼ��� ��ȯ�Ѵ�.
	else return DaysOfMonth[0][logMonth - 1]; // ����̸� DaysOfMonth�� 1�࿡�� �ϼ��� ��ȯ�Ѵ�.
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

	// tm�� ����ü�� �ð� ������ �����ϰ� �ҷ����� ���� asctime, gmtime, localtime, mktime,
	// �׸��� strftime �� ���ؼ� ���˴ϴ�.

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

		int flag = getDayOfWeek(1) + 1; // �� �ѱ� Ȯ�� �÷���
		// �ش� ��/���� 1���� ���� ���� �÷��� ��(0-6)���� �����Ѵ�.

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
		// tm�� time_t�� ��ȯ�� ���� (time_t)-1�� ���� ���� �ش� ���� ���۰��� ��ȯ�Ѵ�.
	}
	else
	{
		// In-lab
		return 0; //�߸��� ���� ����Ǹ� 0�� ��ȯ�Ѵ�.
	}
}
