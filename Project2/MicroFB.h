#pragma once
#pragma once
#include <string>

using namespace std;

class Person
{
public:
	Person();
	Person(string name, Person* nextPtr);
	void insertPerson(string name);
	void deletePerson(string name);
private:
	Person* next;
	Person* cursor;
	string name;
	friend class MicroFB;
	friend class MicroFBNode;
};

class MicroFBNode
{
public:
	MicroFBNode(const Person elem, MicroFBNode* nextPtr);
private:
	Person element;
	MicroFBNode* next;

	friend class MicroFB;
};

class MicroFB
{
public:
	MicroFB();
	void create(string name);
	bool search(string nmae);
	void link(string name1, string name2);
	void unlink(string name1, string name2);
	void print(string name);
	bool checkFriends(string name1, string name2);
private:
	MicroFBNode* top;
	MicroFBNode* temp;
};