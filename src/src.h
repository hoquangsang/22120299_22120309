#ifndef src_h
#define src_h

#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <chrono>
#include <time.h>

#include "IntArray.h"														// header: functions of int array

#include "algorithms.h"														// header: sort algorithms

typedef void (*SortFunction)(int* NameArray, int SizeArray);				// void pointer: call sort functions

enum SortOrder																// status: sort order in runtime.csv (column)
{
	Interchange = 1,
	Bubble = 2,
	Selection = 3,
	Quick = 4,
	Merge = 5,
	Heap = 6,
	Radix = 7
};

enum StateOrder																// status: state order in runtime.csv (row)
{
	random = 0, sorted = 1, reversed = 2
};

const int DataCase[] = { 1000, 3000, 10000, 30000, 100000 };				// array: data test

const int SizeDataCase = sizeof(DataCase) / sizeof(DataCase[0]);			// size of array data test

std::string parent_path(std::string _PATH_ = __FILE__);						// function: get parent directory

void write_file_results(const int*, int, int, int);							// function: write file txt in results folder

double TimeCPUused(SortFunction, const int*, int, int, int);				// function: get time CPU used


const std::string _PROGRAM_PATH_ = __FILE__;								// path: file main.cpp

const std::string _SRC_PATH_ = parent_path(_PROGRAM_PATH_);					// path: folder ./src (containing main.cpp, algorithms.cpp, algorithm.h,...)

const std::string _DIRECTORY_PATH_ = parent_path(_SRC_PATH_);				// path: folder 22120299_22120309 - directory root (containing ./src, ./results, runtime.csv, report.pdf)

const std::string _RUNTIME_PATH_ = _DIRECTORY_PATH_ + "\\runtime.csv";		// path: file runtime.csv

const std::string _RESULTS_PATH_ = _DIRECTORY_PATH_ + "\\results\\";		// path: folder ./results

#endif !src_h
//https://en.cppreference.com/w/cpp/chrono
//https://daynhauhoc.com/t/ham-thoi-gian-trong-c-c/66426/6