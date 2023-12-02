#include "algorithms.h"

void Interchange_sort(int* arr, int size)
{
	for (int idx_1 = 0; idx_1 < size - 1; idx_1++)									// 
	{
		for (int idx_2 = idx_1 + 1; idx_2 < size; idx_2++)							//
		{
			if (arr[idx_1] > arr[idx_2])											// nếu sai vị trí
			{
				std::swap(arr[idx_1], arr[idx_2]);
			}
		}
	}
}

void Bubble_sort(int* arr, int size) 
{
	for (int idx_1 = size - 1; idx_1 > 0; idx_1--)									// thực hiện cho tất cả các phần tử:
	{
		for (int idx_2 = 0; idx_2 < idx_1; idx_2++)									// thực hiện "nổi bọt": đưa phần tử lớn nhất "nổi" lên (đưa về sau cùng)
		{
			if (arr[idx_2] > arr[idx_2 + 1])
			{
				std::swap(arr[idx_2], arr[idx_2 + 1]);
			}
		}
	}
}

void Selection_sort(int* arr, int size) 
{
	int minIdx;																		// biến lưu chỉ mục của phần tử nhỏ nhất

	for (int idx_1 = 0; idx_1 < size - 1; idx_1++)									//
	{
		minIdx = idx_1;																// đặt phần tử nhỏ nhất ở đầu mảng

		for (int idx_2 = idx_1 + 1; idx_2 < size; idx_2++)							// duyệt phần mảng chưa sắp
		{
			if (arr[minIdx] > arr[idx_2]) {
				minIdx = idx_2;														// tìm vị trí của phần tử nhỏ nhất
			}
		}

		if (minIdx != idx_1)														// đặt phần tử nhỏ nhất về đúng vị trí (đầu tiên của phần chưa sắp)
		{
			std::swap(arr[minIdx], arr[idx_1]);
		}
	}
}

void Heapify(int* arr, int size, int cur_idx) 
{
	int largest_idx = cur_idx;														// node hiện tại là node lớn nhất
	int left_child = cur_idx * 2 + 1;												// node con trái
	int right_child = cur_idx * 2 + 2;												// node con phải

	if (left_child < size && arr[left_child] > arr[largest_idx]) {
		largest_idx = left_child;													// largest is left child
	}
	if (right_child < size && arr[right_child] > arr[largest_idx]) {
		largest_idx = right_child;													// largest is right child
	}

	if (largest_idx != cur_idx)														// nếu 1 trong 2 "node con" lớn hơn "node cha", đổi chỗ
	{
		std::swap(arr[largest_idx], arr[cur_idx]);									// swap

		Heapify(arr, size, largest_idx);											// recursive
	}
}
void Heap_sort(int* arr, int size)
{
	for (int cur = size / 2 - 1; cur >= 0; cur--)									// Build Heap: create MAX HEAP
	{
		Heapify(arr, size, cur);													// heapify
	}

	for (int cur = size - 1; cur > 0; cur--)										// duyệt cây heap từ sau ra trước 
	{
		std::swap(arr[0], arr[cur]);												// đưa phần tử lớn nhất (ở cây max heap) ra cuối mảng

		Heapify(arr, cur, 0);														// duy trì tính chất cây heap
	}
}

void Merge(int* arr, int left, int mid, int right)
{
	int Left_size = mid - left + 1;													// size of left array
	int Right_size = right - mid;													// size of right array

	int idx;
	int* Left_arr = new int[Left_size];												// dynamically allocate temp array
	int* Right_arr = new int[Right_size];											// dynamically allocate temp array
	for (idx = 0; idx < Left_size; idx++) {
		Left_arr[idx] = arr[idx + left];											// sao chép phần bên trái vào mảng tạm	
	}
	for (idx = 0; idx < Right_size; idx++) {
		Right_arr[idx] = arr[idx + mid + 1];										// sao chép phần bên phải vào mảng tạm
	}

	int Left_idx, Right_idx = Left_idx = idx = 0;									// index of Left, Right, Array

	while (Left_idx < Left_size && Right_idx < Right_size)							// sao chep gia tri tu 2 mang phu vao mang chinh
	{
		if (Left_arr[Left_idx] <= Right_arr[Right_idx]) {
			arr[left + idx++] = Left_arr[Left_idx++];								// phan tu trai nho hon thi sap vao truoc
		}
		else {
			arr[left + idx++] = Right_arr[Right_idx++];								// phan tu phai nho hon thi sap vao truoc
		}
	}

	while (Left_idx < Left_size) arr[left + idx++] = Left_arr[Left_idx++];			// sao chep phan con lai cua mang ben trai neu co

	while (Right_idx < Right_size)arr[left + idx++] = Right_arr[Right_idx++];		// sao chep phan con lai cua mang ben phai neu co

	delete[] Left_arr;																// thu hồi vùng nhớ
	delete[] Right_arr;																// thu hồi vùng nhớ
}
void Merge_sort(int* arr, int left, int right) 
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;										// middle index

		Merge_sort(arr, left, mid);													// sort: left array

		Merge_sort(arr, mid + 1, right);											// sort: right array

		Merge(arr, left, mid, right);												// merge: left + right
	}
}
void Merge_sort(int* arr, int size) {
	Merge_sort(arr, 0, size - 1);													// overload Merge_sort: call function
}

void Quick_sort(int* arr, int low, int high) {
	if (low >= high) return;
	int pivotIdx = low + std::rand() % (high - low + 1);							// select pivot index: random

	std::swap(arr[pivotIdx], arr[low]);												// đưa giá trị pivot ra đầu mảng
	pivotIdx = low;																	// đặt pivot index = low index

	int first = low + 1;										        			// first unknown
	int last = high;																// last unknown

	while (first <= last) {
		while (first <= last && arr[first] < arr[pivotIdx]) first++;				// find wrong "first index"
		while (first <= last && arr[last] > arr[pivotIdx]) last--;					// find wrong "last index"

		if (first > last) break;													// has sorted

		std::swap(arr[first++], arr[last--]);										//
	}

	std::swap(arr[pivotIdx], arr[last]);

	Quick_sort(arr, low, last - 1);													// sort left (last is pivot index)
	Quick_sort(arr, last + 1, high);												// sort right (last is pivot index)
}
void Quick_sort(int* arr, int size) {
	srand(time(NULL));
	Quick_sort(arr, 0, size - 1);													// overload: call Quick_sort
}

void Counting_sort_at_exp(int* arr, int size, int exp)
{
	int* results = new int[size];													// mảng tạm thời lưu trữ kết quả sắp xếp
	
	int counts[10] = { 0 };															// khởi tạo mảng đếm số lần xuất hiện chữ số thứ i 

	for (int idx = 0; idx < size; idx++) {
		counts[(arr[idx] / exp) % 10]++;											// đếm số lần xuất hiện chữ số i
	}

	for (int dig = 1; dig < 10; dig++)												// đưa mảng đếm về mảng lưu vị trí cuối cùng của các phần tử
	{
		counts[dig] += counts[dig - 1];												// chuyển về mảng tổng tích lũy
	}

	for (int idx = size - 1; idx >= 0; idx--)										// Xây dựng mảng kết quả dựa trên tổng tích lũy và vị trí cuối cùng của từng phần tử
	{
		results[--counts[(arr[idx] / exp) % 10]] = arr[idx];						// đặt phần tử thứ idx vào đúng vị trí và giảm số đếm của mảng đếm
	}

	for (int idx = 0; idx < size; idx++) {
		arr[idx] = results[idx];													// copy arr vao mang ket qua
	}
	delete[] results;																// thu hồi vùng nhớ đã cấp phát
	results = nullptr;
}
void Radix_sort(int* arr, int size)
{
	int maxValue = arr[0];															// max element
	for (int idx = 1; idx < size; idx++) {
		if (maxValue < arr[idx]) {
			maxValue = arr[idx];													// find max
		}
	}

	for (int exp = 1; maxValue / exp > 0; exp *= 10)								// sắp xếp tới khi chữ số đầu tiên của maxV được sắp xếp đúng
	{
		Counting_sort_at_exp(arr, size, exp);										// sap xep mang theo chu so thu i = log(exp) tu phai -> trai										
	}
}