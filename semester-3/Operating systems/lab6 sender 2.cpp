#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#pragma comment(lib, "user32.lib")

#define BUF_SIZE 256
TCHAR szName[] = TEXT("Global\\MyFileMappingObject");
TCHAR szEventName[] = TEXT("event name");

using namespace std;

int _tmain()
{
    setlocale(LC_ALL, "ru");
    HANDLE hMapFile;
    LPCTSTR pMem;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        szName);                 // name of mapping object

    if (hMapFile == NULL)
    {
        _tprintf(TEXT("Could not open file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }

    pMem = (LPTSTR)MapViewOfFile(hMapFile, // handle to map object
        FILE_MAP_ALL_ACCESS,  // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pMem == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile);

        return 1;
    }

    cout << "Введите сообщение:\n";
    string message; getline(cin, message);
    TCHAR szMsg[256];
    std::copy(message.begin(), message.end(), szMsg);
    szMsg[message.size()] = '\0';
    CopyMemory((PVOID)pMem, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
    
    HANDLE hEvent = CreateEvent(NULL, false, false, szEventName);
    if (!SetEvent(hEvent)) {
        _tprintf(TEXT("Could not set event (%d).\n"),
            GetLastError());

        return -1;
    }


    UnmapViewOfFile(pMem);

    CloseHandle(hMapFile);

    return 0;
}