#pragma once
#include <bits/stdc++.h>
#include "Human.hpp"

#define all(v)      v.begin(), v.end()

using namespace std;

class Employee : public Human {
    string personnel_number;
public:
    Employee(string first_name, string middle_name, string last_name, string personnel_number)
        : Human(first_name, middle_name, last_name), personnel_number(personnel_number) {};
    
    string get_personnel_number() {
        return personnel_number;
    }
    virtual void rewrite(tuple<string, string, string, string> new_info) {
        tie(first_name, middle_name, last_name, personnel_number) = new_info;
    }
    string get_info() override {
        return "Employee: " + Human::get_info() + " Personnel number: " + get_personnel_number();
    }
};
