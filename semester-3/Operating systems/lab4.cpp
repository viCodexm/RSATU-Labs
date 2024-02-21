#pragma warning (disable : 4996)

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

void CreateProc(LPSTR process_name) {
	STARTUPINFOA startupInfo = { 0 };
	PROCESS_INFORMATION processInformation = { 0 };
	startupInfo.cb = sizeof(STARTUPINFOA);

	CreateProcessA(NULL, process_name, NULL, NULL, FALSE,
		NULL, NULL, NULL, &startupInfo, &processInformation);

	WaitForSingleObject(processInformation.hProcess, INFINITE);
	CloseHandle(processInformation.hProcess);
	CloseHandle(processInformation.hThread);
}

int main() {
	int n = 0; cin >> n;
	switch (n)
	{
	case 1:
		CreateProc((LPSTR)"calc.exe");
		break;
	case 2:
		WinExec("calc.exe", SW_SHOW);
		break;
	case 3:
		ShellExecute(NULL, NULL,
			L"C:\\Users\\guest\\source\\repos\\ipb-22_labs\\excel_doc.xlsx", 
			NULL, NULL, SW_SHOW);
	default:
		break;
	}
	return 0;
}