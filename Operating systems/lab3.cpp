#pragma warning (disable : 4996)

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

int main() {

	cout << setw(12) << "C" << setw(20) << "windows\n";
	string lines(45, '-'); lines += '\n'; cout << lines << "Task 1.\n";
	
	const size_t size = 20;
	const size_t bytes = 1;

	// task 1. Гранулярность
	int* c_adr[size], * win_adr[size];
	for (int i = 0; i < size; ++i) {
		c_adr[i] = (int*)malloc(bytes);
		win_adr[i] = (int*)LocalAlloc(LPTR, bytes);
		cout << hex << setw(16) << c_adr[i] << setw(16) << win_adr[i] << "\n";
	}
	int c_gran = c_adr[1] - c_adr[0], win_gran = win_adr[1] - win_adr[0];
	cout << lines << "Granularity: " << setw(8) << hex << c_gran << setw(16) << hex << win_gran << "\n" << lines;
	
	// task 2.
	cout << "Task 2.\n" << lines << "They both have header\n" << lines;

	// task 3. Развод блоков по размерам
	cout << "Task 3.\n";
	int* c_adr2[size], * win_adr2[size];
	long long progressive_bytes = bytes;
	for (int i = 0; i < size; ++i) {
		c_adr2[i] = (int*)malloc(progressive_bytes);
		win_adr2[i] = (int*)LocalAlloc(LPTR, progressive_bytes);
		progressive_bytes *= 2;
		cout << hex << setw(16) << c_adr2[i] << setw(16) << win_adr2[i] << "\n";
	}
	cout << lines << "They both have blocks allocation\n" << lines;

	// task 4. Есть ли слайдинг
	cout << "Task 4.\n\nSliding:\n\n" << setw(8) << "C:" << setw(16) << "win:\n";
	int* c_adr3[size], * win_adr3[size];
	const int _size = 1024 * 15;

	for (int i = 0; i < size; ++i) {
		c_adr3[i] = (int*)malloc(_size);
		win_adr3[i] = (int*)LocalAlloc(LPTR, _size);
	}
	
	for (int i = 0; i < size; ++i) {
		free(c_adr3[i]);
		LocalFree(win_adr3[i]);
		cout << setw(16) << c_adr3[i] << setw(16) << win_adr3[i] << "\n";
	}
	
	cout << lines << "They both have sliding (?)\n" << lines;

	return 0;
}