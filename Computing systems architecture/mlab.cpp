
#include <bits/stdc++.h>

using namespace std;

int a, b, c, code_type;
char response;

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
        s[i]--;
        i--;
        if (s[i] == '.')
            break;
        s[i]++;
        carry = s[i] == '2';
    }
//    if (s[i] == '.')
//        s = "error";
    return s;
}
string to_mod_extended_code(int val) {
    string s = to_reverse_code(val);
    if (val >= 0) return '0' + s;

    int i = s.size() - 1;
    s[i]++;
    bool carry = s[i] == '2';
    while (carry) {
        s[i]--;
        i--;
        if (s[i] == '.')
            break;
        s[i]++;
        carry = s[i] == '2';
    }
    if (s[i] == '.') {
        return "10" + s.substr(1, s.size());
    }
    return '1' + s;
}

int main() {
    //cout << to_straight_code(-75) << "\n";
    //cout << to_reverse_code(-75) << "\n";
    //cout << to_extended_code(-75) << "\n";
    //cout << to_mod_extended_code(-75) << "\n";

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