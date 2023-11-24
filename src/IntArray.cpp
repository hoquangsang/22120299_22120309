#include "IntArray.h"

void input_array(int*& arr, int size, std::istream& is) {
	if (arr) delete[] arr;										// clear
	arr = new (std::nothrow) int[size];							// Dynamically allocate an array
	if (!arr) {
		std::cerr << "[!] Memory drained.\n";					// not enough memory	
		exit(-1);												// exit program
	}

	for (int idx = 0; idx < size; idx++) {
		is >> arr[idx];											// istream: input array
	}
}

void output_array(const int* arr, int size, std::ostream& os) {
	for (int idx = 0; idx < size; idx++) {
		os << arr[idx] << " ";									// ostream: output array
	}
	os << std::endl;
}

void create_random_array(int*& arr, int size, int max, int min) {
	if (arr) delete[] arr;										// clear
	arr = new (std::nothrow) int[size];							// dynamically allocate an array
	if (!arr) {
		std::cerr << "[!] Memory drained.\n";					// not enough memory
		exit(-1);												// exit program
	}
	
	srand(time(NULL));											// random: seed = NULL
	for (int idx = 0; idx < size; idx++) {
		arr[idx] = min + (rand() * rand()) % (max - min + 1);	// random: [min, max]
	}
}

void create_sorted_array(int*& arr, int size, int max, int min) {
	if (arr) delete[] arr;										// clear
	arr = new (std::nothrow) int[size];							// dynamically allocate an array
	if (!arr) {
		std::cerr << "[!] Memory drained.\n";					// not enough memory
		exit(-1);												// exit program
	}
	
	srand(time(NULL));											// random: seed = NULL
	for (int idx = 0; idx < size; idx++) {
		arr[idx] = min + (rand() * rand()) % (max - min + 1);	// random: [min, max]
	}
	std::sort(arr, arr + size);									// sort: ascending array
}

void create_reversed_array(int*& arr, int size, int max, int min) {
	if (arr) delete[] arr;										// clear
	arr = new (std::nothrow) int[size];							// dynamically allocate an array
	if (!arr) {
		std::cerr << "[!] Memory drained.\n";					// not enough memory
		exit(-1);												// exit program
	}

	srand(time(NULL));											// random: seed = NULL
	for (int idx = 0; idx < size; idx++) {
		arr[idx] = min + (rand() * rand()) % (max - min + 1);	// random: [min, max]
	}
	std::sort(arr, arr + size, std::greater<int>());			// sort: descending array
}