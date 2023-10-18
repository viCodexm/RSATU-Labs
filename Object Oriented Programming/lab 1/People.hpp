#pragma once
#include "Human.hpp"
#include <bits/stdc++.h>

using namespace std;

struct People {
    vector<Human> people;
    People() {

    }
    People(fstream& file) {
        Human man(file);
        people.push_back(man);
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
    ~People() {
        //delete people;
    }
};