//--------------------------------------------------------------------
//
//  Laboratory 5                                        stacklnk.cpp
//
//  SOLUTION: Linked list implementation of the Stack ADT
// 2016110426_ø¿¡ˆ»∆
//--------------------------------------------------------------------

#include <assert.h>
// #include <alloc.h>
#include "stacklnk.h"
#include <iostream>

using namespace std;
//--------------------------------------------------------------------

template < class SE >
StackNode<SE>::StackNode(const SE &elem, StackNode<SE> *nextPtr)
// Creates a stack node containing element elem and next pointer
// nextPtr.
: element(elem),
next(nextPtr)
{

}

//--------------------------------------------------------------------

template < class SE >
Stack<SE>::Stack(int ignored)
// Creates an empty stack. The parameter is provided for compatability
// with the array implementation and is ignored.
: top(0)
{

}

//--------------------------------------------------------------------

template < class SE >
Stack<SE>:: ~Stack()
// Frees the memory used by a stack.
{
	Stack<SE>::clear();
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::push(const SE &newElement)
// Inserts newElement onto the top of a stack.
{
	if (!Stack<SE>::full())
	{
		top = new StackNode<SE>(newElement, top);
	}
	else cout << "Stack is full" << endl;
}

//--------------------------------------------------------------------

template < class SE >
SE Stack<SE>::pop()
// Removes the topmost element from a stack and returns it.
{
	if (!Stack<SE>::empty())
	{
		StackNode<SE>* tempPtr;
		SE item = top->element;
		tempPtr = top;
		top = top->next;
		delete tempPtr;
		return item;
	}
	else cout << "Stack is empty" << endl;
	return 0;
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::clear()
// Removes all the elements from a stack.
{
	StackNode<SE>* tempPtr;
	while (!top == NULL)
	{
		tempPtr = top;
		top = top->next;
		delete tempPtr;
	}
}

//--------------------------------------------------------------------

template < class SE >
int Stack<SE>::empty() const
// Returns 1 if a stack is empty. Otherwise, returns 0.
{
	if (top == NULL)
		return 1;
	else return 0;
}

//--------------------------------------------------------------------

template < class SE >
int Stack<SE>::full() const
// Returns 1 if a stack is full. Otherwise, returns 0. Cannot be
// done cleanly in generic C++ because there is sometimes overhead
// associated with a memory allocation.
{//
	StackNode<SE>* isfull;
	isfull = new StackNode<SE>(NULL, top);
	try
	{
		return 0;
	}
	catch (const bad_alloc)
	{
		return 1;
	}
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::showStructure() const
// Linked list implementation. Outputs the elements in a stack. If
// the stack is empty, outputs "Empty stack". This operation is
// intended for testing and debugging purposes only.
{
	if (!Stack<SE>::empty())
	{
		StackNode<SE>* print;
		print = top;
		while (!print == NULL)
		{
			cout << "element: " << print->element << endl;
			print = print->next;
		}
	}
}