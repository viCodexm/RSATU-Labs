#pragma once
#include <bits/stdc++.h>
#include "converter.hpp"

using namespace std;

int run() {
    int a, b, c, code_type;
    char response;
p1:
    cout << "Введите границы диапазона A < B\n";
    cout << "A = "; cin >> a;
    cout << "B = "; cin >> b;

p2:
    if (!(a < b)) {
        cout << "\nОшибка ввода границ диапазона\n\n";
        goto p1;
    }

p3:
    cout << "Введите число C, принадлежащее заданному диапазону\n";
    cout << "C = "; cin >> c; cout << "\n";

p4:
    if (!(a <= c && c <= b)) {
        cout << "Ошибка ввода числа C\n\n";
        goto p3;
    }

p5:
    cout << "Введите номер вида кода:\n"
        << "1 Прямой код\n"
        << "2 Обратный код\n"
        << "3 Дополнительный код\n"
        << "4 Модифицированный дополнительный код\n"
        << "Номер вида кода = "; cin >> code_type;

p6:
    if (!(1 <= code_type && code_type <= 4)) {
        cout << "\nОшибка ввода номера вида кода\n\n";
        goto p5;
    }
    cout << "\n";

p7:
    switch (code_type)
    {
    case 1:
        cout << "Прямой код\n"
            << "C = " << to_straight_code(c) << endl;
        break;
    case 2:
        cout << "Обратный код\n"
            << "C = " << to_reverse_code(c) << endl;
        break;
    case 3:
        cout << "Дополнительный код\n"
            << "C = " << to_extended_code(c) << endl;
        break;
    case 4:
        cout << "Модифицированный дополнительный код\n"
            << "C = " << to_mod_extended_code(c) << endl;
        break;
    default:
        goto p5;
        break;
    }

p8:
    cout << "Изменить номер вида кода?\n"
        << "Y-да, N-нет\n";
    cin >> response;

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
    cout << "Ввести новое число C?\n"
        << "Y-да, N-нет\n";
    cin >> response;

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
    cout << "Завершить работу программы?\n"
        << "Y-да, N-нет\n";
    cin >> response;

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