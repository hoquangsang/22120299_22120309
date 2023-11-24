#include "algorithms.h"

void Interchange_sort(int* arr, int size) {
	int temp;														// use swap

	for (int idx_1 = 0; idx_1 < size - 1; idx_1++)					//
	{
		for (int idx_2 = idx_1 + 1; idx_2 < size; idx_2++)			//
		{
			if (arr[idx_1] > arr[idx_2])							// swap
			{
				temp = arr[idx_1];
				arr[idx_1] = arr[idx_2];
				arr[idx_2] = temp;
			}
		}
	}
}

void Selection_sort(int* arr, int size) {
	int minIdx;														//
	int temp;														//

	for (int idx_1 = 0; idx_1 < size - 1; idx_1++)					//
	{
		minIdx = idx_1;												//

		for (int idx_2 = idx_1 + 1; idx_2 < size; idx_2++)			// tìm phần tử nhỏ nhất ở mảng chưa sắp
		{
			if (arr[minIdx] > arr[idx_2]) {
				minIdx = idx_2;
			}
		}
		if (minIdx != idx_1)										// đặt phần tử nhỏ nhất về đúng vị trí (đầu tiên của phần chưa sắp)
		{
			temp = arr[minIdx];
			arr[minIdx] = arr[idx_1];
			arr[idx_1] = temp;
		}
	}
}

void Bubble_sort(int* arr, int size) {
	int temp;

	for (int idx_1 = size - 1; idx_1 > 0; idx_1--)					// thực hiện cho tất cả các phần tử:
	{

		for (int idx_2 = 0; idx_2 < idx_1; idx_2++)					// thực hiện "nổi bọt": đưa phần tử lớn nhất "nổi" lên (đưa về sau cùng)
		{
			if (arr[idx_2] > arr[idx_2 + 1])
			{
				temp = arr[idx_2];
				arr[idx_2] = arr[idx_2 + 1];
				arr[idx_2 + 1] = temp;
			}
		}
	}
}

void Heapify(int* arr, int size, int cur_idx) {
	int largest_idx = cur_idx;										//
	int left_child = cur_idx * 2 + 1;								//
	int right_child = cur_idx * 2 + 2;								//

	if (left_child < size && arr[left_child] > arr[largest_idx]) {
		largest_idx = left_child;									// largest is left child
	}
	if (right_child < size && arr[right_child] > arr[largest_idx]) {
		largest_idx = right_child;									// largest is right child
	}

	if (largest_idx != cur_idx)										// nếu 1 trong 2 "node con" lớn hơn "node cha", đổi chỗ
	{
		int temp = arr[largest_idx];								// swap
		arr[largest_idx] = arr[cur_idx];
		arr[cur_idx] = temp;

		Heapify(arr, size, largest_idx);							// recursive
	}
}
void Heap_sort(int* arr, int size) {

	for (int cur = size / 2 - 1; cur >= 0; cur--)					// Build Heap: create MAX HEAP
	{
		Heapify(arr, size, cur);									// heapify
	}

	int temp;														// use to swap
	for (int cur = size - 1; cur > 0; cur--)						// đưa phần tử lớn nhất (ở cây max heap) ra cuối mảng
	{
		temp = arr[cur]; arr[cur] = arr[0]; arr[0] = temp;			// swap

		Heapify(arr, cur, 0);										// duy trì tính chất cây heap
	}
}

void Merge(int* arr, int left, int mid, int right) {
	int Lsize = mid - left + 1;										// size of left array
	int Rsize = right - mid;										// size of right array

	int idx;
	int* Larr = new int[Lsize];										// dynamically allocate temp array
	int* Rarr = new int[Rsize];										// dynamically allocate temp array
	for (idx = 0; idx < Lsize; idx++) {
		Larr[idx] = arr[idx + left];								// sao chép phần bên trái vào mảng tạm	
	}
	for (idx = 0; idx < Rsize; idx++) {
		Rarr[idx] = arr[idx + mid + 1];								// sao chép phần bên phải vào mảng tạm
	}

	int Lidx, Ridx = Lidx = idx = 0;								// index of Left, Right, Array

	while (Lidx < Lsize && Ridx < Rsize)							// sao chep gia tri tu 2 mang phu vao mang chinh
	{
		if (Larr[Lidx] <= Rarr[Ridx]) {
			arr[left + idx++] = Larr[Lidx++];						// phan tu trai nho hon thi sap vao truoc
		}
		else {
			arr[left + idx++] = Rarr[Ridx++];						// phan tu phai nho hon thi sap vao truoc
		}
	}

	while (Lidx < Lsize) arr[left + idx++] = Larr[Lidx++];			// sao chep phan con lai cua mang ben trai neu co

	while (Ridx < Rsize)arr[left + idx++] = Rarr[Ridx++];			// sao chep phan con lai cua mang ben phai neu co

	delete[] Larr;
	delete[] Rarr;
}
void Merge_sort(int* arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;						// middle index

		Merge_sort(arr, left, mid);									// sort: left array

		Merge_sort(arr, mid + 1, right);							// sort: right array

		Merge(arr, left, mid, right);								// merge: left + right
	}
}
void Merge_sort(int* arr, int size) {
	Merge_sort(arr, 0, size - 1);									// overload Merge_sort: call funtion
}

void Quick_sort(int* arr, int low, int high) {
	if (low >= high) return;

	int pivotIdx = (low + high) / 2;								// select pivot index: between array
	int first = low;												// first unknown
	int last = high;												// last unknown

	while (true) {
		while (arr[first] < arr[pivotIdx]) first++;					// find wrong "first index"
		while (arr[last] > arr[pivotIdx]) last--;					// find wrong "last index"

		if (first > last) break;									// has sorted

		std::swap(arr[first++], arr[last--]);						// else: swap wrong index
	}
	Quick_sort(arr, low, last);										// sort left array pivot
	Quick_sort(arr, first, high);									// sort right array pivot
}
void Quick_sort(int* arr, int size) {
	Quick_sort(arr, 0, size - 1);									// overload Quick_sort: call function
}

void Quick_sort_randomized(int* arr, int low, int high) {
	if (low >= high) return;

	srand((time(NULL)));
	int pivotIdx = low + rand() % (high - low + 1);					// select pivot index: random

	std::swap(arr[pivotIdx], arr[(low + high) / 2]);				// swap pivot - middle 
	pivotIdx = (low + high) / 2;									// put P in the middle of the array

	int first = low;												// first unknown
	int last = high;												// last unknown
	while (true) {
		while (arr[first] < arr[pivotIdx]) first++;					// find wrong "first index"
		while (arr[last] > arr[pivotIdx]) last--;					// find wrong "last index"

		if (first > last) break;									// has sorted

		std::swap(arr[first++], arr[last--]);						// else: swap wrong index
	}
	Quick_sort(arr, low, last);										// sort left array
	Quick_sort(arr, first, high);									// sort right array
}
void Quick_sort_randomized(int* arr, int size) {
	Quick_sort_randomized(arr, 0, size - 1);						// overload Quick_sort_randomized: call function
}

void Radix_sort(int* arr, int size) {
	/*
			| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
		0	|
	   ...	|
	 size-1 |

	*/

	int** Buckets = new int* [size + 1];							// Create Buckets to sort elements: row = size
	for (int row = 0; row < size; row++) {
		Buckets[row] = new int[10];									// columns = 10 = radix DEC
	}

	for (int exp = 1; ; exp *= 10) {								// sort by: digit [log10(exp) + 1]

		int countDigits[10] = { 0 };								// radix counting array

		for (int idx = 0; idx < size; idx++) {
			int dig = (arr[idx] / exp) % 10;						// is col or [radix]
			Buckets[countDigits[dig]++][dig] = arr[idx];			// put the elements into array B
		}

		if (countDigits[0] == size) break;							// array is sorted when all element have radix: 0 

		for (int dig = 0, idx = 0; dig < 10; dig++) 				// copy Buckets into array in order: first column -> last column
		{
			for (int row = 0; row < countDigits[dig]; row++)		// copy buckets into array in order: first row -> last row
			{
				arr[idx++] = Buckets[row][dig];
			}
		}
	}

	if (Buckets) {
		for (int row = 0; row < size; row++) {
			if (Buckets[row]) {
				delete[] Buckets[row];								// clear *Buckets
				Buckets[row] = nullptr;
			}
		}
		delete[] Buckets;											// clear **Buckets
		Buckets = nullptr;
	}
}
