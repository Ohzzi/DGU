#include <assert.h>
#include "ListDbl.h"
#include <iostream>

using namespace std;

template < class LE >
ListNode<LE>::ListNode(const LE &elem, ListNode<LE> *priorPtr, ListNode<LE> *nextPtr)
// 리스트 노드 생성자. 리스트의 노드 간 prior, next를 지정, element를 삽입.
	:element(elem), prior(priorPtr), next(nextPtr)
{

}


//------------ 클래스 생성자/ 소멸자 ------------------


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


//------------ List manipulation operations ------------------


template < class LE >
void List<LE>::insert(const LE &newElement)
// 리스트 삽입 연산
{
	if (!full())
	{
		ListNode<LE>* newNode = new ListNode<LE>(newElement, NULL, NULL);
		if (cursor == NULL) // 빈 리스트에 노드를 삽입할 때
		{
			head = newNode;
		}
		else if(cursor->next == NULL) // 리스트의 맨 끝에 노드를 삽입할 때
		{
			newNode->prior = cursor;
			newNode->prior->next = newNode;
		}
		else // 리스트의 중간에 노드를 삽입할 때
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
// 리스트 제거 연산
{
	if (!empty())
	{
		ListNode<LE>* tempNode = cursor;
		if (head == cursor) // 맨 앞의 노드를 지울 때
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
		else if (cursor->next == NULL) // 맨 뒤의 노드를 지울 때
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
// 리스트 노드 교체 연산
{
	if (!empty())
	{
		cursor->element = newElement;
	}
}


template < class LE >
void List<LE>::clear()
// 리스트 클리어 연산
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
// 리스트가 비어있는지 확인, 참이면 1 거짓이면 0 반환
{
	if (head == NULL) return true;
	else return false;
}


template < class LE >
int List<LE>::full() const
// 리스트가 가득 차있는지 확인, 참이면 1 거짓이면 0 반환
{
	return false;
}


//------------ List manipulation operations ------------------


template < class LE >
int List<LE>::gotoBeginning()
// 리스트 맨 앞으로 이동
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
// 리스트 맨 뒤로 이동
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
// 리스트 다음으로 이동
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
// 리스트 이전으로 이동
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
// 현재 커서를 가져옴
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