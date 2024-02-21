
#include <bits/stdc++.h>

using namespace std;

struct Owner { string fio; };
struct Engine { float volume; };
struct Wheel { float diameter; };

struct Automobile {
    Owner owner; Engine engine; vector<Wheel> wheels;
    virtual int count_info();
    virtual string owner_info();
};

struct PassengerCar : Automobile {
    int passengers;
    PassengerCar(string fio, int passengers) : passengers(passengers) { owner.fio = fio; }
    int count_info() override { return passengers; }
    string owner_info() override { return owner.fio; }
};

struct Truck : Automobile {
    float weight;
    Truck(string fio, float weight) : weight(weight) { owner.fio = fio; }
    int count_info() override { return weight; }
    string owner_info() override { return owner.fio; }
};

struct AutoQueue {
    vector<shared_ptr<Automobile>> q;

    void read_from_file(string filename) {
        fstream file(filename);
        while (!file.eof()) {
            char type; string fio; float data; file >> type >> fio >> data;
            (type == 'p') ? q.push_back(make_shared<PassengerCar>(fio, data, type))
                : q.push_back(make_shared<Truck>(fio, data, type));
        }
    }
    vector<string> get_fios() {
        vector<string> res;
        for (const auto& automobile : q)
            res.push_back(automobile->owner.fio);
        return res;
    }
};

int main() {
    AutoQueue aq;
    aq.read_from_file("input.txt");
    vector<string> fios = aq.get_fios();

    return 0;
}