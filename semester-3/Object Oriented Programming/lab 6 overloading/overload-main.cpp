
#include <bits/stdc++.h>
#include "Matrix.hpp"


int main() {
    Matrix m1(2, 3); m1 = 1.0; m1.setValue(0, 1, 6);
    Matrix m2(2, 3); m2 = 2.0;
    m1.print("m1:");
    m2.print("m2:");
    try {
        Matrix m3 = m1 * m2;
        m3.print("m3:");
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}