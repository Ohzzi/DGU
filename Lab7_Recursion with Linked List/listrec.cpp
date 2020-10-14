#include <iostream>
#include "listrec.h"
#include "stacklnk.cpp"

using namespace std;

//-----------------------------------------------------------------------

template < class LE >
ListNode<LE>::ListNode(const LE& elem, ListNode* nextPtr)
// 리스트 노드의 생성자
	:element(elem), next(nextPtr)
{

}

//-----------------------------------------------------------------------

template < class LE >
List<LE>::List(int ignored)
// 리스트의 생성자
	:head(0), cursor(0)
{

}

template < class LE >
List<LE>::~List()
// 리스트의 소멸자
{
	clear();
}

//------------------------------------------------------------------------

template < class LE >
void List<LE>::insert(const LE& newElement)
{
	ListNode<LE>* tempPtr = new ListNode<LE>(newElement, NULL);
	if (head == NULL) // 리스트가 empty
	{
		head = tempPtr;
		cursor = tempPtr;
	}
	else if (cursor->next == NULL) // cursor가 리스트의 맨 끝
	{
		cursor->next = tempPtr;
		cursor = tempPtr;
	}
	else
	{
		tempPtr->next = cursor;
		cursor->next = tempPtr;
		cursor = tempPtr;
	}
}

template < class LE >
void List<LE>::clear()
{
	ListNode<LE>* tempPtr = head;
	while (head != NULL)
	{
		head = head->next;
		delete tempPtr;
	}
}

template < class LE >
void List<LE>::showStructure() const
{
	ListNode<LE>* tempPtr = head;
	while (tempPtr != NULL)
	{
		cout << tempPtr->element;
		if (tempPtr->next != NULL)
			cout << " | ";
		tempPtr = tempPtr->next;
	}
	cout << endl;
}

template < class LE >
void List<LE>::write() const
// 재귀함수 writeSub를 통해 원소를 출력한다
{
	cout << "List : ";
	writeSub(head);
	cout << endl;
}

template < class LE >
void List<LE>::writeSub(ListNode<LE>* p) const
// p!=NULL 이면 p의 원소를 출력하고 다시 writeSub를 호출한다
{
	if (p != NULL)
	{
		cout << p->element;
		writeSub(p->next);
	}
}

template < class LE >
void List<LE>::insertEnd(const LE &newElement)
// 재귀함수 insertEndSub를 통해 리스트의 맨 끝에 노드를 추가한다
{
	insertEndSub(head, newElement);
}

template < class LE >
void List<LE>::insertEndSub(ListNode<LE>*& p, const LE& newElement)
{
	if (p != NULL)
		insertEndSub(p->next, newElement); // p가 리스트의 끝에 도달할 때 까지 재귀함수를 호출
	else
	{
		p = new ListNode<LE>(newElement, NULL);
		cursor = p;
	} // 리스트의 맨 끝에 새 노드를 만들어주고 커서를 옮겨줌.
}

template < class LE >
void List<LE>::writeMirror() const
// 리스트의 원소들을 모두 출력한 뒤 재귀를 통해 반대로 출력한다
{
	cout << "Mirror : ";
	writeMirrorSub(head);
	cout << endl;
}

template < class LE >
void List<LE>::writeMirrorSub(ListNode<LE>* p) const
{
	if (p != NULL)
	{
		cout << p->element;
		writeMirrorSub(p->next); // 모든 원소를 출력
		cout << p->element; // 다시 반대로 출력
	}
}

template < class LE >
void List<LE>::reverse()
// reverseSub를 통해 원소들의 순서를 거꾸로 바꾸어준다
{
	reverseSub(NULL, head);
}

template < class LE >
void List<LE>::reverseSub(ListNode<LE>* p, ListNode<LE>* nextP)
{
	if (nextP != NULL)
	{
		reverseSub(nextP, nextP->next); // 다음 노드로 계속
		nextP->next = p; // 링크를 반대로 해준다
	}
	else
		head = p; // 모든 작업이 끝나면 head도 바꾸어준다
}

template < class LE >
void List<LE>::deleteEnd()
{
	deleteEndSub(head);
	cursor = head;
}

template < class LE >
void List<LE>::deleteEndSub(ListNode<LE>*& p)
{
	if (p->next != NULL) // p가 맨 마지막 노드인지 아닌지 판별
	{
		deleteEndSub(p->next); // p가 마지막 노드에 갈 때 까지 재귀함수 호출
	}
	else
	{
		delete p; // 노드 삭제
		p = NULL;
	}
}

template < class LE >
int List<LE>::length() const
{
	return lengthSub(head);
}

template < class LE >
int List<LE>::lengthSub(ListNode<LE>* p) const
{
	if (p == NULL)
		return 0; // NULL이면 0 반환
	else
		return lengthSub(p->next) + 1; // 맨 끝에 갈 때까지 계속 재귀
}

template < class LE >
void List<LE>::unknown1() const
// Unknown function 1.
{
	unknown1Sub(head);
	cout << endl;
}

template < class LE >
void List<LE>::unknown1Sub(ListNode<LE>* p) const
// Recursive partner of the unknown1() function.
{
	if (p != 0) 
	{ 
		cout << p->element; 
		if (p->next != 0)
		{
			unknown1Sub(p->next->next);
			cout << p->next->element;
		}
	}
}