#include <iostream>
#include <string>
#include <fstream>

//-----------------------------------------------------------------------

using namespace std;

enum Month { January, February, March, April, May, June, July, August, September, October, November, December, Error };
Month convert(string month);

class Addressbook
{
public:
	Addressbook(string name, string phone, string birthday);

private:
	string name;
	string phone;
	string birthday;
	Addressbook* next;
	friend class AddressManager;
};

class AddressManager
{
public:
	AddressManager();
	bool readfile(string filepath);
	bool writefile(string filepath);
	void addEntry();
	void removeEntry(string name);
	void selectMonth(string month);
	void showStructure() const;

private:
	int monthcount[12];
	int size;
	Addressbook* top;
 };