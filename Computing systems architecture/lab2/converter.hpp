#pragma once
#include <bits/stdc++.h>

using namespace std;

string to_straight_code(int val, bool negative) {
    if (val == 0)
        return negative ? "1.0" : "0.0";

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
string to_reverse_code(int val, bool negative) {
    if (val == 0 && negative)
        return "Значения '-0' в данном коде не существует";
    
    string s = to_straight_code(val, negative);
    if (val >= 0)
        return s;

    for (int i = 2; i < s.size(); ++i)
        if (s[i] == '1')
            s[i] = '0';
        else if (s[i] == '0')
            s[i] = '1';
    return s;
}
string to_extended_code(int val, bool negative) {
    if (val == 0 && negative)
        return "Значения '-0' в данном коде не существует";

    string s = to_reverse_code(val, negative);
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
string to_mod_extended_code(int val, bool negative) {
    if (val == 0 && negative)
        return "Значения '-0' в данном коде не существует";

    string s = to_extended_code(val, negative);
    if (val >= 0) return '0' + s;
    return '1' + s;
}

int binary_to_int(string code) {
    int sign = (code[0] == '1' || code[1] == '1') ? -1 : 1;
    reverse(code.begin(), code.end());
    const int size = code.size();
    int ans = 0;
    for (int i = 0; i < size && code[i] != '.'; ++i)
        if (code[i] == '1')
            ans += pow(2, i);
    
    return sign * ans;
}


void make_same_size(string& a, string& b, int prefix_length) {
    int asize = a.size(), bsize = b.size();
    const int diff = abs(asize - bsize);

    if (asize < bsize)
        a = a.substr(0, prefix_length) + string(diff, '0') + a.substr(prefix_length, asize - 1);
    else if (asize > bsize)
        b = b.substr(0, prefix_length) + string(diff, '0') + b.substr(prefix_length, bsize - 1);
}

string mod_ex_add(int ai, int bi) {
    //int sign = ((a[0] == '1' && b[0] != '1') || (a[0] != '1' && b[0] == '1')) ? -1 : 1;
    
    string a = to_mod_extended_code(ai, ai < 0);
    string b = to_mod_extended_code(bi, bi < 0);

    a = a.substr(0, 3) + '0' + a.substr(3, a.size() - 2);
    b = b.substr(0, 3) + '0' + b.substr(3, b.size() - 2);

    make_same_size(a, b, 3);

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
    if (a[2] == '0')
        return a.substr(0, 2) + a.substr(3, a.size() - 1);
    return a;
}
/**/