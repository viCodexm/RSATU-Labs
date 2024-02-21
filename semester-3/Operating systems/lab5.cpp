#pragma warning (disable : 4996)

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <io.h>

using namespace std;

int main() {
	
    cout << "Input path to directory:\n";
    char dir[200];
    scanf("%s", &dir);
    strcat(dir, "*.*");

    struct _finddata_t c_file;
    intptr_t hFile;

    if ((hFile = _findfirst(dir, &c_file)) == -1L)
        printf("No files in current directory!\n");
    else
    {
        printf("*.* files:\n\n");
        printf("RDO HID SYS ARC NORMAL SUBDIR FILE NAME    %25c SIZE\n", ' ');
        printf("--- --- --- --- ------ ------ ---------    %25c ----\n", ' ');
        _findnext(hFile, &c_file); // to skip '.' file
        do {
            
            printf((c_file.attrib & _A_RDONLY) ? " Y  " : " N  ");
            printf((c_file.attrib & _A_HIDDEN) ? " Y  " : " N  ");
            printf((c_file.attrib & _A_SYSTEM) ? " Y  " : " N  ");
            printf((c_file.attrib & _A_ARCH) ? " Y   " : " N   ");
            printf((c_file.attrib & _A_NORMAL) ? " Y     " : " N     ");
            printf((c_file.attrib & _A_SUBDIR) ? " Y   " : " N   ");
            printf(" %-30s  %9ld\n",
                c_file.name, c_file.size);
        } while (_findnext(hFile, &c_file) == 0);
        _findclose(hFile);
    }
	return 0;
}