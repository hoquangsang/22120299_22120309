#include "src.h"

std::string parent_path(std::string _PATH_) {
	size_t pos = _PATH_.find_last_of("\\");												// tìm dấu '\' cuối cùng trong "path"
	if (!pos) {
		std::cerr << "[!] Can't found.\n";
		return _PATH_;
	}
	return _PATH_.substr(0, pos);														// trả về đường dẫn cha: đường dẫn trước dấu \ cuối cùng
}

std::string path_txt(int sort_algo, int state, int size) {
	//form: <sort_algo>_<state>_<size>.txt
	std::string path = _RESULTS_PATH_;													// đường dẫn tới .\results

	switch (sort_algo)																	// tên thuật toán (sort algorithm)
	{
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

	switch (state)																		// tên trạng thái (state)
	{
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

	path += std::to_string(size) + ".txt";												// kích thước (size)

	return path;																		// file: sortalgo_state_size.txt
}

void write_file_results(const int *arr, int sort, int state, int size) {
	std::ofstream write_txt;															// luồng ghi vào file txt (trong .\results)
	std::string path_results_txt = path_txt(sort, state, size);							// đường dẫn tới vị trí cần ghi
	write_txt.open(path_results_txt);													// mở file / tạo file

	if (!write_txt.is_open()) {
		std::cerr << "\n[!] Can't access path: " << path_results_txt;
		return;
	}
	output_array(arr, size, write_txt);													// thực hiện ghi file: std::ostream = std::ofstream : write_txt
	write_txt.close();																	// đóng file dẫn

	std::cout << "[✔️] Successfully wrote the results into: " << path_results_txt << "\n";
}

double TimeCPUused(SortFunction SORTFUNCTION, const int *arr, int sort, int state, int size) {
	int* testArr = copy_array(arr, size);												// copy mảng tạm để không thay đổi mảng ban đầu
	
	//<chrono> is more accurate than <time.h>

	auto start = std::chrono::high_resolution_clock::now();								// bắt đầu đo thời gian
	SORTFUNCTION(testArr, size);														// sắp xếp mảng tạm
	auto end = std::chrono::high_resolution_clock::now();								// kết thúc đo thời gian

	write_file_results(testArr, sort, state, size);										// ghi kết quả sau sắp xếp vào file kết quả
	delete[] testArr;																	// thu hồi vùng nhớ đã cấp phát
	testArr = nullptr;

	std::chrono::duration<double> duration = end - start;								//	đếm thời gian chạy từ start -> end
	double result = duration.count();
	return result;
}


int main(int argc, char** argv) {
	std::ofstream write_csv;															// luồng ghi vào file runtime.csv

	write_csv.open(_RUNTIME_PATH_);														// mở ghi/tạo file tới đường dẫn file runtime.csv
	if (!write_csv.is_open()) {
		std::cerr << "[!] Can't open path: " << _RUNTIME_PATH_ << std::endl;
		return 1;
	}

	write_csv << "State,Size,Interchange,Bubble,Selection,Quick,Merge,Heap,Radix,\n";	// thứ tự trên hàng đầu tiên
	
	
	for (int state = random; state <= reversed; state++)								// state có 3 trạng thái: random, sorted, reversed
	{
		for (int idx_size = 0; idx_size < SizeDataCase; idx_size++)						// size có 5 kích thước: 1 000, 3 000, 10 000, 30 000, 100 000
		{
			int* arr = nullptr;
			int size = DataCase[idx_size];												// kích thước cho CASE TEST

			switch (state) {
			case random: {
				create_random_array(arr, size);											// khởi tạo 1 mảng với state = random
				write_csv << "random,";
				break;
			}
			case sorted: {
				create_sorted_array(arr, size);											// khởi tạo 1 mảng với state = sorted
				write_csv << "sorted,";
				break;
			}
			case reversed: {
				create_reversed_array(arr, size);										// khởi tạo 1 mảng với state = reversed
				write_csv << "reversed,";
				break;
			}
			}

			write_csv << size << ",";
			int sort = Interchange;														// thứ tự đầu tiên: từ interchange

			write_csv << TimeCPUused(Interchange_sort, arr, sort++, state, size) << ",";// ghi thời gian chạy của Interchange_sort
			write_csv << TimeCPUused(Bubble_sort, arr, sort++, state, size) << ",";		// ghi thời gian chạy của Bubble_sort
			write_csv << TimeCPUused(Selection_sort, arr, sort++, state, size) << ",";	// ghi thời gian chạy của Selection_sort
			write_csv << TimeCPUused(Quick_sort, arr, sort++, state, size) << ",";		// ghi thời gian chạy của Quick_sort
			write_csv << TimeCPUused(Heap_sort, arr, sort++, state, size) << ",";		// ghi thời gian chạy của Heap_sort
			write_csv << TimeCPUused(Merge_sort, arr, sort++, state, size) << ",";		// ghi thời gian chạy của Merge_sort
			write_csv << TimeCPUused(Radix_sort, arr, sort++, state, size) << ",";		// ghi thời gian chạy của Radix_sort
			write_csv << "\n";
			
			delete[] arr;
			arr = nullptr;
		}
	}

	write_csv.close();																	// đóng file


	std::cout << "\n[✔️] Successfully wrote the results into: " << _RUNTIME_PATH_ << "\n";
	system("pause");
	return 0;
}