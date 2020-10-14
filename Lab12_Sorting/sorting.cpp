#include "sorting.h"
#include <algorithm>
#include <iostream>

using namespace std;

template<class LE>
Sorting<LE>::Sorting(LE *original) 
	:list(original), num_compare(0)
{

}

template<class LE>
Sorting<LE>::~Sorting() {
	delete[] list;
}

template<class LE>
int Sorting<LE>::insertion_sort(int n) {
	//in-lab, pre-lab
	int i, j;
	num_compare = 0;
	for (i = 1; i < n; i++)
	{
		j = i;
		while (j != 0) // 비교 대상이 끝까지
		{
			if (list[j] < list[j - 1])
			{
				swap(list[j], list[j - 1]);
				j--;
				num_compare++;
			} // j번째가 j-1번째보다 작으면 스왑해주고 j--
			else j--; // 아니면 그냥 j--
		}
		print_list(0, n - 1);
	}
	return num_compare;
}


template<class LE>
int Sorting<LE>::quick_sort(int left, int right) {
	//in-lab, pre-lab
	num_compare = 0;
	return quickPartition(list, left, right);
}

template<class LE>
int Sorting<LE>::quickPartition(LE keyList[], int left, int right) {
	//in-lab, pre-lab
	int i = left + 1, j = right;
	//LE pivot = keyList[left];
	int pivot = left;
	while (i <= j) // 포인터가 엇갈릴때까지
	{
		while (keyList[i] < keyList[pivot])
		{
			num_compare++;
			i++;
		}
		while (keyList[j] > keyList[pivot])
		{
			num_compare++;
			j--;
		}
		if (i < j) swap(keyList[i++], keyList[j--]); // i번째와 j번째를 바꿔줌
		if (i > j) swap(keyList[j], keyList[pivot]); // 포인터가 엇갈리면 j번째를 피벗과 바꿔줌
	}
	print_list(left, right);
	if (left < j - 1) quickPartition(keyList, left, j - 1); // j가 기준점, j의 왼쪽에서 quicksort
	if (j + 1 < right) quickPartition(keyList, j + 1, right); // j의 오른쪽에서 quicksort
	return num_compare;
}

template<class LE>
void Sorting<LE>::merge(LE keyList[], int left, int mid, int right) {
	//in-lab, pre-lab
	LE* tmp = new LE[MAX_SIZE]; // 임시 배열을 만들어줌
	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right)
	{
		if (keyList[i] < keyList[j])
		{
			tmp[k++] = keyList[i++];
			num_compare++;
		}
		else
		{
			tmp[k++] = keyList[j++];
			num_compare++;
		}
	} // 임시 배열로 정렬해줌
	if (i > mid)
	{
		for (i = j; i <= right; i++)
			tmp[k++] = keyList[i];
	}
	else
	{
		for (j = i; j <= mid; j++)
			tmp[k++] = keyList[j];
	} // 나머지를 일괄 복사
	for (k = left; k <= right; k++)
		keyList[k] = tmp[k]; // 임시 배열을 원래 배열로 복사해줌
	print_list(left, right);
}

template<class LE>
int Sorting<LE>::merge_sort(int left, int right) {
	//in-lab, pre-lab
	if (left < right)
	{
		int middle = (left + right) / 2;
		merge_sort(left, middle);
		merge_sort(middle + 1, right);
		merge(list, left, middle, right);
	}
	return num_compare;
}

template<class LE>
void Sorting<LE>::copy_list(LE newList[], int n, int compare) {
	num_compare = compare;

	for (int i = 0; i < MAX_SIZE; i++)
		list[i] = newList[i];

}

template<class LE>
void Sorting<LE>::print_list(int left, int right) {
	for (int i = left; i < right+1 ; i++)
		cout << "|" << list[i] << "|";
	cout << endl;
}

