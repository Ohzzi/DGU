#include "heap.h"
#include <iostream>

using namespace std;

template < class HE >
Heap<HE>::Heap(int maxNumber)
	:maxSize(maxNumber), size(0), element(new HE[maxNumber])
{
	// constructor
}

template < class HE >
Heap<HE>::~Heap()
{
	delete[] element;
	// destructor
}

template < class HE >
void Heap<HE>::insert(const HE& newElement)
{
	if (!full())
	{
		int child = size;
		int parent = size / 2;
		element[size] = newElement;
		size++; // heap의 맨 끝에 데이터 추가
		while (child != 0)
		{
			if (element[child].pty() > element[parent].pty())
			{
				HE tempHeap = element[child];
				element[child] = element[parent];
				element[parent] = tempHeap;
				child = parent;
				parent = child / 2;
			} // heap정렬 (bottom부터)
			else break;
		}
	}
}

template < class HE >
HE Heap<HE>::removeMax()
{
	if (!empty())
	{
		HE result = element[0]; // 반환값은 맨 위의 데이터
		element[0] = element[size-1];
		size--; // 첫번째 데이터와 맨 마지막 데이터를 바꿔준 후 맨 마지막 값을 삭제

		int parent = 0;
		int child = parent * 2 + 1;
		while (child < size) // left subtree가 존재하는 한 계속 비교
		{
			if (child +1 < size) // right subtree가 존재
			{
				if (element[child].pty() < element[child + 1].pty())
					child++; // right subtree가 left보다 크면 parent를 right와 비교해야 한다.
			}
			if (element[parent].pty() < element[child].pty())
			{
				HE tempHeap = element[child];
				element[child] = element[parent];
				element[parent] = tempHeap;
				parent = child;
				child = parent * 2 + 1;
			} // child가 parent보다 크면 둘을 바꿔준다
			else break;
		}
		return result;
	}
	else
	{
		HE result;
		result.setPty(0);
		return result;
	}
}

template < class HE >
void Heap<HE>::clear()
{
	size = 0;
}

template < class HE >
int Heap<HE>::empty() const
{
	if (size == 0) return true;
	else return false;
}

template < class HE >
int Heap<HE>::full() const
{
	if (size == maxSize) return true;
	else return false;
}

template < class HE >
void Heap<HE>::showStructure() const
{
	int j; // counter

	cout << endl;
	if (empty())
		cout << "Empty heap" << endl;
	else
	{
		cout << "size = " << size << endl;
		for (j = 0; j < maxSize; j++)
			cout << j << "\t";
		cout << endl;
		for (j = 0; j < size; j++)
			cout << element[j].pty() << "\t";
		cout << endl << endl; // array로 출력
		showSubtree(0, 0); // tree로 출력
	}
}

template < class HE >
void Heap<HE>::showSubtree(int index, int level) const
{
	int j; // counter

	if (index < size)
	{
		showSubtree(2 * index + 2, level + 1); // right subtree 출력
		for (j = 0; j < level; j++)
			cout << "\t";
		cout << " " << element[index].pty();
		if (2 * index + 2 < size) // subtree가 양쪽 다 있으면 < 출력
			cout << "<";
		else if (2 * index + 1 < size) // subtree가 left만 있으면 \출력
			cout << "\\";
		cout << endl;
		showSubtree(2 * index + 1, level + 1); // left subtree 출력
	}
}