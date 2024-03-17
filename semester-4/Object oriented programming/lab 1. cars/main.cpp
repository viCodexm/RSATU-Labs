
#include <bits/stdc++.h>

using namespace std;

struct Owner {
    string fio;
    Owner() : fio("") {};
    Owner(string fio) : fio(fio) {};
};
struct Engine {
    float volume;
    Engine() : volume(0.0f) {};
    Engine(float volume) : volume(volume) {};
};
struct Wheel {
    float diameter;
    Wheel() : diameter(0.0f) {};
    Wheel(float diameter) : diameter(diameter) {};
};

struct Automobile {
    Owner* owner;
    Engine* engine;
    vector<Wheel*> wheels;

    Automobile(Owner* owner, float volume, int countWheels, float diameterWheels) {
        this->owner = owner;
        engine = new Engine(volume);
        for (int i =  0; i < countWheels; ++i)
            wheels.push_back(new Wheel(diameterWheels));
    }

    virtual ~Automobile() {
        delete engine;
        for (auto& wheel : wheels)
            delete wheel;
    }
    virtual int count_info() = 0;
    virtual string owner_info() = 0;    
};

struct PassengerCar : Automobile {
    int passengers;
    PassengerCar(Owner* owner, float volume, int countWheels, float diameterWheels, int passengers) : Automobile(owner, volume, countWheels, diameterWheels), passengers(passengers) {}
    int count_info() override { return passengers; }
    string owner_info() override { return owner->fio; }
};

struct Truck : Automobile {
    float weight;
    Truck(Owner* owner, float volume, int countWheels, float diameterWheels, float weight) : Automobile(owner, volume, countWheels, diameterWheels), weight(weight) {}
    int count_info() override { return weight; }
    string owner_info() override { return owner->fio; }
};

struct AutoQueue {
    vector<shared_ptr<Automobile>> q;

    void read_from_file(string filename) {
        fstream file(filename);
        while (!file.eof()) {
            char type; string name; float volume, diameterWheels; int countWheels;
            file >> type >> name >> volume >> countWheels >> diameterWheels;
            Owner* owner = new Owner(name);
            if (type == 'p') {
                int passengers; file >> passengers;
                q.push_back(make_shared<PassengerCar>(owner, volume, countWheels, diameterWheels, passengers));
            } else if (type == 't') {
                float weight; file >> weight;
                q.push_back(make_shared<Truck>(owner, volume, countWheels, diameterWheels, weight));
            }
        }
    }
    pair<int, int> get_info() {
        int passengers = 0; float weight = 0;
        for (const auto& automobile : q) {
            float data = automobile->count_info();

            if (dynamic_pointer_cast<PassengerCar>(automobile))
                passengers += data;
            else weight += data;
        }
        return {passengers, weight};
    }
    vector<string> get_fios() {
        vector<string> res;
        for (const auto& automobile : q)
            res.push_back(automobile->owner->fio);
        return res;
    }
    ~AutoQueue() {}
};

int main() {
    AutoQueue aq;
    aq.read_from_file("input.txt");
    vector<string> names = aq.get_fios();
    
    cout << "Имена владельцев машин:\n";
    for (string& str : names)
        cout << str << "\n";
    return 0;
}