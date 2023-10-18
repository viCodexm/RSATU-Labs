#pragma once
#include <bits/stdc++.h>

using namespace std;

string to_straight_code(int val) {
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
/*
string mod_ex_add(string a, string b) {
    //int sign = ((a[0] == '1' && b[0] != '1') || (a[0] != '1' && b[0] == '1')) ? -1 : 1;


    while (a.size() < b.size())
        a.push_back('0');
    while (b.size() < a.size())
        b.push_back('0');

    for (int i = a.size() - 1; i >= 2; i--)
        if (a[i])
}
*/