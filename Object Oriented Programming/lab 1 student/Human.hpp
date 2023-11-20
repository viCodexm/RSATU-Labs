#pragma once
#include <bits/stdc++.h>

using namespace std;

struct Human {
    string first_name, middle_name, last_name;

    Human(string first_name, string middle_name, string last_name)
        : first_name(first_name), middle_name(middle_name), last_name(last_name) {};

    Human(fstream& file) {
        file >> first_name >> middle_name >> last_name;
    }
    string get_fio() {
        for (char& c : first_name)
            c = toupper(c);
        for (char& c : middle_name)
            c = tolower(c);
        for (char& c : last_name)
            c = tolower(c);

        return first_name + " " + middle_name + " " + last_name;
    }
    void rewrite(string _first_name, string _middle_name, string _last_name) {
        first_name = _first_name;
        middle_name = _middle_name;
        last_name = _last_name;
    }
    void write_to_file(ofstream& file) {
        string fio = get_fio();
        file << fio << "\n";
    }
    bool empty() {
        return first_name == "" || middle_name == "" || last_name == "";
    }
};