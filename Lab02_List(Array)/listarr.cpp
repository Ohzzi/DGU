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
	dataItems = new DataType[maxNumber]; // new를 통해 메모리를 동적할당한다.
}

//--------------------------------------------------------------------

List:: ~List()

// Frees the memory used by a list.

{
	// pre-lab
	delete[] dataItems; // 배열이므로 delete[]를 사용해서 메모리를 반납한다.
}

//--------------------------------------------------------------------

void List::insert(const DataType &newDataItem)
throw (logic_error)

// Inserts newDataItem after the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) data items in the
// list. In either case, moves the cursor to newDataItem.

{
	// pre-lab
	if (!List::isFull()) // 리스트가 가득 차 있는지 검사한다.
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
				size++; //커서가 맨 끝에 있으면 커서 뒤에 값을 삽입한다.
			}
			else {
				for (int i = size; i >= cursor; i--) {
					dataItems[i + 1] = dataItems[i];
				}
				dataItems[cursor] = newDataItem;
				cursor++;
				size++;
			} // 커서가 맨 끝에 있지 않으면 뒤의 값들을 하나씩 미루고 삽입한다.
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
			dataItems[i] = dataItems[i + 1]; // 커서가 위치한 곳에 있는 데이터에 커서+1번째 데이터를 덮어씌우는 것을 반복한다.
		}
		size--; // 데이터를 제거했으므로 사이즈를 1 줄인다.
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
	// size와 cursor를 초기 설정으로 바꾸어준다.
}

//--------------------------------------------------------------------

bool List::isEmpty() const

// Returns 1 if a list is empty. Otherwise, returns 0.

{
	// pre-lab
	if (size == 0) return 1;
	else return 0;
	// size가 0이면 1을, 아니면 0을 반환한다.
}

//--------------------------------------------------------------------

bool List::isFull() const

// Returns 1 if a list is full. Otherwise, returns 0.

{
	// pre-lab
	if (size == maxSize) return 1;
	else return 0;
	// size가 maxSize이면(꽉 차있으면) 1을, 아니면 0을 반환한다.
}

//--------------------------------------------------------------------
 
int List::gotoBeginning() throw (logic_error)

// Moves the cursor to the beginning of the list.

{
	// pre-lab
	if (!List::isEmpty()) {
		cursor = 0;
		return 1;
	} // 리스트가 비어있지 않다면 커서를 리스트의 제일 처음으로 보내고, true를 반환한다.
	else return 0; // 리스트가 비어있으면 false를 반환한다.
}



//--------------------------------------------------------------------

int List::gotoEnd() throw (logic_error)

// Moves the cursor to the end of the list.

{
	// pre-lab
	if (!List::isEmpty()) {
		cursor = size - 1;
		return 1;
	} // 리스트가 비어있지 않다면 커서를 리스트의 끝으로 보내고, true를 반환한다.
	else return 0; // 리스트가 비어있으면 false를 반환한다.
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
		return 1; // 리스트가 비어있지 않고 커서가 리스트의 맨 끝에 있지 않으면 커서를 증가시키고 true를 반환한다.
	}
	else return 0; // 리스트가 비어있거나 커서가 맨 끝에 있으면 false를 반환한다.
}

//--------------------------------------------------------------------

bool List::gotoPrior() throw (logic_error)

// If the cursor is not at the beginning of a list, then moves the
// cursor to the preceeding item in the list and returns true.
// Otherwise, returns false.

{
	// pre-lab
	if (!List::isEmpty() && (cursor != 0)) {
		cursor--; // 리스트가 비어있지 않고 커서가 맨 앞에 있지 않으면 커서를 이전으로 옮기고 true를 반환한다.
		return 1;
	}
	else return 0; // 리스트가 비어있거나 커서가 맨 앞에 있으면 false를 반환한다.
}

//--------------------------------------------------------------------

DataType List::getCursor() const throw (logic_error)

// Returns the item marked by the cursor.

{
	// pre-lab
	if (!List::isEmpty()) {
		return dataItems[cursor];
	}
	// 리스트가 비어있지 않으면 커서 위치의 값을 반환한다.
}

//--------------------------------------------------------------------

void List::showStructure() const

// Outputs the data items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing/debugging
// purposes only.

{
	// pre-lab
	if (!List::isEmpty()) {
		cout << "Size : " << size << endl; // 리스트의 크기 출력
		cout << "Location of the cursor : " << cursor << endl; // 현재 커서의 위치 출력
		for (int i = 0; i < size; i++) {
			cout << "data" << i << " : " << dataItems[i] << endl; // 반복문으로 첫번째 데이터부터 마지막 데이터까지 출력
		}
	}
	else cout << "The list is empty" << endl;	   	  
}
 