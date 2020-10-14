//--------------------------------------------------------------------
//
//  Laboratory 5                                        stackarr.cpp
//
//  SOLUTION: Array implementation of the Stack ADT
// 2016110426_������
//--------------------------------------------------------------------

#include <assert.h>
#include "stackarr.h"
#include <iostream>
using namespace std;

//--------------------------------------------------------------------

template < class SE >
Stack<SE>::Stack(int maxNumber)
// Creates an empty stack. Allocates enough memory for maxNumber
// elements (defaults to defMaxStackSize).
	: maxSize(maxNumber), top(-1)
{
	element = new SE[maxNumber]; // �޸� �����Ҵ�
}

//--------------------------------------------------------------------

template < class SE >
Stack<SE>:: ~Stack()
// Frees the memory used by a stack.
{
	delete[] element; // �޸� �ݳ�
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::push(const SE& newElement)
// Inserts newElement onto the top of a stack.
{
	if (!Stack<SE>::full())
	{
		element[top + 1] = newElement;
		top++;
		// stack�� �� ������ ������ top+1��° �迭�� newElement�� �����ϰ� top�� 1 ������Ų��.
	}
	else cout << "The stack is full" << endl;
}

//--------------------------------------------------------------------

template < class SE >
SE Stack<SE>::pop()
// Removes the topmost element from a stack and returns it.
{
	if (!Stack<SE>::empty())
	{
		return element[top--];
	}
	// stack�� ������� ������ �� ���� element�� ��ȯ�ϰ� top�� 1 ���ҽ�Ų��.
	else return 0;
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::clear()
// Removes all the elements from a stack.
{
	top = -1;
	// top�� �ʱⰪ(-1)�� ����� stack�� �ʱ�ȭ��Ų��.
}

//--------------------------------------------------------------------

template < class SE >
int Stack<SE>::empty() const
// Returns 1 if a stack is empty. Otherwise, returns 0.
{
	if (top == -1) return 1;
	else return 0;
	// stack�� ���������(top�� �ʱⰪ) 1��, �ƴϸ� 0�� ��ȯ�Ѵ�.
}

//--------------------------------------------------------------------

template < class SE >
int Stack<SE>::full() const
// Returns 1 if a stack is full. Otherwise, returns 0.
{
	if (top == maxSize - 1) return 1;
	else return 0;
	// top�� maxSize-1�̸� (top�� -1���� �����ϹǷ�) stack�� �� �� �����Ƿ� 1��, �ƴϸ� 0�� ��ȯ�Ѵ�.
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::showStructure() const
// Array implementation. Outputs the elements in a stack. If the
// stack is empty, outputs "Empty stack". This operation is intended
// for testing and debugging purposes only.
{
	if (!Stack<SE>::empty())
	{
		cout << "top : " << top << endl;
		for (int i = 0; i <= top; i++)
		{
			cout << i << "data : " << element[i] << endl;
		}
	}
	else cout << "Empty stack" << endl;
	// empty �Լ��� stack�� ����ִ��� �˻�. ������� ������ top�� �� ���� ���Ҹ� ���.
	// ���� stack�� ��������� "Empty stack"�� ���.
}