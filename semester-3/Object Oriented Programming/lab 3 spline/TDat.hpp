
#pragma once
#include <bits/stdc++.h>

using namespace std;

class TDat {
public:
    map<double, double> coords;

    TDat() {
        read_from_file("input.o");
    }

    void read_from_file(string file_name) {
        fstream file(file_name);
        while (!file.eof()) {
            pair<double, double> p;
            file >> p.first >> p.second;
            coords[p.first] = p.second;
        }
        file.close();
    }
    virtual double get_y(double x) {
        if (coords.find(x) == coords.end()) {
            cout << "Ошибка, значения не существует";
            return -1;
        }
        return coords[x];
    }
    void print(int x) {
        if (get_y(x) != -1)
            cout << "x: " << x << " y: " << this->get_y(x) << "\n";
    }
    void print_values() {
        if (coords.empty())
            cout << "Список координат пуст!\n";
        
        for (auto& cord : coords)
            this->print(cord.first);
    }
};