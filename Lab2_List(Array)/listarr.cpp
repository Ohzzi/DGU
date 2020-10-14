//--------------------------------------------------------------------
//
//                                                       listarr.cpp
//
//  SOLUTION: Array implementation of the List ADT
//
//--------------------------------------------------------------------


#include "listarr.h"

using namespace std;

//--------------------------------------------------------------------

List::List(int maxNumber)

// Creates an empty list. Allocates enough memory for maxNumber
// data items (defaults to defMaxListSize).

: maxSize(maxNumber),
size(0),
cursor(-1)
{
	// pre-lab
	dataItems = new DataType[maxNumber]; // new�� ���� �޸𸮸� �����Ҵ��Ѵ�.
}

//--------------------------------------------------------------------

List:: ~List()

// Frees the memory used by a list.

{
	// pre-lab
	delete[] dataItems; // �迭�̹Ƿ� delete[]�� ����ؼ� �޸𸮸� �ݳ��Ѵ�.
}

//--------------------------------------------------------------------

void List::insert(const DataType &newDataItem)
throw (logic_error)

// Inserts newDataItem after the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) data items in the
// list. In either case, moves the cursor to newDataItem.

{
	// pre-lab
	if (!List::isFull()) // ����Ʈ�� ���� �� �ִ��� �˻��Ѵ�.
	{
		if (List::isEmpty()) {
			dataItems[size] = newDataItem;
			cursor = size;
			size++;
		}
		else if (!List::isEmpty()) {
			if ((size - cursor) == 1) {
				dataItems[size] = newDataItem;
				cursor = size;
				size++; //Ŀ���� �� ���� ������ Ŀ�� �ڿ� ���� �����Ѵ�.
			}
			else {
				for (int i = size; i >= cursor; i--) {
					dataItems[i + 1] = dataItems[i];
				}
				dataItems[cursor] = newDataItem;
				cursor++;
				size++;
			} // Ŀ���� �� ���� ���� ������ ���� ������ �ϳ��� �̷�� �����Ѵ�.
		}
	}
	else cout << "The list is full" << endl;
}

//--------------------------------------------------------------------

void List::remove() throw (logic_error)

// Removes the data items  marked by the cursor from a list. Moves the
// cursor to the next data item item in the list. Assumes that the
// first list data items "follows" the last list data item.

{
	// pre-lab
	if (!List::isEmpty()) {
		for (int i = cursor; i < size - 1; i++) {
			dataItems[i] = dataItems[i + 1]; // Ŀ���� ��ġ�� ���� �ִ� �����Ϳ� Ŀ��+1��° �����͸� ������ ���� �ݺ��Ѵ�.
		}
		size--; // �����͸� ���������Ƿ� ����� 1 ���δ�.
	}
	else cout << "The list is already Empty" << endl;
}

//--------------------------------------------------------------------

void List::replace(const DataType &newDataItem)
throw (logic_error)

// Replaces the item marked by the cursor with newDataItem and
// leaves the cursor at newDataItem.

{
	// Requires that the list is not empty
	// pre-lab
	if (!List::isEmpty()) {
		dataItems[cursor] = newDataItem;
	}
	else cout << "The list is Empty" << endl;
}

//--------------------------------------------------------------------

void List::clear()

// Removes all the data items from a list.

{
	// pre-lab
	size = 0;
	cursor = -1;
	// size�� cursor�� �ʱ� �������� �ٲپ��ش�.
}

//--------------------------------------------------------------------

bool List::isEmpty() const

// Returns 1 if a list is empty. Otherwise, returns 0.

{
	// pre-lab
	if (size == 0) return 1;
	else return 0;
	// size�� 0�̸� 1��, �ƴϸ� 0�� ��ȯ�Ѵ�.
}

//--------------------------------------------------------------------

bool List::isFull() const

// Returns 1 if a list is full. Otherwise, returns 0.

{
	// pre-lab
	if (size == maxSize) return 1;
	else return 0;
	// size�� maxSize�̸�(�� ��������) 1��, �ƴϸ� 0�� ��ȯ�Ѵ�.
}

//--------------------------------------------------------------------
 
int List::gotoBeginning() throw (logic_error)

// Moves the cursor to the beginning of the list.

{
	// pre-lab
	if (!List::isEmpty()) {
		cursor = 0;
		return 1;
	} // ����Ʈ�� ������� �ʴٸ� Ŀ���� ����Ʈ�� ���� ó������ ������, true�� ��ȯ�Ѵ�.
	else return 0; // ����Ʈ�� ��������� false�� ��ȯ�Ѵ�.
}



//--------------------------------------------------------------------

int List::gotoEnd() throw (logic_error)

// Moves the cursor to the end of the list.

{
	// pre-lab
	if (!List::isEmpty()) {
		cursor = size - 1;
		return 1;
	} // ����Ʈ�� ������� �ʴٸ� Ŀ���� ����Ʈ�� ������ ������, true�� ��ȯ�Ѵ�.
	else return 0; // ����Ʈ�� ��������� false�� ��ȯ�Ѵ�.
}

//--------------------------------------------------------------------

bool List::gotoNext() throw (logic_error)

// If the cursor is not at the end of a list, then moves the
// cursor to the next item in the list and returns true. Otherwise,
// returns false.

{
	// pre-lab
	if (!List::isEmpty() && !(cursor == size - 1)) {
		cursor++;
		return 1; // ����Ʈ�� ������� �ʰ� Ŀ���� ����Ʈ�� �� ���� ���� ������ Ŀ���� ������Ű�� true�� ��ȯ�Ѵ�.
	}
	else return 0; // ����Ʈ�� ����ְų� Ŀ���� �� ���� ������ false�� ��ȯ�Ѵ�.
}

//--------------------------------------------------------------------

bool List::gotoPrior() throw (logic_error)

// If the cursor is not at the beginning of a list, then moves the
// cursor to the preceeding item in the list and returns true.
// Otherwise, returns false.

{
	// pre-lab
	if (!List::isEmpty() && (cursor != 0)) {
		cursor--; // ����Ʈ�� ������� �ʰ� Ŀ���� �� �տ� ���� ������ Ŀ���� �������� �ű�� true�� ��ȯ�Ѵ�.
		return 1;
	}
	else return 0; // ����Ʈ�� ����ְų� Ŀ���� �� �տ� ������ false�� ��ȯ�Ѵ�.
}

//--------------------------------------------------------------------

DataType List::getCursor() const throw (logic_error)

// Returns the item marked by the cursor.

{
	// pre-lab
	if (!List::isEmpty()) {
		return dataItems[cursor];
	}
	// ����Ʈ�� ������� ������ Ŀ�� ��ġ�� ���� ��ȯ�Ѵ�.
}

//--------------------------------------------------------------------

void List::showStructure() const

// Outputs the data items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing/debugging
// purposes only.

{
	// pre-lab
	if (!List::isEmpty()) {
		cout << "Size : " << size << endl; // ����Ʈ�� ũ�� ���
		cout << "Location of the cursor : " << cursor << endl; // ���� Ŀ���� ��ġ ���
		for (int i = 0; i < size; i++) {
			cout << "data" << i << " : " << dataItems[i] << endl; // �ݺ������� ù��° �����ͺ��� ������ �����ͱ��� ���
		}
	}
	else cout << "The list is empty" << endl;	   	  
}
 