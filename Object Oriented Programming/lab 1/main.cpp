
#include <bits/stdc++.h>
#include "People.hpp"
#include "Human.hpp"

using namespace std;

int main() {
    fstream file;
    file.open("\\home\\dmitry\\local\\src\\vs code\\C++\\OOP\\lab\\input.txt");
    if (!file.is_open()) {
        cout << "THE HELL\n";
        return 0;
    }
    People guys(file);
    
    for (int i = 0; i < guys.size(); ++i)
        cout << guys.get_fio(i) << "\n";
    
    cout << "END\n\n";
    return 0;
}