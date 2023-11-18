#pragma once
#include <bits/stdc++.h>
#include "Human.hpp"

#define all(v)      v.begin(), v.end()

using namespace std;

class Student : public Human {
    string group_name;
    unsigned int group_number;
public:
    Student(string first_name, string middle_name, string last_name, string group_name, unsigned int group_number)
        : Human(first_name, middle_name, last_name), group_name(group_name), group_number(group_number)
    {
        for_each(all(group_name), [](char& c) {toupper(c);});
        if (not(1 <= group_number && group_number <= 5))
            cout << "Ошибка ввода курса!\n";
    };
    string get_group() {
        return group_name + " " + to_string(group_number);
    }
    virtual void rewrite(tuple<string, string, string, string, int> new_info) {
        tie(first_name, middle_name, last_name, group_name, group_number) = new_info;
    }
    string get_info() override {
        return "Student: " + Human::get_info() + " Group: " + get_group();
    }
};
