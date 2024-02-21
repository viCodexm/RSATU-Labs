
#include <bits/stdc++.h>
#include "run.hpp"

using namespace std;

void test(int i) {
    cout << setw(8) << i << "\n"
        << to_straight_code(i) << "\n"
        << to_reverse_code(i) << "\n"
        << to_extended_code(i) << "\n"
        << to_mod_extended_code(i) << "\n\n";

    cout << binary_to_int(to_straight_code(i)) << "\n\n\n";
}

int main() {
    
    return run();
}