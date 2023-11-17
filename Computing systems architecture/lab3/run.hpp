#pragma once
#include <bits/stdc++.h>
#include "converter.hpp"

using namespace std;

#define MINUS_ZERO_DOESNT_EXIST "Значения '-0' в данном коде не существует"

int _stoi(string str, int* p_value) {
    try {
        *p_value = stoi(str);
        return 0;
    }
    catch (exception& e) {
        return -1;
    }
    return 0;
}

bool int_input(string message, int& ans) {
    bool f = false;
    cout << message;
    if (cin >> ans)
        f = true;
    else {
        cin.clear();
        cin.ignore();
    }
    return f;
}
char char_input(string message) {
    bool f = false;
    char ans = 0;
    while (!f) {
        cout << message;
        if (cin >> ans)
            f = true;
        else {
            cout << "Ошибка ввода\n";
            cin.clear();
            cin.ignore();
        }
    }
    cin.clear();
    cin.ignore();
    return toupper(ans);
}
void check(string code) {
    if (code == MINUS_ZERO_DOESNT_EXIST)
        cout << code << "\n";
    else cout << "C = " << code << "\n";
}

int run() {

p1:
    int a, b, m, code_type, i_ans;
    char response;
    string stra, strb, str_ans, R;
    bool f1, f2;

    cout << "Введите два целых числа (A < B)\n";
    cout << "A = "; getline(cin, stra);
    cout << "B = "; getline(cin, strb);
    
p2:
    if (_stoi(stra, &a) != 0 || _stoi(strb, &b) != 0 || a >= b)  {
        cout << "\nОшибка ввода исходных чисел\n\n";
        goto p1;
    }
    
p3:
    cout << "Введите номер способа деления:\n"
         << "1 C восстановлением и сдвигом остатка\n"
         << "2 C восстановлением остатка и сдвигом делителя\n" 
         << "3 Без восстановления, но со сдвигом остатка\n"
         << "4 Без восстановления, но со сдвигом делителя\n";

p4:
    if (!int_input("M = ", m) || m < 1 || 4 < m) {
        cout << "\nОшибка ввода номера способа деления\n\n";
        goto p3;
    }
    if (m != 1) {
        cout << "\nCпособ деления не реализован\n\n";
        goto p3;
    }

p5: 
    // CHECK THIS SHIT: 0/any, any/0, 0/0;
    
    
    cout << "Деление с восстановлением остатка и сдвигом делителя\n";
    bitset<16> bits_a(abs(a)); bitset<16> bits_b(abs(b));
    stra = bits_a.to_string(); strb = bits_b.to_string();
    int cut = min(stra.find_first_of('1'), strb.find_first_of('1'));

    stra = stra.substr(cut); strb = strb.substr(cut);
    // SHOULD I MAKE OUTPUT LIKE THIS?
    
    string MDK_B = code_add_one(code_reverse(strb)); // REMEMBER IT DOESNT HAVE "11." or "00."
    cout << "A = " << stra << "\n";
    cout << "B = " << strb << "\n\n";
    cout << setw(12) << "|B|" << setw(16) << "-|B|\n";
    cout << "МПК   00."+strb << "    " << "11."+strb << "\n";
    cout << "МОК   00."+strb << "    " << "11."+code_reverse(strb) << "\n";
    cout << "МДК   00."+strb << "    " << "11." + MDK_B << "\n\n";

    string up = "00."+stra, down = "11."+MDK_B, res;
pOUT:
    cout << up << "\n";
    cout << down << "\n";
    cout << string(stra.size() + 3, '-') << "\n";

    res = code_plus_code(up, down);
    cout << res << ((res[0] == '0') ? "   > 0" : "   < 0") << "\n";

    // > 0
    if (res[0] == '0') {
        up = mdk_code_move_left(res);
        cout << up << "   <---\n";
    }
    // < 0
    else {
        cout << up << "   Во\n";
        up = mdk_code_move_left(up);
        cout << up << "   <---\n";
    }
    R += (res[0] == '0') ? '1' : '0';
    cout << "R = " << R[0] << '.' << R.substr(1) << "\n";
    if (R.size() == up.size() - 1) // is that so?
        goto p7;

p6:
    cout << "Продолжить деление?\n";
    response = char_input("(Y - да / N - нет)\n");

    switch (response)
    {
    case 'Y':
        goto pOUT; // 
    case 'N':
        goto p7; // CAREFUL
    default:
        cout << "Ошибка ввода запроса на продолжение деления\n";
        goto p6;
    }

p7:
    cout << "zR = zA (+) zB = " << ((a*b < 0) ? "-1" : "1") << " => R " << ((a*b < 0) ? "< 0" : "> 0") << "\n"; // is that so?
    while (R.size() > 1 && R[R.size() - 1] == '0')
        R.pop_back();
    cout << "R(2) = " << ((a*b < 0) ? "-" : "+") << R[0] << '.' << R.substr(1) << "\n"; // is that so?
    
    cout << "R(10) = ";
    double _res = 0;
    for (int i = 0; i < R.size(); ++i) {
        if (R[i] == '1')
            _res += (1 / pow(2, i));
    }
    cout << (double)_res << "\n";

p8:
    cout << "Изменить значения исходных чисел?\n";
    response = char_input("(Y - да / N - нет)\n");
    //string buf;
    //getline(cin, buf);
    //cin.clear();
    switch (response)
    {
    case 'Y':
        goto p1;
    case 'N':
        break;
    default:
        cout << "Ошибка ввода запроса на изменение исходных чисел\n";
        goto p8;
    }
    return 0;
}