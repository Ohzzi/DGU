//--------------------------------------------------------------------
//
//  Laboratory 5                                        stackarr.cpp
//
//  SOLUTION: Array implementation of the Stack ADT
// 2016110426_오지훈
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
	element = new SE[maxNumber]; // 메모리 동적할당
}

//--------------------------------------------------------------------

template < class SE >
Stack<SE>:: ~Stack()
// Frees the memory used by a stack.
{
	delete[] element; // 메모리 반납
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
		// stack이 꽉 차있지 않으면 top+1번째 배열에 newElement를 저장하고 top을 1 증가시킨다.
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
	// stack이 비어있지 않으면 맨 위의 element를 반환하고 top을 1 감소시킨다.
	else return 0;
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::clear()
// Removes all the elements from a stack.
{
	top = -1;
	// top을 초기값(-1)로 만들어 stack을 초기화시킨다.
}

//--------------------------------------------------------------------

template < class SE >
int Stack<SE>::empty() const
// Returns 1 if a stack is empty. Otherwise, returns 0.
{
	if (top == -1) return 1;
	else return 0;
	// stack이 비어있으면(top이 초기값) 1을, 아니면 0을 반환한다.
}

//--------------------------------------------------------------------

template < class SE >
int Stack<SE>::full() const
// Returns 1 if a stack is full. Otherwise, returns 0.
{
	if (top == maxSize - 1) return 1;
	else return 0;
	// top이 maxSize-1이면 (top은 -1부터 시작하므로) stack이 꽉 차 있으므로 1을, 아니면 0을 반환한다.
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
	// empty 함수로 stack이 비어있는지 검사. 비어있지 않으면 top과 맨 위의 원소를 출력.
	// 만약 stack이 비어있으면 "Empty stack"을 출력.
}