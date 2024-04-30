
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>

using namespace std;

int func_calls = 0;
const float eps = 0.0015;
const float gold = 0.381966; //2 - ((1 + 5**0.5) / 2);

int func1(int x) {
    func_calls++;
    return x * x - x * x * x * x + 7 * x;
}

int func2(int x) {
    func_calls++;
    return exp(x) - x - 2;
}

void find(float left, float right, float x1, float x2, float precalc_x1, float precalc_x2) {
    float mid = (right - left) / 2;
    if (mid <= eps) {
        printf("x = %f\ny = %f\nКолличество вызовов: %d\n", x1, func1(x1), func_calls);
        return;
    }
    if (precalc_x1 <= precalc_x2) {
        left = x1;
        x1 = x2; precalc_x1 = precalc_x2;
        x2 = right - (right - left) * gold;
        precalc_x2 = func1(x2);
        find(left, right, x1, x2, precalc_x1, precalc_x2);
    }
    else {
        right = x2;
        x2 = x1; precalc_x2 = precalc_x1;
        x1 = left + (right - left) * gold;
        precalc_x1 = func1(x1);
        find(left, right, x1, x2, precalc_x1, precalc_x2);
    }
}

int main() {
    cout << "Введите левую и правую границы: ";
    float left, right; cin >> left >> right;

    float x1 = left + (right - left) * gold;
    float x2 = right - (right - left) * gold;

    float precalc_x1 = func1(x1);
    float precalc_x2 = func1(x2);

    find(left, right, x1, x2, precalc_x1, precalc_x2);
    return 0;
}