#pragma once
#include <bits/stdc++.h>

using namespace std;

string to_straight_code(int val) {
    if (val == -0)
        return "1.0";
    string s;
    int n = abs(val);
    while (n > 0) {
        s += to_string(n % 2);
        n /= 2;
    }
    if (val >= 0)
        s += ".0";
    else s += ".1";

    reverse(s.begin(), s.end());
    return s;
}
string to_reverse_code(int val) {
    if (val == -0)
        return "Значения '-0' в данном коде не существует";
    
    string s = to_straight_code(val);
    if (val >= 0)
        return s;

    for (int i = 2; i < s.size(); ++i)
        if (s[i] == '1')
            s[i] = '0';
        else if (s[i] == '0')
            s[i] = '1';
    return s;
}
string to_extended_code(int val) {
    if (val == -0)
        return "Значения '-0' в данном коде не существует";

    string s = to_reverse_code(val);
    if (val >= 0)
        return s;

    int i = s.size() - 1;
    s[i]++;
    bool carry = s[i] == '2';
    while (carry) {
        s[i] -= 2;
        i--;
        if (s[i] == '.')
            break;
        s[i]++;
        carry = s[i] == '2';
    }
    return s;
}
string to_mod_extended_code(int val) {
    if (val == -0)
        return "Значения '-0' в данном коде не существует";

    string s = to_extended_code(val);
    if (val >= 0) return '0' + s;
    return '1' + s;
}

int binary_to_int(string code) {
    int sign = (code[0] == '1') ? -1 : 1;
    reverse(code.begin(), code.end());
    const int size = code.size();
    int ans = 0;
    for (int i = 0; i < size && code[i] != '.'; ++i)
        if (code[i] == '1')
            ans += pow(2, i);
    
    return sign * ans;
}

// still in development

void make_same_size(string& a, string& b) {
    while (a.size() < b.size())
        a.push_back('0');
    while (b.size() < a.size())
        b.push_back('0');
}

string mod_ex_add(int ai, int bi) {
    //int sign = ((a[0] == '1' && b[0] != '1') || (a[0] != '1' && b[0] == '1')) ? -1 : 1;
    
    string _a = to_straight_code(ai);
    string _b = to_straight_code(bi);

    string a = _a.substr(0, 3) + '0' + _a.substr(3, _a.size() - 3);
    string b = _b.substr(0, 3) + '0' + _b.substr(3, _b.size() - 3);

    make_same_size(a, b);

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
    return a;
}
/**/