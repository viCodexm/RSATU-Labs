#pragma warning (disable : 4996)
#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	OSVERSIONINFO osver;
	ZeroMemory(&osver, sizeof(OSVERSIONINFO));
	osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osver);

	cout << "Major Version: " << osver.dwMajorVersion << "\n"
		<< "Minor Version: " << osver.dwMinorVersion << "\n"
		<< "BUILD: " << osver.dwBuildNumber << "\n";
	
	OSVERSIONINFOEX info;
	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((LPOSVERSIONINFOW)&info);

	cout << "\ninfo.wSuiteMask value: " << info.wSuiteMask;
	cout << "\nWindows Server 2003, Wev edition ";
	info.wSuiteMask & VER_SUITE_BLADE ?  cout << "is installed" : cout << "is not installed";

	cout << "\nWindows Server 2003, Compute Eluster edition ";
	info.wSuiteMask & VER_SUITE_COMPUTE_SERVER ? cout << "is installed" : cout << "is not installed";

	cout << "\nWindows XP Embedded ";
	info.wSuiteMask & VER_SUITE_EMBEDDEDNT ? cout << "is installed" : cout << "is not installed";

	cout << "\nMicrosoft BackOffice components ";
	info.wSuiteMask & VER_SUITE_BACKOFFICE ? cout << "are installed" : cout << "are not installed";

	cout << "\nRemote Desktop ";
	info.wSuiteMask & VER_SUITE_SINGLEUSERTS ? cout << "is supported" : cout << "is not supported";

	cout << "\n\n";
	return 0;
}