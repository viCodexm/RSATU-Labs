#pragma once
#include "Human.hpp"
#include <bits/stdc++.h>

using namespace std;

struct People {
    string file_name;
    vector<Human> people;

    /*People() {
        this->file_name = "input.txt";
        fstream file(file_name);
        while (!file.eof()) {
            Human man(file);
            if (!man.empty())
                people.push_back(man);
        }
        file.close();
    }*/

    People(string file_name) {
        this->file_name = file_name;
        fstream file(file_name);
        while (!file.eof()) {
            Human man(file);
            if (!man.empty())
                people.push_back(man);
        }
        file.close();
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
        cout << "������� ���:\n";
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
        if (0 <= idx && idx < people.size())
            people[idx] = man;
        else cout << "WRONG INDEX\n";
    }
    ~People() {
        ofstream ff(file_name);
        for (int i = 0; i < people.size(); ++i)
            people[i].write_to_file(ff);
        
        ff.close();
    }
};