
#include <bits/stdc++.h>

using namespace std;

struct Command {
    struct Key {
        char current_state, current_symbol;

        bool operator<(const Key& other) const {
            if (current_state == other.current_state)
                return current_symbol < other.current_symbol;
            return current_state < other.current_state;
        }
    };
    struct Value {
        char next_state, new_symbol;
    };
    Key key; Value value;

    bool read() {
        return cin >> key.current_state && cin >> key.current_symbol && cin >> value.next_state && cin >> value.new_symbol;
    }
};

struct TuringTape {
    string tape;
    char current_state = '0';

    void trim() {
        tape.erase(begin(tape),
            find_if_not(begin(tape), end(tape),
            [](char c) { return c == '0'; }));
    }
    void read() { cin >> tape; }

    void print() {
        if (tape.back() != '#') tape.push_back('#');
        cout << tape << "   состояние: " << current_state << "\n";
    }

    void move_cycle_left() {
        tape = tape.substr(1, tape.size()) + tape[0];
    }
    void set_state(char state) { current_state = state; }

    void handle_command(Command::Value command, char& current_symbol) {
        current_symbol = command.new_symbol;
        set_state(command.next_state);
    }
};

int main() {
    freopen("Turing-table.txt", "r", stdin);
    TuringTape turing; turing.read();
    map<Command::Key, Command::Value> table;
    
    for (Command cmd; cmd.read();)
        table[cmd.key] = cmd.value;
    
    turing.print();
    for (char& current_symbol : turing.tape) {
        Command::Key key = { turing.current_state, current_symbol };
        auto it = table.find(key);
        if (it == table.end()) {
            cout << "Команда не найдена!\nКоманда: состояние " << key.current_state << " символ " << key.current_symbol << "\n";
            return -1;
        }
        Command::Value value = it->second;
        turing.handle_command(value, current_symbol);
        turing.print();
    }

    return 0;
}