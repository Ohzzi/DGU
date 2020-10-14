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
	if (cursor == NULL) // cursor가 NULL = 첫 친구
		this->next = newPerson;
	else // 아닌 경우 이미 친구가 존재
		cursor->next = newPerson;
	cursor = newPerson; // newPerson으로 cursor를 옮겨줌
}

void Person::deletePerson(string name)
{
	bool check = false; // 리스트 내에 존재하는지 유무를 판단할 변수 check
	Person* tempPerson = this->next, * prior = tempPerson; // 현재 Person의 다음부터 친구 리스트이므로 tempPerson을 this->next로 해줌
	Person* deletePerson;
	while (tempPerson != NULL)
	{
		if (tempPerson->name.compare(name) != 0)
		{
			prior = tempPerson;
			tempPerson = tempPerson->next;
		} // tempPerson의 name이 삭제하려는 name이 아니면 prior는 tempPerson으로 만들어주고 tempPerson을 다음 Person으로 넘겨준다
		else // tempPerson의 name이 삭제하려는 name과 일치할 경우
		{
			deletePerson = tempPerson;
			if (prior == tempPerson)
			{ // prior == tempPerson이면 맨 처음 Person
				this->next = tempPerson->next;
				cursor = NULL;
			} //this와 tempPerson의 next를 연결해준다
			else
			{
				prior->next = tempPerson->next; // prior의 next와 tempPerson의 next를 연결해준다
				if (cursor == tempPerson) // cursor == tempPerson이면 (지우려는 person이 맨 끝)
					cursor = prior; // cursor를 앞으로 옮겨준다
			}
			delete deletePerson;
			check = true;
			break;
		}
	}
	if (check == false) cout << "They are not friends" << endl;
	// check가 false이면 삭제가 안되었음(친구가 아님)
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
	} // 새 Person을 만들어서 MicroFB에 추가
	else
		cout << "Already exists" << endl;
}

bool MicroFB::search(string name)
{
	bool check = false; // search에 성공했는지 확인하는 변수 check
	MicroFBNode* searchNode = top;
	while (searchNode != NULL)
	{
		if (searchNode->element.name.compare(name) == 0)
		{
			check = true;
			temp = searchNode; // search에 성공했으므로 check를 true값으로 주고 temp를 해당 위치로 만들어준다
			break;
		}
		else
			searchNode = searchNode->next;
	}
	return check;
}

void MicroFB::link(string name1, string name2)
{
	if (search(name2) && search(name1)) // search(name1)에서 temp = name1의 노드
		temp->element.insertPerson(name2); // 친구 1에 친구 2를 추가
	if (search(name1) && search(name2)) // search(name2)에서 temp = name2의 노드
		temp->element.insertPerson(name1); // 친구 2에 친구 1을 추가
}

void MicroFB::unlink(string name1, string name2)
{
	if (search(name2) && search(name1)) // search(name1)에서 temp = name1의 노드
		temp->element.deletePerson(name2); // 친구 1에서 친구 2를 삭제
	if (search(name1) && search(name2)) // search(name2)에서 temp = name2의 노드
		temp->element.deletePerson(name1); // 친구 2에서 친구 1을 삭제
}

void MicroFB::print(string name)
{
	if (search(name)) // temp = name을 가진 person의 노드
	{
		cout << "\t" << "\t";
		Person* printPtr = temp->element.next; // temp->element가 person이고, 이 person의 next부터 친구목록이므로 printPtr 시작
		while (printPtr != NULL)
		{
			cout << printPtr->name << " ";
			printPtr = printPtr->next;
		} // printPtr을 옮겨가면서 출력
		cout << endl;
	}
	else cout << "Wrong name" << endl;
}

bool MicroFB::checkFriends(string name1, string name2)
{
	bool check = false;
	if (!search(name1) || !search(name2)) // name1이나 name2로 search에 실패하면 해당 person이 존재하지 않으므로 false 반환
		return false;
	search(name1); // temp = name1의 노드
	Person* checkPtr = temp->element.next; // temp->element.next부터 친구 리스트
	while (checkPtr != NULL)
	{
		if (checkPtr->name.compare(name2) == 0) // name1의 친구 리스트에 name2가 존재하면
		{
			check = true;
			break;
		}
		else
			checkPtr = checkPtr->next;
	}
	if (checkPtr == NULL) // checkPtr이 NULL이 될 때 까지 탐색을 마치면 친구 리스트에 name2가 존재하지 않는다
		check = false;
	return check; // check를 반환해준다
}