#pragma warning (disable : 4996)

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <io.h>

using namespace std;

int main() {
	//HWND hWnd = FindWindowA((LPCSTR)"OGNDOWSPROJECT", (LPCSTR)"WindowsProject");
	HWND hWnd = FindWindowA(NULL, (LPCSTR)"WindowsProject");
	cout << hWnd << endl;

	LPCTSTR lpszString = L"Hello World :)";
	wstring lpszStringw;
	wcin >> lpszStringw;
	lpszString = lpszStringw.c_str();
	COPYDATASTRUCT cds;
	cds.dwData = 1;
	cds.cbData = (lstrlen(lpszString) + 1) * sizeof(TCHAR);
	cout << cds.cbData << endl;
	cds.lpData = (PVOID)lpszString;
	
	LRESULT result = SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)(LPVOID)&cds);
	cout << result;

	return 0;
}