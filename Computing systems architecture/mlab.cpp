
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

void test_add(int a, int b) {
    string _a = to_straight_code(a);
    string _b = to_straight_code(b);
    make_same_size(_a, _b);
    string _ab = mod_ex_add(a, b);
    const int sw = 16;
    cout << setw(sw) << _a << "\n"
         << setw(sw) << "+\n"
         << setw(sw) << _b << "\n"
         << setw(sw) << "=\n";
    cout << setw(sw) << _ab << "\n";

    cout << "Answer: " << binary_to_int(_ab);
}

int main() {
    /*
    test(-75);
    test(-77);
    test(-64);
    test(33);
    
    test_add(14, 75);
    /**/
    
    return run();
}