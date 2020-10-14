#include "MicroFB.h"
#include <iostream>

using namespace std;

int main()
{
	char cmd = NULL;
	string personName;
	MicroFB facebook;
	cout << "Input" << "\t" << "\t" << "Output" << endl;
	do
	{
		cin >> cmd;
		string name1, name2;
		switch (cmd)
		{
		case 'P': case 'p':
			cin >> personName;
			facebook.create(personName);
			break;
		case 'F': case 'f':
			cin >> name1 >> name2;
			facebook.link(name1, name2);
			break;
		case 'U': case 'u':
			cin >> name1 >> name2;
			facebook.unlink(name1, name2);
			break;
		case 'L': case 'l':
			cin >> personName;
			facebook.print(personName);
			break;
		case 'Q': case 'q':
			cin >> name1 >> name2;
			if (facebook.checkFriends(name1, name2))
				cout << "\t" << "\t" << "Yes" << endl;
			else
				cout << "\t" << "\t" << "No" << endl;
			break;
		case 'X': case 'x':
			break;
		}
	} while (cmd != 'X' && cmd != 'x');
}