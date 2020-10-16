#include "address.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	string file, element;
	AddressManager AddressManager;
	char cmd = NULL; // command
	do
	{
		cout << endl << "Commands: " << endl;
		cout << "\tR: read from a file" << endl;
		cout << "\t+: add a new entry" << endl;
		cout << "\t-: remove an entry" << endl;
		cout << "\tW: write to a file" << endl;
		cout << "\tM: select a Month" << endl;
		cout << "\tQ: quit the program" << endl << endl;
		cout << ">> ";
		AddressManager.showStructure();
		cin >> cmd;

		switch (cmd)
		{
		case 'R': case 'r':
			cout << "Enter the name of file: ";
			cin >> file;
			AddressManager.readfile(file);
			break;
		case '+':
			AddressManager.addEntry();
			break;
		case '-':
			cin.ignore(256, '\n');
			cout << "Remove an entry" << endl << "name: ";
			getline(cin, element);
			AddressManager.removeEntry(element);
			break;
		case 'W': case 'w':
			cout << "Enter the name of file: ";
			cin >> file;
			AddressManager.writefile(file);
			cout << "The list was written into " << file << endl;
			break;
		case 'M': case 'm':
			cout << "Enter the selected month: ";
			cin >> element;
			AddressManager.selectMonth(element);
			break;
		case 'Q': case 'q':
			break;
		default:
			cout << "Inactive or invalid command" << endl;
		}
	} while (cmd != 'Q' && cmd != 'q');
}