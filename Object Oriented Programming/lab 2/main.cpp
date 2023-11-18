
#include <bits/stdc++.h>
#include "People.hpp"
#include "Human.hpp"

using namespace std;

int main() {
    
    string file_name = "input.o";
    cout << "Ввести имя файла? (y - да / n - нет) (по умолчанию input.o)\n";
    char response; cin >> response;

    if (tolower(response) == 'y')
        cin >> file_name;

    People guys("input.o");
    
    cout << "-----содержимое файла:-----\n";
    for (int i = 0; i < guys.size(); ++i)
        cout << guys.get_fio(i) << "\n";

    response = (char)NULL;
    while (response != 'n') {
        cout << "добавить или изменить информацию о человеке? (y - добавить нового / e - изменить / n - завершить работу программы)\n";
        cin >> response;
        if (tolower(response) == 'y') {
            guys.add_via_console();
        }
        else if (tolower(response) == 'e') {
            cout << "введите номер изменяемого человка (0-индексация):\n";
            int num; cin >> num;
            guys.change(num);
        }
    }
    return 0;
}