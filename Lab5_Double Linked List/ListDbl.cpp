#include <assert.h>
#include "ListDbl.h"
#include <iostream>

using namespace std;

template < class LE >
ListNode<LE>::ListNode(const LE &elem, ListNode<LE> *priorPtr, ListNode<LE> *nextPtr)
// ����Ʈ ��� ������. ����Ʈ�� ��� �� prior, next�� ����, element�� ����.
	:element(elem), prior(priorPtr), next(nextPtr)
{

}


//------------ Ŭ���� ������/ �Ҹ��� ------------------


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


//------------ List manipulation operations ------------------


template < class LE >
void List<LE>::insert(const LE &newElement)
// ����Ʈ ���� ����
{
	if (!full())
	{
		ListNode<LE>* newNode = new ListNode<LE>(newElement, NULL, NULL);
		if (cursor == NULL) // �� ����Ʈ�� ��带 ������ ��
		{
			head = newNode;
		}
		else if(cursor->next == NULL) // ����Ʈ�� �� ���� ��带 ������ ��
		{
			newNode->prior = cursor;
			newNode->prior->next = newNode;
		}
		else // ����Ʈ�� �߰��� ��带 ������ ��
		{
			newNode->prior = cursor;
			newNode->prior->next = newNode;
			newNode->next = cursor->next;
			newNode->next->prior = newNode;
		}
		cursor = newNode;
	}
	else cout << "Fulled list" << endl;
}


template < class LE >
void List<LE>::remove()
// ����Ʈ ���� ����
{
	if (!empty())
	{
		ListNode<LE>* tempNode = cursor;
		if (head == cursor) // �� ���� ��带 ���� ��
		{
			if (cursor->next == NULL)
			{
				head = NULL;
				cursor = NULL;
			}
			else
			{
				cursor = cursor->next;
				head = cursor;
			}
		}
		else if (cursor->next == NULL) // �� ���� ��带 ���� ��
		{
			cursor = cursor->prior;
			cursor->next = NULL;
		}
		else
		{
			cursor->prior->next = cursor->next;
			cursor->next->prior = cursor->prior;
			cursor = cursor->prior;
		}
		delete tempNode;
	}
	else cout << "Empty list" << endl;
}


template < class LE >
void List<LE>::replace(const LE &newElement)
// ����Ʈ ��� ��ü ����
{
	if (!empty())
	{
		cursor->element = newElement;
	}
}


template < class LE >
void List<LE>::clear()
// ����Ʈ Ŭ���� ����
{
	if (!empty())
	{
		ListNode<LE>* tempNode;
		while (head != NULL)
		{
			tempNode = head;
			head = head->next;
			delete tempNode;
		}
		cursor = NULL;
	}
}


//------------ List status operations ------------------


template < class LE >
int List<LE>::empty() const
// ����Ʈ�� ����ִ��� Ȯ��, ���̸� 1 �����̸� 0 ��ȯ
{
	if (head == NULL) return true;
	else return false;
}


template < class LE >
int List<LE>::full() const
// ����Ʈ�� ���� ���ִ��� Ȯ��, ���̸� 1 �����̸� 0 ��ȯ
{
	return false;
}


//------------ List manipulation operations ------------------


template < class LE >
int List<LE>::gotoBeginning()
// ����Ʈ �� ������ �̵�
{
	if (!empty())
	{
		cursor = head;
		return true;
	}
	else return false;
}


template < class LE >
int List<LE>::gotoEnd()
// ����Ʈ �� �ڷ� �̵�
{
	if (!empty())
	{
		while (cursor->next != NULL)
		{
			gotoNext();
		}
		return true;
	}
	else return false;
}


template < class LE >
int List<LE>::gotoNext()
// ����Ʈ �������� �̵�
{
	if (!empty())
	{
		cursor = cursor->next;
		return true;
	}
	else return false;
}


template < class LE >
int List<LE>::gotoPrior()
// ����Ʈ �������� �̵�
{
	if (!empty())
	{
		cursor = cursor->prior;
		return true;
	}
	else return false;
}


template < class LE >
LE List<LE>::getCursor() const
// ���� Ŀ���� ������
{
	if (!empty())
	{
		return cursor->element;
	}
	else
	{
		cout << "Empty list" << endl;
		return false;
	}
}


//-----------------------------------------------------------


template < class LE >
void List<LE>::showStructure() const
// Output the list structure
{
	if (empty()) cout << "Empty list" << endl;
	else
	{
		cout << "cursor : " << cursor->element << endl;
		ListNode<LE>* tempNode = head;
		while (tempNode != NULL)
		{
			cout << tempNode->element << " ";
			tempNode = tempNode->next;
		}
		cout << endl;
	}
}


//-----------------------------------------------------------

/*
template < class LE >
void List<LE>::reverse()
// In-lab opertions
{
	
}

//-----------------------------------------------------------

template < class LE >
int List<LE>::length()
// In-lab opertions
{
	
}

//-----------------------------------------------------------

template < class LE >
int List<LE>::position()
// In-lab opertions
{
	
}*/