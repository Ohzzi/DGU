//--------------------------------------------------------------------
//
//  Laboratory 6                                        queueArr.cpp
//
//  SOLUTION: Array implementation of the Queue ADT
//  2016110426_Oh Jihoon
//--------------------------------------------------------------------

#include <iostream>
#include <assert.h>
#include "queuearr.h"

using namespace std;

//--------------------------------------------------------------------

template < class QE >
Queue<QE>::Queue(int maxNumber)

// Creates an empty queue. Allocates enough memory for maxNumber
// elements (defaults to defMaxQueueSize).

	: maxSize(maxNumber + 1),
	front(maxSize - 1),
	rear(maxSize - 1) // maxSize�� ���� ũ�⺸�� 1 ũ�� �ϰ� �� ĭ�� ����. front, rear�� -1���Ͱ� �ƴ϶� maxSize -1 ���� ����.
{
	element = new QE[maxSize]; // �����Ҵ�
}

//--------------------------------------------------------------------

template < class QE >
Queue<QE>:: ~Queue()

// Frees the memory used by a queue.

{
	delete[] element; // �޸� ����
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::enqueue(const QE &newElement)

// Inserts newElement at the rear of a queue.

{
	if (!Queue<QE>::full())
	{
		rear = (rear + 1) % maxSize;
		element[rear] = newElement;
	} // rear�� 1 �������Ѽ� �� ��ġ�� newElement�� �ִ´�.
	else cout << "Queue is full" << endl;
}

//--------------------------------------------------------------------

template < class QE >
QE Queue<QE>::dequeue()

// Removes the least recently added (front) element from a queue and
// returns it.

{
	if (!Queue<QE>::empty())
	{
		QE item;
		front = (front + 1) % maxSize;
		item = element[front];
		element[front] = NULL;
		return item;
	}
	else cout << "Queue is empty" << endl;
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::clear()

// Removes all the elements from a queue.

{
	for (int i = 0; i < maxSize ; i++)
		element[i] = NULL; // �迭�� ��� ���� �ʱ�ȭ
	rear = maxSize - 1;
	front = maxSize - 1; // �ʱ� ���·� �ǵ�����.
}

//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::empty() const

// Returns 1 if a queue is empty. Otherwise, returns 0.

{
	return (rear == front); // rear == front �̸� empty
}

//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::full() const

// Returns 1 if a queue is full. Otherwise, returns 0.

{
	//if (rear + 1 == front) return true;
	//else return false;
	return ((rear + 1) % maxSize == front);
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::showStructure() const

// Array implementation. Outputs the elements in a queue. If the
// queue is empty, outputs "Empty queue". This operation is intended
// for testing and debugging purposes only.

{
	int j;   // Loop counter

	// if (front == -1)
	if (Queue<QE>::empty())
		cout << "Empty queue" << endl;
	else
	{
		cout << "front = " << front << "  rear = " << rear << endl;
		for (j = 0; j < maxSize; j++)
			cout << j << "\t";
		cout << endl;
		for (j = 0; j < maxSize; j++)
			cout << element[j] << "\t";
		cout << endl; // 0������ maxSize ���� element�� ����Ѵ�.
	}
}
template < class QE >
void Queue<QE>::putFront(const QE &newDataItem){
	//In-Lab. 2
}

template < class QE >
QE Queue<QE>::getRear(){
	//In-Lab. 2
}

template < class QE >
int Queue<QE>::getLength(){
	//In-Lab. 3
}
