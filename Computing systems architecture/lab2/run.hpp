#pragma once
#include <bits/stdc++.h>
#include "converter.hpp"

using namespace std;

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
    int a, b, c, code_type;
    char response;
    string ans;
    bool f1, f2;
p1:
    cout << "Введите границы диапазона A < B\n";
    f1 = int_input("A = ", a);
    f2 = int_input("B = ", b);

p2:
    if (!f1 || !f2 || !(a < b)) {
        cout << "\nОшибка ввода границ диапазона\n\n";
        goto p1;
    }

p3:
    cout << "Введите число C, принадлежащее заданному диапазону\n";

p4:
    if (!int_input("C = ", c) || !(a <= c && c <= b)) {
        cout << "\nОшибка ввода числа C\n\n";
        goto p3;
    }

p5:
    cout << "Введите номер вида кода:\n"
        << "1 Прямой код\n"
        << "2 Обратный код\n"
        << "3 Дополнительный код\n"
        << "4 Модифицированный дополнительный код\n";

p6:
    if (!int_input("Номер вида кода = ", code_type) || !(1 <= code_type && code_type <= 4)) {
        cout << "\nОшибка ввода номера вида кода\n\n";
        goto p5;
    }
    cout << "\n";

p7:
    switch (code_type)
    {
    case 1:
        cout << "Прямой код\n";
        check(to_straight_code(c));
        break;
    case 2:
        cout << "Обратный код\n";
        check(to_reverse_code(c));
        break;
    case 3:
        cout << "Дополнительный код\n";
        check(to_extended_code(c));
        break;
    case 4:
        cout << "Модифицированный дополнительный код\n";
        check(to_mod_extended_code(c));
        break;
    default:
        goto p5;
        break;
    }

p8:
    cout << "Изменить номер вида кода?\n";
    response = char_input("Y-да, N-нет\n");

p9:
    switch (response)
    {
    case 'Y':
        goto p5;
        break;
    case 'N':
        goto p10;
        break;
    default:
        cout << "\nОшибка запроса на изменение вида кода\n\n";
        goto p8;
        break;
    }

p10:
    cout << "Ввести новое число C?\n";
    response = char_input("Y-да, N-нет\n");

p11:
    switch (response)
    {
    case 'Y':
        goto p3;
        break;
    case 'N':
        goto p12;
        break;
    default:
        cout << "\nОшибка запроса на ввод нового числа\n\n";
        goto p10;
        break;
    }

p12:
    cout << "Завершить работу программы?\n";
    response = char_input("Y-да, N-нет\n");
    
p13:
    switch (response)
    {
    case 'Y':
        return 0;
    case 'N':
        goto p1;
        break;
    default:
        cout << "\nОшибка ввода запроса на завершение программы\n\n";
        goto p13;
        break;
    }
    return 0;
}