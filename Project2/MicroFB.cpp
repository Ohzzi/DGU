#include <iostream>
#include "MicroFB.h"

using namespace std;

Person::Person()
{
	// constructor;
}

Person::Person(string name, Person* nextPtr)
{
	this->name = name;
	this->next = nextPtr;
	this->cursor = NULL;
}

void Person::insertPerson(string name)
{
	Person* newPerson = new Person(name, NULL);
	if (cursor == NULL) // cursor�� NULL = ù ģ��
		this->next = newPerson;
	else // �ƴ� ��� �̹� ģ���� ����
		cursor->next = newPerson;
	cursor = newPerson; // newPerson���� cursor�� �Ű���
}

void Person::deletePerson(string name)
{
	bool check = false; // ����Ʈ ���� �����ϴ��� ������ �Ǵ��� ���� check
	Person* tempPerson = this->next, * prior = tempPerson; // ���� Person�� �������� ģ�� ����Ʈ�̹Ƿ� tempPerson�� this->next�� ����
	Person* deletePerson;
	while (tempPerson != NULL)
	{
		if (tempPerson->name.compare(name) != 0)
		{
			prior = tempPerson;
			tempPerson = tempPerson->next;
		} // tempPerson�� name�� �����Ϸ��� name�� �ƴϸ� prior�� tempPerson���� ������ְ� tempPerson�� ���� Person���� �Ѱ��ش�
		else // tempPerson�� name�� �����Ϸ��� name�� ��ġ�� ���
		{
			deletePerson = tempPerson;
			if (prior == tempPerson)
			{ // prior == tempPerson�̸� �� ó�� Person
				this->next = tempPerson->next;
				cursor = NULL;
			} //this�� tempPerson�� next�� �������ش�
			else
			{
				prior->next = tempPerson->next; // prior�� next�� tempPerson�� next�� �������ش�
				if (cursor == tempPerson) // cursor == tempPerson�̸� (������� person�� �� ��)
					cursor = prior; // cursor�� ������ �Ű��ش�
			}
			delete deletePerson;
			check = true;
			break;
		}
	}
	if (check == false) cout << "They are not friends" << endl;
	// check�� false�̸� ������ �ȵǾ���(ģ���� �ƴ�)
}

MicroFBNode::MicroFBNode(const Person elem, MicroFBNode* nextPtr)
	:element(elem), next(nextPtr)
{
	// constructor
}

MicroFB::MicroFB()
	:top(NULL), temp(NULL)
{
	// constructor
}

void MicroFB::create(string name)
{
	if (!search(name))
	{
		Person newPerson(name, NULL);
		MicroFBNode* newNode = new MicroFBNode(newPerson, top);
		newNode->next = top;
		top = newNode;
	} // �� Person�� ���� MicroFB�� �߰�
	else
		cout << "Already exists" << endl;
}

bool MicroFB::search(string name)
{
	bool check = false; // search�� �����ߴ��� Ȯ���ϴ� ���� check
	MicroFBNode* searchNode = top;
	while (searchNode != NULL)
	{
		if (searchNode->element.name.compare(name) == 0)
		{
			check = true;
			temp = searchNode; // search�� ���������Ƿ� check�� true������ �ְ� temp�� �ش� ��ġ�� ������ش�
			break;
		}
		else
			searchNode = searchNode->next;
	}
	return check;
}

void MicroFB::link(string name1, string name2)
{
	if (search(name2) && search(name1)) // search(name1)���� temp = name1�� ���
		temp->element.insertPerson(name2); // ģ�� 1�� ģ�� 2�� �߰�
	if (search(name1) && search(name2)) // search(name2)���� temp = name2�� ���
		temp->element.insertPerson(name1); // ģ�� 2�� ģ�� 1�� �߰�
}

void MicroFB::unlink(string name1, string name2)
{
	if (search(name2) && search(name1)) // search(name1)���� temp = name1�� ���
		temp->element.deletePerson(name2); // ģ�� 1���� ģ�� 2�� ����
	if (search(name1) && search(name2)) // search(name2)���� temp = name2�� ���
		temp->element.deletePerson(name1); // ģ�� 2���� ģ�� 1�� ����
}

void MicroFB::print(string name)
{
	if (search(name)) // temp = name�� ���� person�� ���
	{
		cout << "\t" << "\t";
		Person* printPtr = temp->element.next; // temp->element�� person�̰�, �� person�� next���� ģ������̹Ƿ� printPtr ����
		while (printPtr != NULL)
		{
			cout << printPtr->name << " ";
			printPtr = printPtr->next;
		} // printPtr�� �Űܰ��鼭 ���
		cout << endl;
	}
	else cout << "Wrong name" << endl;
}

bool MicroFB::checkFriends(string name1, string name2)
{
	bool check = false;
	if (!search(name1) || !search(name2)) // name1�̳� name2�� search�� �����ϸ� �ش� person�� �������� �����Ƿ� false ��ȯ
		return false;
	search(name1); // temp = name1�� ���
	Person* checkPtr = temp->element.next; // temp->element.next���� ģ�� ����Ʈ
	while (checkPtr != NULL)
	{
		if (checkPtr->name.compare(name2) == 0) // name1�� ģ�� ����Ʈ�� name2�� �����ϸ�
		{
			check = true;
			break;
		}
		else
			checkPtr = checkPtr->next;
	}
	if (checkPtr == NULL) // checkPtr�� NULL�� �� �� ���� Ž���� ��ġ�� ģ�� ����Ʈ�� name2�� �������� �ʴ´�
		check = false;
	return check; // check�� ��ȯ���ش�
}