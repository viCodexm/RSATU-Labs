
#include <bits/stdc++.h>
#include "People.hpp"
#include "Human.hpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    string file_name = "input.txt";
    cout << "Ввести имя файла? (y - да / n - нет) (по умолчанию input.txt)\n";
    char response; cin >> response;

    if (tolower(response) == 'y')
        cin >> file_name;

    fstream file;
    file.open(file_name);
    if (!file.is_open()) {
        cout << "File not found.\n";
        return 0;
    }
    People guys(file);
    
    cout << "-----Содержимое файла:-----\n";
    for (int i = 0; i < guys.size(); ++i)
        cout << guys.get_fio(i) << "\n";

    response = (char)NULL;
    while (response != 'n') {
        cout << "Добавить нового или изменить человека? (y - добавить нового / e - изменить / n - завершить работу программы)\n";
        cin >> response;
        if (tolower(response) == 'y') {
            guys.add_via_console();
        }
        else if (tolower(response) == 'e') {
            cout << "Введите номер изменяемого человека (0-индексация):\n";
            int num; cin >> num;
            guys.change(num);
        }
    }
    
    
    file.close();
    ofstream ff(file_name);
    if (!ff.is_open()) {
        cout << "FILE NOT OPEN!\n";
        return -1;
    }
    for (int i = 0; i < guys.people.size(); ++i) {
        string fio = guys.get_fio(i);
        ff << fio << "\n";
    }

    ff.close();
    return 0;
}