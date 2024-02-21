#pragma warning (disable : 4996)

#include <Windows.h>
#include <iostream>
#include <memoryapi.h>
#include <winnt.h>
#include <iomanip>
#include <sstream>

using namespace std;

void print_state(MEMORY_BASIC_INFORMATION& meminfo) {
	cout << setw(12);
	switch (meminfo.Type)
	{
	case MEM_IMAGE:
		cout << "MEM_IMAGE";
		break;
	case MEM_MAPPED:
		cout << "MEM_MAPPED";
		break;
	case MEM_PRIVATE:
		cout << "MEM_PRIVATE";
		break;
	}
	
	cout << setw(8);

	switch (meminfo.AllocationProtect) {
	case NULL:
		cout << "NO_ACCESS";
		break;
	case PAGE_EXECUTE:
		cout << "PE";
		break;
	case PAGE_EXECUTE_READ:
		cout << "PER";
		break;
	case PAGE_EXECUTE_READWRITE:
		cout << "PERW";
		break;
	case PAGE_EXECUTE_WRITECOPY:
		cout << "PEWC";
		break;
	case PAGE_NOACCESS:
		cout << "PNA";
		break;
	case PAGE_READONLY:
		cout << "PRO";
		break;
	case PAGE_READWRITE:
		cout << "PRW";
		break;
	case PAGE_WRITECOPY:
		cout << "PWC";
		break;
	case PAGE_TARGETS_INVALID:
		cout << "PTI / PTNU";
		break;
	case PAGE_GUARD:
		cout << "PAGE_GUARD";
		break;
	case PAGE_NOCACHE:
		cout << "PAGE_NOCACHE";
		break;
	case PAGE_WRITECOMBINE:
		cout << "PAGE_WRITECOMBINE";
		break;
	}
	cout << " ";
}

void print_procces_info(BYTE* current) {
	cout << "\n";
	const int SIZE = 256;
	WCHAR buf[SIZE];
	memset(&buf, false, sizeof buf);
	GetModuleFileNameW((HMODULE)(current), buf, sizeof buf / sizeof buf[0]);
	int idx = 0;
	while (idx < SIZE && buf[idx] != NULL) {
		cout << (char)buf[idx];
		idx++;
	}
	cout << "\n";
}

int main() {
	BYTE* current = NULL;

	cout << "Current:   BaseAddr:  AllocBase:  RegionSize:  Type:  Protect:\n";
	while ((int)(current) >= 0) {

		MEMORY_BASIC_INFORMATION meminfo;
		if (!VirtualQuery((LPVOID)current, &meminfo, sizeof meminfo))
			break;
		
		cout << hex
			<< setw(8) << (int)current << " "
			<< setw(10) << meminfo.BaseAddress << " "
			<< setw(10) << meminfo.AllocationBase << " "
			<< setw(9) << meminfo.RegionSize << " ";

		if (meminfo.State == MEM_COMMIT) {
			print_state(meminfo);
			if (meminfo.Type == MEM_IMAGE && ((char)*current == 'M') && ((char)*(current + 1) == 'Z') && ((int)current % 65536 == 0))
				print_procces_info(current);

		}
		else if (meminfo.State == MEM_FREE)
			cout << setw(12) << "!FREE!";
		else if (meminfo.State == MEM_RESERVE)
			cout << setw(12) << "!RESERVE!";
		
		
		current += meminfo.RegionSize;
		cout << "\n";
	}
	return 0;
}