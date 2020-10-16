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
			} // 새 노드를 만들어서 name, phone, bithday를 읽어오고 해당 노드를 top으로 만들어줌. 파일의 eof까지 반복
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
		file.close(); // 파일 쓰기가 끝나면 파일을 꼭 닫아주어야 한다.
	}
	return 0;
}

void AddressManager::addEntry()
{
	string name, phone, birthday;
	cin.ignore(256, '\n');
	bool check; // 영문,숫자 판별할 카운터 check 선언
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
	} while (!check); // name 입력받기
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
	} while (!check); // phone 입력받기
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
	} while (!check); // birthday 입력받기
	Addressbook* location;
	location = new Addressbook(name,phone,birthday); // 입력을 받을 포인터 location을 새로 할당
	location->next = top;
	top = location;
	int in_month = stoi(birthday.substr(0, 2)) - 1;
	// birthday 입력받고 stoi로 맨 앞의 두 숫자(month)를 정수형으로 바꾸어줌.
	monthcount[in_month]++; // in_month에 받은 숫자에 해당하는 monthcount를 ++해줌.
	size++; // size 증가
}

void AddressManager::removeEntry(string name)
{
	if (top != NULL) // top이 NULL이면 제거할 필요가 없음
	{
		int in_month;
		bool check = false;
		if (top->name == name) // 만약 top의 name이 입력받은 name과 같으면
		{
			in_month = stoi(top->birthday.substr(0, 2)) - 1;
			top = top->next; // top을 지우고 top 다음의 노드를 top으로 만듦
			size--;
			monthcount[in_month]--;
			check = true;
		}
		Addressbook* location;
		location = top;
		while (!check) //top을 지우지 않았을 경우에만 동작
		{
			if (location->next == NULL)
			{
				location = location->next;
				break; // location이 참조할 다음 노드가 NULL이면 루프를 탈출
			}
			if (location->next->name == name) // location 다음 노드의 name이 입력받은 name과 같으면
			{
				Addressbook* del;
				del = location->next; // 삭제를 위해 del을 생성하고 location의 다음 노드를 할당 
				location->next = del->next; // del을 지워야 하므로 location과 del의 다음 노드를 연결
				in_month = stoi(del->birthday.substr(0, 2)) - 1;
				delete del; // del 삭제
				size--; // size 줄임
				monthcount[in_month]--; // monthcount 줄임
				check = true;
			}
			else
			{
				location = location->next; // location을 다음 노드로 넘김
			}
		}
		if (location == NULL) cout << "incorrect name" << endl;
	}
	else cout << "Empty" << endl;
}

void AddressManager::selectMonth(string month)
{
	month[0] = toupper(month[0]); // 열거형에 있는 month들이 대문자로 시작하므로 입력받은 month의 첫글자를 대문자로 변환
	Month m = convert(month); // string month를 변환해줄 열거형 m
	if (m != Error)
	{
		cout << "Total number of birthday in " << month << ": " << monthcount[m] << endl;
		Addressbook* location = top; // top부터 month를 검색할 location 선언
		while (location != NULL)
		{
			int tempMonth = stoi(location->birthday.substr(0, 2)) - 1; // stoi를 통해 month를 가져옴
			if (m == tempMonth)
			{
				cout << location->name << endl << location->phone << endl << location->birthday << endl << endl; // m == tempMonth이면 데이터 출력
			}
			location = location->next; // location을 다음 노드로 넘김
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