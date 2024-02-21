#pragma warning (disable : 4996)
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>

#define BUF_SIZE 256
TCHAR szName[] = TEXT("Global\\MyFileMappingObject");
TCHAR szMsg[] = TEXT("Message from first process.");
TCHAR szEventName[] = TEXT("event name");

using namespace std;

int _tmain()
{
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
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }
    pMem = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
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
    HANDLE hEvent = CreateEvent(NULL, false, false, szEventName);
    WaitForSingleObject(hEvent, INFINITE);

    
    for (int i = 0; i < BUF_SIZE; ++i)
        cout << (CHAR)*(pMem + i);

    UnmapViewOfFile(pMem);

    CloseHandle(hMapFile);

    return 0;
}