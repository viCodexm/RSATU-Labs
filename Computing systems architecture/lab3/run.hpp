#pragma once
#include <bits/stdc++.h>
#include "converter.hpp"

using namespace std;

#define A_minus_B   2
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
    int a, b, m, code_type, i_ans;
    char response;
    string stra, strb, str_ans, r2;
    bool f1, f2;
p1:
    cout << "Введите два целых числа (A < B)\n";
    cout << "A = "; getline(cin, stra);
    cout << "B = "; getline(cin, strb);
    
p2:
    if (_stoi(stra, &a) != 0 || _stoi(strb, &b) != 0)  {
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
    if (m != A_minus_B) {
        cout << "\nCпособ деления не реализован\n\n";
        goto p3;
    }

p5:
    if (stra == "-0")
        stra = MINUS_ZERO_DOESNT_EXIST;
    else stra = to_straight_code(a, a < 0, 0);

    if (strb == "-0")
        strb = MINUS_ZERO_DOESNT_EXIST;
    else strb = to_straight_code(-b, -b < 0, 0);

    int size = 0;
    if (stra != MINUS_ZERO_DOESNT_EXIST && strb != MINUS_ZERO_DOESNT_EXIST) {
        //make_same_size(stra, strb, 3);
        size = max(stra.size(), strb.size());
        stra = to_mod_extended_code(a, a < 0, size);
        strb = to_mod_extended_code(-b, -b < 0, size);
    }
    
    
    //str_ans = mod_ex_add(a, b);
    i_ans = a - b;//binary_to_int(str_ans);
    r2 = to_straight_code(i_ans, i_ans < 0, 0);
    string body = r2.substr(2, r2.size() - 1);
    while (body.size() > 2 && body[0] == '0')
        body.erase(0, 1);

    if (r2[0] == '1')
        r2 = '-' + body;
    else r2 = body;

    cout << "\nA-B\n"
        << stra << "\n"
        << strb << "\n"
        << string(strb.size(), '-') << "\n"
        <<  to_mod_extended_code(i_ans, i_ans < 0, size) << "\n"
        
        << "R(ОК) = " << to_reverse_code(i_ans, i_ans < 0, size) << "\n"
        << "R(ПК) = " << to_straight_code(i_ans, i_ans < 0, size) << "\n"
        //<< "R(ДК) = " << to_extended_code(i_ans, i_ans < 0) << "\n"
        //<< "МДК = " << to_mod_extended_code(i_ans, i_ans < 0) << "\n"
        << "R(2) = " << r2 << "\n"
        << "R(10) = " << i_ans << "\n";

p6:
    cout << "Изменить номер выполняемой операции?\n";
    response = char_input("(Y - да / N - нет)\n");

    switch (response)
    {
    case 'Y':
        goto p3;
    case 'N':
        goto p7;
    default:
        cout << "Ошибка запросов на повоторный ввод номера операции\n";
        goto p6;
    }

p7:
    cout << "Ввести новое значение заданных чисел?\n";
    response = char_input("(Y - да / N - нет)\n");
    string buf;
    //getline(cin, buf);
    //cin.clear();
    switch (response)
    {
    case 'Y':
        goto p1;
    case 'N':
        break;
    default:
        cout << "Ошибка запросов на ввод новых заданных чисел\n";
        goto p7;
    }
    return 0;
}