//--------------------------------------------------------------------
//
//  Laboratory 6                                        queueLnk.cpp
//
//  SOLUTION: Linked list implementation of the Queue ADT
//  2016110426_������
//--------------------------------------------------------------------

#include <iostream>
#include <assert.h>
#include "queueLnk.h"

using namespace std;

//--------------------------------------------------------------------

template < class QE >
QueueNode<QE>::QueueNode(const QE &elem, QueueNode<QE> *nextPtr)

// Creates a queue node containing element elem and next pointer
// nextPtr.

: element(elem),
next(nextPtr)
{}

//--------------------------------------------------------------------

template < class QE >
Queue<QE>::Queue(int ignored)

// Creates an empty queue. Parameter is provided for compatability
// with the array implementation and is ignored.

: front(0),
rear(0)
{}

//--------------------------------------------------------------------

template < class QE >
Queue<QE>:: ~Queue()

// Frees the memory used by a queue.

{
	clear();
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::enqueue(const QE &newElement)

// Inserts newElement at the rear of a queue.

{
	QueueNode<QE>* tempPtr = new QueueNode<QE>(newElement, NULL);
	if (rear == NULL)
		front = tempPtr; // ���� rear�� NULL�̸� ť�� ��� �����Ƿ� front�� tempPtr�� ������־�� ��.
	else rear->next = tempPtr; // rear�� NULL�� �ƴϸ� rear�� ���� ���� ���� ��������ش�.
	rear = tempPtr; // ���� ���� ��带 rear�� �����.
}

//--------------------------------------------------------------------

template < class QE >
QE Queue<QE>::dequeue()

// Removes the least recently (front) element from a queue and
// returns it.

{
	if (!Queue<QE>::empty())
	{
		QueueNode<QE>* tempPtr = front;
		QE item = tempPtr->element; // item�� ��ȯ�� element�� ����
		front = front->next; // front�� ���� ���� �ٲ��ش�.
		if (front == NULL) rear = NULL; // ���� front�� NULL�� �Ѿ�ٸ� �� ������ ��带 �����ϰ� �Ǵ� ���̹Ƿ� rear�� NULL�� �ٲ��ش�.
		delete tempPtr;
		return item;
	}
	else
	{
		cout << "Empty queue" << endl;
		return NULL;
	}
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::clear()

// Removes all the elements from a queue.

{
	QueueNode<QE>* tempPtr;
	while (front != NULL)
	{
		tempPtr = front;
		front = front->next;
		delete tempPtr; // front�� NULL�� �� �� ���� front�� �����Ѵ�.
	}
	rear = NULL; // front�� NULL�� �Ǹ� rear�� NULL�� �����.
}


//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::empty() const

// Returns 1 if a queue is empty. Otherwise, returns 0.

{
	if (front == NULL) return true; // front�� NULL�̸� �ʱ� �����̹Ƿ� empty��
	else return false;
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::showStructure() const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
	QueueNode<QE>* tempPtr = front;
	if (Queue<QE>::empty()) cout << "Empty queue" << endl;
	else
	{
		while (tempPtr != NULL)
		{
			cout << tempPtr->element << " ";
			tempPtr = tempPtr->next;
		} // ����� ���� tempPtr�� NULL�� �� ��(���̻� ����� element�� ���� ��) ���� tempPtr�� next�� �����鼭 element�� ���
		cout << endl;
	}
}