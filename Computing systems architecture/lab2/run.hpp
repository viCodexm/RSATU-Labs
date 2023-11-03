#pragma once
#include <bits/stdc++.h>
#include "converter.hpp"

using namespace std;

#define A_minus_B   2

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
    return ans;
}
void check(string code) {
    if (code == "Значения '-0' в данном коде не существует")
        cout << code << "\n";
    else cout << "C = " << code << "\n";
}

int run() {
    int a, b, m, code_type, i_ans;
    char response;
    string stra, strb, str_ans;
    bool f1, f2;
p1:
    cout << "Введите два целых числа\n";
    f1 = int_input("A = ", a);
    f2 = int_input("B = ", b);

p2:
    if (!f1 || !f2) {
        cout << "\nОшибка ввода чисел\n\n";
        goto p1;
    }

p3:
    cout << "Введите номер вида выполняемой операции (M):\n"
         << "1 A+B\n2 A-B\n3 -A+B\n4 -A-B\n";

p4:
    if (!int_input("M = ", m) || m < 1 || 4 < m) {
        cout << "\nОшибка ввода номера выполняемой операции\n\n";
        goto p3;
    }
    if (m != A_minus_B) {
        cout << "\nОперация " << m << " не реализована\n\n";
        goto p3;
    }

p5:
    stra = to_mod_extended_code(a, a < 0);
    strb = to_mod_extended_code(b, b < 0);
    make_same_size(stra, strb, 3);
    //str_ans = mod_ex_add(a, b);
    i_ans = a - b;//binary_to_int(str_ans);
    cout << "\nA-B\n"
        << "A = " << stra << "\n"
        << "B = " << strb << "\n"
        << string(4 + strb.size(), '-') << "\n"
        << "результат:\n"
        << "ПК = " << to_straight_code(i_ans, i_ans < 0) << "\n"
        << "ОК = " << to_reverse_code(i_ans, i_ans < 0) << "\n"
        << "ДК = " << to_extended_code(i_ans, i_ans < 0) << "\n"
        << "МДК = " << to_mod_extended_code(i_ans, i_ans < 0) << "\n"
        << "R(2) = " << to_straight_code(i_ans, i_ans < 0) << "\n" // **** what should be here?
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