#pragma once
#include <bits/stdc++.h>

using namespace std;

struct Human {
    string first_name, middle_name, last_name;
    // Олег Бозов Петрович

    Human(fstream& file) {
        file >> first_name >> middle_name >> last_name;
    }
    string get_fio() {
        return first_name + " " + middle_name + " " + last_name;
    }
    void rewrite(string& _first_name, string& _middle_name, string& _last_name) {
        first_name = _first_name;
        middle_name = _middle_name;
        last_name = _last_name;
    }
    void wrtie_to_file(fstream& file) {

    }
};