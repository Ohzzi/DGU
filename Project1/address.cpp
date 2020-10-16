#include "address.h"
#include <iostream>
#include <string>
#include <fstream>

//-----------------------------------------------------------------------------------------

Month convert(string month)
{
	if (month == "January") return January;
	else if (month == "February") return February;
	else if (month == "March") return March;
	else if (month == "April") return April;
	else if (month == "May") return May;
	else if (month == "June") return June;
	else if (month == "July") return July;
	else if (month == "August") return August;
	else if (month == "September") return September;
	else if (month == "October") return October;
	else if (month == "November") return November;
	else if (month == "December") return December;
	else return Error;
}

Addressbook::Addressbook(string name = "", string phone = "", string birthday = "")
{
	this->name = name;
	this->phone = phone;
	this->birthday = birthday;
	this->next = NULL;
}

AddressManager::AddressManager()
{
	for (int i = 0; i < 12; i++)
		monthcount[i] = 0;
	size = 0;
	top = 0;
}

bool AddressManager::readfile(string filepath)
{
	ifstream file(filepath.data());
	if (file.is_open())
	{
		Addressbook* location;
		string temp;
		while (!file.eof()) {
			getline(file, temp);
			if (temp != "")
			{
				location = new Addressbook();
				location->next = top;
				location->name = temp;
				getline(file, temp);
				location->phone = temp;
				getline(file, temp);
				location->birthday = temp;
				top = location;
				size++;
				int in_month = stoi(temp.substr(0, 2)) - 1;
				monthcount[in_month]++;
			} // �� ��带 ���� name, phone, bithday�� �о���� �ش� ��带 top���� �������. ������ eof���� �ݺ�
		}
	}
	else cout << "wrong file name" << endl;
	return 0;
}

bool AddressManager::writefile(string filepath)
{
	ofstream file(filepath.data());
	if (file.is_open())
	{
		while (top != NULL)
		{
			file << top->name << endl
				<< top->phone << endl
				<< top->birthday << endl << endl;
			top = top->next;
		}
		file.close(); // ���� ���Ⱑ ������ ������ �� �ݾ��־�� �Ѵ�.
	}
	return 0;
}

void AddressManager::addEntry()
{
	string name, phone, birthday;
	cin.ignore(256, '\n');
	bool check; // ����,���� �Ǻ��� ī���� check ����
	do
	{
		check = true;
		cout << "name: ";
		getline(cin, name);
		for (unsigned int i = 0; i < name.length(); i++) {
			if (isalpha(name[i]) == 0 && name[i] !=' ') {
				check = false;
				cout << "incorrect name" << endl;
				break;
			}
		}
	} while (!check); // name �Է¹ޱ�
	do
	{
		check = true;
		cout << "phone number: ";
		getline(cin, phone);
		for (unsigned int i = 0; i < phone.length(); i++) {
			if (isalnum(phone[i]) == 0 && phone[i] != '(' && phone[i] != ')' && phone[i] != '-' && phone[i] != ' ') {
				check = false;
				cout << "incorrect phone number" << endl;
				break;
			}
		}
	} while (!check); // phone �Է¹ޱ�
	do
	{
		check = true;
		cout << "birthday(MM/DD/YYYY): ";
		getline(cin, birthday);
		for (unsigned int i = 0; i < birthday.length(); i++) {
			if (isalnum(birthday[i]) == 0 && birthday[2] != '/' && birthday[4] != '/' || stoi(birthday.substr(0,2))>12) {
				check = false;
				cout << "incorrect birthday" << endl;
				break;
			}
		}
	} while (!check); // birthday �Է¹ޱ�
	Addressbook* location;
	location = new Addressbook(name,phone,birthday); // �Է��� ���� ������ location�� ���� �Ҵ�
	location->next = top;
	top = location;
	int in_month = stoi(birthday.substr(0, 2)) - 1;
	// birthday �Է¹ް� stoi�� �� ���� �� ����(month)�� ���������� �ٲپ���.
	monthcount[in_month]++; // in_month�� ���� ���ڿ� �ش��ϴ� monthcount�� ++����.
	size++; // size ����
}

void AddressManager::removeEntry(string name)
{
	if (top != NULL) // top�� NULL�̸� ������ �ʿ䰡 ����
	{
		int in_month;
		bool check = false;
		if (top->name == name) // ���� top�� name�� �Է¹��� name�� ������
		{
			in_month = stoi(top->birthday.substr(0, 2)) - 1;
			top = top->next; // top�� ����� top ������ ��带 top���� ����
			size--;
			monthcount[in_month]--;
			check = true;
		}
		Addressbook* location;
		location = top;
		while (!check) //top�� ������ �ʾ��� ��쿡�� ����
		{
			if (location->next == NULL)
			{
				location = location->next;
				break; // location�� ������ ���� ��尡 NULL�̸� ������ Ż��
			}
			if (location->next->name == name) // location ���� ����� name�� �Է¹��� name�� ������
			{
				Addressbook* del;
				del = location->next; // ������ ���� del�� �����ϰ� location�� ���� ��带 �Ҵ� 
				location->next = del->next; // del�� ������ �ϹǷ� location�� del�� ���� ��带 ����
				in_month = stoi(del->birthday.substr(0, 2)) - 1;
				delete del; // del ����
				size--; // size ����
				monthcount[in_month]--; // monthcount ����
				check = true;
			}
			else
			{
				location = location->next; // location�� ���� ���� �ѱ�
			}
		}
		if (location == NULL) cout << "incorrect name" << endl;
	}
	else cout << "Empty" << endl;
}

void AddressManager::selectMonth(string month)
{
	month[0] = toupper(month[0]); // �������� �ִ� month���� �빮�ڷ� �����ϹǷ� �Է¹��� month�� ù���ڸ� �빮�ڷ� ��ȯ
	Month m = convert(month); // string month�� ��ȯ���� ������ m
	if (m != Error)
	{
		cout << "Total number of birthday in " << month << ": " << monthcount[m] << endl;
		Addressbook* location = top; // top���� month�� �˻��� location ����
		while (location != NULL)
		{
			int tempMonth = stoi(location->birthday.substr(0, 2)) - 1; // stoi�� ���� month�� ������
			if (m == tempMonth)
			{
				cout << location->name << endl << location->phone << endl << location->birthday << endl << endl; // m == tempMonth�̸� ������ ���
			}
			location = location->next; // location�� ���� ���� �ѱ�
		}
	}
	else cout << "incorrect month" << endl;
}

void AddressManager::showStructure() const
{
	if (size != 0) {
		cout << "Total number of entries in the list: " << size << endl;
		cout << "Number of birthdays in" << endl;
	}
	if (monthcount[0] != 0)
		cout << "\tJanuary: " << monthcount[0] << endl;
	if (monthcount[1] != 0)
		cout << "\tFebruary: " << monthcount[1] << endl;
	if (monthcount[2] != 0)
		cout << "\tMarch: " << monthcount[2] << endl;
	if (monthcount[3] != 0)
		cout << "\tApril: " << monthcount[3] << endl;
	if (monthcount[4] != 0)
		cout << "\tMay: " << monthcount[4] << endl;
	if (monthcount[5] != 0)
		cout << "\tJune: " << monthcount[5] << endl;
	if (monthcount[6] != 0)
		cout << "\tJuly: " << monthcount[6] << endl;
	if (monthcount[7] != 0)
		cout << "\tAugust: " << monthcount[7] << endl;
	if (monthcount[8] != 0)
		cout << "\tSeptember: " << monthcount[8] << endl;
	if (monthcount[9] != 0)
		cout << "\tOctober: " << monthcount[9] << endl;
	if (monthcount[10] != 0)
		cout << "\tNovember: " << monthcount[10] << endl;
	if (monthcount[11] != 0)
		cout << "\tDecember: " << monthcount[11] << endl;
}