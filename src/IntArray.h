#ifndef IntArray_h
#define IntArray_h

#include <iostream>
#include <algorithm>
#include <time.h>

void input_array(int*& arr, int size, std::istream& is);										// input 

void output_array(const int* arr, int size, std::ostream& os);									// output

int* copy_array(const int* arr, int size);															// copy

void create_random_array(int*& arr, int size, int max = INT_MAX / 1000, int min = 0);			// random			(default: [0, 2147483])

void create_sorted_array(int*& arr, int size, int max = INT_MAX / 1000, int min = 0);			// sorted random	(default: [0, 2147483])

void create_reversed_array(int*& arr, int size, int max = INT_MAX / 1000, int min = 0);			// reversed random	(default: [0, 2147483])

#endif !IntArray_h
