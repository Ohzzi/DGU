//--------------------------------------------------------------------
//
//  Laboratory 6                                        queueLnk.cpp
//
//  SOLUTION: Linked list implementation of the Queue ADT
//  2016110426_오지훈
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
		front = tempPtr; // 만약 rear가 NULL이면 큐가 비어 있으므로 front를 tempPtr로 만들어주어야 함.
	else rear->next = tempPtr; // rear가 NULL이 아니면 rear를 새로 만든 노드와 연결시켜준다.
	rear = tempPtr; // 새로 만든 노드를 rear로 만든다.
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
		QE item = tempPtr->element; // item에 반환할 element를 저장
		front = front->next; // front를 다음 노드로 바꿔준다.
		if (front == NULL) rear = NULL; // 만약 front가 NULL로 넘어갔다면 맨 마지막 노드를 제거하게 되는 것이므로 rear도 NULL로 바꿔준다.
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
		delete tempPtr; // front가 NULL이 될 때 까지 front를 제거한다.
	}
	rear = NULL; // front가 NULL이 되면 rear도 NULL로 만든다.
}


//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::empty() const

// Returns 1 if a queue is empty. Otherwise, returns 0.

{
	if (front == NULL) return true; // front가 NULL이면 초기 상태이므로 empty임
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
		} // 출력을 위한 tempPtr이 NULL이 될 때(더이상 출력할 element가 없을 때) 까지 tempPtr을 next로 보내면서 element를 출력
		cout << endl;
	}
}