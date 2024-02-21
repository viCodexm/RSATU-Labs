#pragma once
#include <bits/stdc++.h>

#define all(v)      v.begin(), v.end()

using namespace std;

struct Human {
    string first_name, middle_name, last_name;

    Human(string first_name, string middle_name, string last_name)
        : first_name(first_name), middle_name(middle_name), last_name(last_name) {};

    Human(fstream& file) {
        file >> first_name >> middle_name >> last_name;
    }
    virtual string get_info() {
        transform(all(first_name), first_name.begin(), ::toupper);
        transform(all(middle_name), middle_name.begin(), ::tolower);
        transform(all(last_name), last_name.begin(), ::tolower);

        return first_name + " " + middle_name + " " + last_name;
    }
    virtual void rewrite(tuple<string, string, string> new_name) {
        tie(first_name, middle_name, last_name) = new_name;
    }
    void write_to_file(ofstream& file) {
        file << get_info() << "\n";
    }
    bool empty() {
        return first_name.empty() || middle_name.empty() || last_name.empty();
    }
};
