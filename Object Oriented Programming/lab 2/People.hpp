#pragma once
#include <bits/stdc++.h>
#include "Human.hpp"
#include "Student.hpp"
#include "Employee.hpp"

using namespace std;

struct People {
    string file_name;
    vector<shared_ptr<Human>> people;

    People() {
        this->file_name = "input.txt";
        read_humans_from_file(this->file_name);
    }

    People(string file_name) {
        this->file_name = file_name;
        read_humans_from_file(this->file_name);
    }
    void read_humans_from_file(string file_name) {
        fstream file(file_name);
        while (!file.eof()) {
            string id; file >> id;
            if (id == "Student:") {
                string first_name, middle_name, last_name, group_name;
                unsigned int group_number;
                file >> first_name >> middle_name >> last_name >> id >> group_name >> group_number;
                people.push_back(make_shared<Student>(first_name, middle_name, last_name, group_name, group_number));
            } else if (id == "Employee:") {
                string first_name, middle_name, last_name, personnel_number;
                file >> first_name >> middle_name >> last_name >> id >> id >> personnel_number;
                people.push_back(make_shared<Employee>(first_name, middle_name, last_name, personnel_number));
            } else {
                string middle_name, last_name; file >> middle_name >> last_name;
                people.push_back(make_shared<Human>(id, middle_name, last_name));
            }
        }
        file.close();
    }

    string get_fio(int i) {
        return people[i].get()->get_info();
    }
    int size() {
        return people.size();
    }
    template <typename _T>
    void add(_T& somebody) {
        static_assert(is_base_of<Human, _T>::value, "T must be a subclass of Human");
        people.push_back(make_shared<_T>(somebody));
    }

    Student read_student_via_console() {
        cout << "введите фио, группу, номер группы:\n";
        string first_name, middle_name, last_name, group_name; int group_number;
        cin >> first_name >> middle_name >> last_name >> group_name >> group_number;

        return Student(first_name, middle_name, last_name, group_name, group_number);
    }
    Employee read_employee_via_console() {
        cout << "введите фио, номер табеля:\n";
        string first_name, middle_name, last_name, personnel_number;
        cin >> first_name >> middle_name >> last_name >> personnel_number;

        return Employee(first_name, middle_name, last_name, personnel_number);
    }
    Human read_human_via_console() {
        cout << "введите фио:\n";
        string first_name, middle_name, last_name;
        cin >> first_name >> middle_name >> last_name;

        return Human(first_name, middle_name, last_name);
    }
    
    void add_via_console() {
        cout << "Студент (S) / Работник (R) / Другой (D)\n";
        char response; cin >> response;
        if (response == 'S') {
            Student student = read_student_via_console();
            people.push_back(make_shared<Student>(student));
        } else if (response == 'R') {
            Employee employee = read_employee_via_console();
            people.push_back(make_shared<Employee>(employee));
        } else {
            Human man = read_human_via_console();
            people.push_back(make_shared<Human>(man));
        }
    }
    void change(int idx) {
        if (not(0 <= idx && idx < people.size())) {
            cout << "Неправильный индекс!\n";
            return;
        }
        const auto person = people[idx];
        if (auto student = dynamic_cast<Student*>(person.get()))
            *student = read_student_via_console();
        else if (auto employee = dynamic_cast<Employee*>(person.get()))
            *employee = read_employee_via_console();
        else if (auto somebody = dynamic_cast<Human*>(person.get()))
            *somebody = read_human_via_console();
    }
    ~People() {
        ofstream file(file_name);
        for (const auto person : people)
            person->write_to_file(file);
        
        file.close();
    }
};