#include <iostream>
#include "listrec.h"
#include "stacklnk.cpp"

using namespace std;

//-----------------------------------------------------------------------

template < class LE >
ListNode<LE>::ListNode(const LE& elem, ListNode* nextPtr)
// ����Ʈ ����� ������
	:element(elem), next(nextPtr)
{

}

//-----------------------------------------------------------------------

template < class LE >
List<LE>::List(int ignored)
// ����Ʈ�� ������
	:head(0), cursor(0)
{

}

template < class LE >
List<LE>::~List()
// ����Ʈ�� �Ҹ���
{
	clear();
}

//------------------------------------------------------------------------

template < class LE >
void List<LE>::insert(const LE& newElement)
{
	ListNode<LE>* tempPtr = new ListNode<LE>(newElement, NULL);
	if (head == NULL) // ����Ʈ�� empty
	{
		head = tempPtr;
		cursor = tempPtr;
	}
	else if (cursor->next == NULL) // cursor�� ����Ʈ�� �� ��
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
// ����Լ� writeSub�� ���� ���Ҹ� ����Ѵ�
{
	cout << "List : ";
	writeSub(head);
	cout << endl;
}

template < class LE >
void List<LE>::writeSub(ListNode<LE>* p) const
// p!=NULL �̸� p�� ���Ҹ� ����ϰ� �ٽ� writeSub�� ȣ���Ѵ�
{
	if (p != NULL)
	{
		cout << p->element;
		writeSub(p->next);
	}
}

template < class LE >
void List<LE>::insertEnd(const LE &newElement)
// ����Լ� insertEndSub�� ���� ����Ʈ�� �� ���� ��带 �߰��Ѵ�
{
	insertEndSub(head, newElement);
}

template < class LE >
void List<LE>::insertEndSub(ListNode<LE>*& p, const LE& newElement)
{
	if (p != NULL)
		insertEndSub(p->next, newElement); // p�� ����Ʈ�� ���� ������ �� ���� ����Լ��� ȣ��
	else
	{
		p = new ListNode<LE>(newElement, NULL);
		cursor = p;
	} // ����Ʈ�� �� ���� �� ��带 ������ְ� Ŀ���� �Ű���.
}

template < class LE >
void List<LE>::writeMirror() const
// ����Ʈ�� ���ҵ��� ��� ����� �� ��͸� ���� �ݴ�� ����Ѵ�
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
		writeMirrorSub(p->next); // ��� ���Ҹ� ���
		cout << p->element; // �ٽ� �ݴ�� ���
	}
}

template < class LE >
void List<LE>::reverse()
// reverseSub�� ���� ���ҵ��� ������ �Ųٷ� �ٲپ��ش�
{
	reverseSub(NULL, head);
}

template < class LE >
void List<LE>::reverseSub(ListNode<LE>* p, ListNode<LE>* nextP)
{
	if (nextP != NULL)
	{
		reverseSub(nextP, nextP->next); // ���� ���� ���
		nextP->next = p; // ��ũ�� �ݴ�� ���ش�
	}
	else
		head = p; // ��� �۾��� ������ head�� �ٲپ��ش�
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
	if (p->next != NULL) // p�� �� ������ ������� �ƴ��� �Ǻ�
	{
		deleteEndSub(p->next); // p�� ������ ��忡 �� �� ���� ����Լ� ȣ��
	}
	else
	{
		delete p; // ��� ����
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
		return 0; // NULL�̸� 0 ��ȯ
	else
		return lengthSub(p->next) + 1; // �� ���� �� ������ ��� ���
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