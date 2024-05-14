
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>

using namespace std;

int func_calls = 0;
const float eps = 0.0015;
const float gold = 0.381966; //2 - ((1 + 5**0.5) / 2);

float func(float x) {
    func_calls++;
    return sin(x) + x / 2;
    // return x * x - x * x * x * x + 7 * x;
    // return exp(x) - x - 2;
}

void find(float left, float right, float a, float b, float precalc_a, float precalc_b) {
    float mid = (right - left) / 2;
    if (mid <= eps) {
        printf("x = %f\ny = %f\nКолличество вызовов: %d\n", a, func(a), func_calls);
        return;
    }
    if (precalc_a <= precalc_b) {
        left = a;
        a = b;
        b = right - (right - left) * gold;
        precalc_a = precalc_b; precalc_b = func(b);
    }
    else {
        right = b;
        b = a;
        a = left + (right - left) * gold;
        precalc_b = precalc_a; precalc_a = func(a);
    }
    find(left, right, a, b, precalc_a, precalc_b);
}

void find(float left, float right, float a, float b) {
    float mid = (right - left) / 2;

    while (mid > eps) {
        mid = (right - left) / 2;
        float nextX1 = func(a), nextX2 = func(b);

        if (nextX1 <= nextX2) {
            left = a; a = b;
            b = right - (right - left) * gold;
        } else {
            right = b; b = a;
            a = left + (right - left) * gold;
        } 
    }
    printf("x = %f\ny = %f\nКолличество вызовов: %d\n", a, func(a), func_calls);
}

int main() {
    cout << "Введите левую и правую границы: ";
    float left, right; cin >> left >> right;

    float diff = right - left;
    float a = left + diff * gold;
    
    float frow = right - a;
    float take = diff - frow;
    int count = 1;
    while (frow > eps) {
        frow = take * gold;
        take -= frow;
        count++;
    }
    cout << count << "\n";

    float x1 = left + (right - left) * gold;
    float x2 = right - (right - left) * gold;

    float precalc_x1 = func(x1);
    float precalc_x2 = func(x2);

    find(left, right, x1, x2, precalc_x1, precalc_x2);
     
    // find(left, right, x1, x2);
    return 0;
}