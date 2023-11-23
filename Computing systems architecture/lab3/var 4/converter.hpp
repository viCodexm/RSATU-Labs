#pragma once
#include <bits/stdc++.h>

using namespace std;

#define MINUS_ZERO_DOESNT_EXIST "Значения '-0' в данном коде не существует"

string code_reverse(string code) {

    for (int i = 0; i < code.size(); ++i)
        (code[i] == '1') ? code[i] = '0' : code[i] = '1';

    return code;
}
string code_add_one(string code) {
    int i = code.size() - 1;
    code[i]++;
    bool carry = code[i] == '2';
    while (carry) {
        code[i] -= 2;
        i--;
        code[i]++;
        carry = code[i] == '2';
    }
    return code;
}
string code_plus_code(string a, string b) {
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; --i) {
        if (a[i] == '.')
            continue;
        
        int count = ((a[i] == '1') + (b[i] == '1')) + min(1, carry);

        switch (count) {
        case 0:
            break;
        case 1:
            if (carry)
                carry = false;
            a[i] = '1';
            break;
        case 2:
            carry = true;
            a[i] = '0';
            break;
        case 3:
            carry = true;
            a[i] = '1';
            break;
        }
    }
    return (carry) ? "00" + a.substr(2) : a;
}

string mdk_code_move_right(string code, char add_left) {
    return code.substr(0, 3) + add_left + code.substr(3, code.size() - 4);
}
