#pragma once
#include "Human.hpp"
#include <bits/stdc++.h>

using namespace std;

struct People {

    vector<Human> people;
    People() {

    }
    People(fstream& file) {
        while (!file.eof()) {
            Human man(file);
            if (!man.empty())
                people.push_back(man);
        }
    }
    string get_fio(int i) {
        return people[i].get_fio(); 
    }
    Human* get_address(int i) {
        return &people[i];
    }
    int size() {
        return people.size();
    }
    void add(Human& human) {
        people.push_back(human);
    }
    Human read_human_via_console() {
        cout << "Âגוהטעו ÔÈÎ קונוח ןנמבוכû:\n";
        string first_name, middle_name, last_name;
        cin >> first_name >> middle_name >> last_name;

        Human man(first_name, middle_name, last_name);
        return man;
    }
    void add_via_console() {
        Human man = read_human_via_console();
        this->add(man);
    }
    void change(int idx) {
        Human man = read_human_via_console();
        people[idx] = man;
    }
    ~People() {
        
    }
};