#include "src.h"

std::string parent_path(std::string _PATH_) {
	size_t pos = _PATH_.find_last_of("\\");
	if (!pos) {
		std::cerr << "[!] Can't found.\n";
		return _PATH_;
	}
	return _PATH_.substr(0, pos);
}

std::string path_txt(int sort_algo, int state, int size) {
	//form: <sort_algo>_<state>_<size>.txt
	std::string path = _RESULTS_PATH_;
	switch (sort_algo) {
	case Interchange: {
		path += "interchange";
		break;
	}
	case Bubble: {
		path += "bubble";
		break;
	}
	case Selection: {
		path += "selection";
		break;
	}
	case Quick: {
		path += "quick";
		break;
	}
	case Quick_randomized: {
		path += "quickRandomized";
		break;
	}
	case Merge: {
		path += "merge";
		break;
	}
	case Heap: {
		path += "heap";
		break;
	}
	case Radix: {
		path += "radix";
		break;
	}
	}

	switch (state) {
	case random: {
		path += "_random_";
		break;
	}
	case sorted: {
		path += "_sorted_";
		break;
	}
	case reversed: {
		path += "_reversed_";
		break;
	}
	}

	path += std::to_string(size) + ".txt";

	return path;
}

void write_file_results(const int *arr, int sort, int state, int size) {
	std::ofstream write_txt;
	std::string path_results_txt = path_txt(sort, state, size);
	write_txt.open(path_results_txt);
	if (!write_txt.is_open()) {
		std::cerr << "\n[!] Can't access path: " << path_results_txt;
		return;
	}
	output_array(arr, size, write_txt);
	write_txt.close();
	std::cout << "[✔️] Successfully wrote the results into: " << path_results_txt << "\n";
}

double TimeCPUused(SortFunction SORTFUNCTION, int sort, int state, int size) {
	int* testArr = nullptr;
	switch (state) {
	case random: {
		create_random_array(testArr, size);
		break;
	}
	case sorted: {
		create_sorted_array(testArr, size);
		break;
	}
	case reversed: {
		create_reversed_array(testArr, size);
		break;
	}
	}
	
	//<chrono> is more accurate than <time.h>

	auto start = std::chrono::high_resolution_clock::now();						// double start = clock();
	SORTFUNCTION(testArr, size);												// sort function
	auto end = std::chrono::high_resolution_clock::now();						// double end = clock();

	write_file_results(testArr, sort, state, size);
	delete[] testArr;
	testArr = nullptr;

	std::chrono::duration<double> duration = end - start;						//	double result = (end - start) / CLOCKS_PER_SEC;
	double result = duration.count();
	return result;
}


int main(int argc, char** argv) {
	std::ofstream write_csv;

	write_csv.open(_RUNTIME_PATH_);
	if (!write_csv.is_open()) {
		std::cerr << "[!] Can't open path: " << _RUNTIME_PATH_ << std::endl;
		return 1;
	}

	write_csv << "State,Size,Interchange,Bubble,Selection,Quick,Quick randomized,Merge,Heap,Radix\n";
	
	
	for (int state = random; state <= reversed; state++) {
		for (int idx_size = 0; idx_size < SizeDataCase; idx_size++) {
			switch (state) {
			case random: {
				write_csv << "random,";
				break;
			}
			case sorted: {
				write_csv << "sorted,";
				break;
			}
			case reversed: {
				write_csv << "reversed,";
				break;
			}
			}
			int size = DataCase[idx_size];
			write_csv << size << ",";
			int sort = Interchange;
			write_csv << TimeCPUused(Interchange_sort, sort++, state, size) << ",";
			write_csv << TimeCPUused(Bubble_sort, sort++, state, size) << ",";
			write_csv << TimeCPUused(Selection_sort, sort++, state, size) << ",";
			write_csv << TimeCPUused(Quick_sort, sort++, state, size) << ",";
			write_csv << TimeCPUused(Quick_sort_randomized, sort++, state, size) << ",";
			write_csv << TimeCPUused(Heap_sort, sort++, state, size) << ",";
			write_csv << TimeCPUused(Merge_sort, sort++, state, size) << ",";
			write_csv << TimeCPUused(Radix_sort, sort++, state, size) << ",";
			write_csv << "\n";
			
		}

	}

	write_csv.close();
	std::cout << "\n[✔️] Successfully wrote the results into: " << _RUNTIME_PATH_ << "\n";

	system("pause");
	return 0;
}