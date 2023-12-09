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
// assume that a.size == b.size
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
string mdk_code_move_left(string code) {
    code += '0'; swap(code[2], code[3]);
    return code.substr(1);
}

void make_same_size(string& a, string& b, int prefix_length) {
    int asize = a.size(), bsize = b.size();
    const int diff = abs(asize - bsize);
    if (asize < bsize)
        a = a.substr(0, prefix_length) + string(diff, '0') + a.substr(prefix_length, asize);
    else if (asize > bsize)
        b = b.substr(0, prefix_length) + string(diff, '0') + b.substr(prefix_length, bsize);
}



// код из второй лабы
#define MINUS_ZERO_DOESNT_EXIST "Значения '-0' в данном коде не существует"

// val, "val < 0", force_any_size (0 - dont)
string to_straight_code(int val, bool negative, int body_size) {
    if (val == 0)
        return negative ? "1.0" : "0.0";

    string s;
    int n = abs(val);
    while (n > 0) {
        s += to_string(n % 2);
        n /= 2;
    }
    reverse(s.begin(), s.end());

    if (s.size() >= body_size) {
        return (val >= 0) ? "0." + s : "1.0" + s;
    }
    else {
        int add = body_size - s.size();
        return (val >= 0) ? "0." + string(add, '0') + s : "1." + string(add, '0') + s;
    }

    return s;
}
string to_reverse_code(int val, bool negative, int body_size) {
    if (val == 0 && negative)
        return MINUS_ZERO_DOESNT_EXIST;
    
    string s = to_straight_code(val, negative, body_size);
    if (val >= 0)
        return s;

    for (int i = 2; i < s.size(); ++i)
        if (s[i] == '1')
            s[i] = '0';
        else if (s[i] == '0')
            s[i] = '1';
    return s;
}
string to_extended_code(int val, bool negative, int body_size) {
    if (val == 0 && negative)
        return MINUS_ZERO_DOESNT_EXIST;

    string s = to_reverse_code(val, negative, body_size);
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
string to_mod_extended_code(int val, bool negative, int body_size) {
    if (val == 0 && negative)
        return MINUS_ZERO_DOESNT_EXIST;

    string s = to_extended_code(val, negative, body_size);
    
    if (val >= 0) return "00." + s.substr(2, s.size() - 1);
    return "11." + s.substr(2, s.size() - 1);
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

// separates every 4 chars in string with space
string space_wrapper(string output) {
    string str;
    int idx = 0;
    for (char& c : output) {
        if (idx == 4) {
            idx = 0;
            str += " ";
        }
        str += c;
        idx++;
    }
    return str;
}

bool isHex(string str) {
    if (str.size() != 8)
        return false;
    for (char& c : str)
        if (not(('A' <= c && c <= 'F') || isdigit(c)))
            return false;
    return true;
}
string hex_to_bin(string hexStr) {
    map<char, string> hexMap = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
    };

    string binStr = "";
    for (char c : hexStr)
        binStr += hexMap[c];

    return binStr;
}
string bin_to_hex(string binStr) {
    map<string, char> binMap = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
        {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
        {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}
    };
    string hexStr = "";
    for (int i = 0; i < binStr.size() - 3; i += 4)
        hexStr += binMap[binStr.substr(i, 4)];
    return hexStr;
}
int bin_to_dec(string binStr) {
    int decimal = 0;
    const int size = binStr.size();
    for (int i = 0; i < size; ++i) {
        if (binStr[i] == '1')
            decimal += pow(2, size - i - 1);
    }
    return decimal;
}

string get_matisse(string binStr) {
    string mantisse = "0," + binStr.substr(9, 32);
    while (!mantisse.empty() && mantisse[mantisse.size() - 1] == '0')
        mantisse.pop_back();
    return mantisse;
}
string without_leading_zeroes(string str) {
    int leading_zeros = 0;
    while (leading_zeros < str.size() && str[leading_zeros] == '0')
        leading_zeros++;
    return str.substr(leading_zeros);
} 