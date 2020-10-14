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
		size++; // heap�� �� ���� ������ �߰�
		while (child != 0)
		{
			if (element[child].pty() > element[parent].pty())
			{
				HE tempHeap = element[child];
				element[child] = element[parent];
				element[parent] = tempHeap;
				child = parent;
				parent = child / 2;
			} // heap���� (bottom����)
			else break;
		}
	}
}

template < class HE >
HE Heap<HE>::removeMax()
{
	if (!empty())
	{
		HE result = element[0]; // ��ȯ���� �� ���� ������
		element[0] = element[size-1];
		size--; // ù��° �����Ϳ� �� ������ �����͸� �ٲ��� �� �� ������ ���� ����

		int parent = 0;
		int child = parent * 2 + 1;
		while (child < size) // left subtree�� �����ϴ� �� ��� ��
		{
			if (child +1 < size) // right subtree�� ����
			{
				if (element[child].pty() < element[child + 1].pty())
					child++; // right subtree�� left���� ũ�� parent�� right�� ���ؾ� �Ѵ�.
			}
			if (element[parent].pty() < element[child].pty())
			{
				HE tempHeap = element[child];
				element[child] = element[parent];
				element[parent] = tempHeap;
				parent = child;
				child = parent * 2 + 1;
			} // child�� parent���� ũ�� ���� �ٲ��ش�
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
		cout << endl << endl; // array�� ���
		showSubtree(0, 0); // tree�� ���
	}
}

template < class HE >
void Heap<HE>::showSubtree(int index, int level) const
{
	int j; // counter

	if (index < size)
	{
		showSubtree(2 * index + 2, level + 1); // right subtree ���
		for (j = 0; j < level; j++)
			cout << "\t";
		cout << " " << element[index].pty();
		if (2 * index + 2 < size) // subtree�� ���� �� ������ < ���
			cout << "<";
		else if (2 * index + 1 < size) // subtree�� left�� ������ \���
			cout << "\\";
		cout << endl;
		showSubtree(2 * index + 1, level + 1); // left subtree ���
	}
}