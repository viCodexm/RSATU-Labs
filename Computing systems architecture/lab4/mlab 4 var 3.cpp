#include <bits/stdc++.h>
#include "converter.hpp"

using namespace std;

#define MINUS_ZERO_DOESNT_EXIST "Значения '-0' в данном коде не существует"

bool isHex(string str) {
    if (str.size() != 8)
        return false;
    for (char& c : str)
        if (not(('A' <= c && c <= 'Z') || isdigit(c)))
            return true;
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

int main() {
    // ипА = спА - 127
p1:
    int a, b, m, code_type, i_ans;
    char response;
    string hexA, hexB, str_ans, R;
    vector<string> output;
    bool f1, f2;

    cout << "Введите два вещественных шестнадцатеричных числа:\n";
    cout << "A = "; getline(cin, hexA);
    cout << "B = "; getline(cin, hexB);
    
p2:
    if (!isHex(hexA) || !isHex(hexB))  {
        cout << "\nОшибка ввода исходных чисел\n\n";
        goto p1;
    }
    if (hexA == "00000000" || hexB == "00000000") {
        cout << "R(2) = 0\nR(16) = 0\n";
        goto p1;
    }

pUnpacking:
    string binA = hex_to_bin(hexA), binB = hex_to_bin(hexB);
    
    // внимательно смотреть лишние нули
    cout << "\n"
         << "A(2) = " << binA << "\n"
         << "zA = " << binA[0] << "\n"
         << "спА(2) = " << binA.substr(1, 8) << "\n"
         << "спА(10) = " << bin_to_dec(binA.substr(1, 8)) << "\n"
         << "ипА(10) = " << bin_to_dec(binA.substr(1, 8)) - 127 << "\n"
         << "mA = " << get_matisse(binA) << "\n"
         << "\n"
         << "B(2) = " << binB << "\n"
         << "zB = " << binB[0] << "\n"
         << "спB(2) = " << binB.substr(1, 8) << "\n"
         << "спB(10) = " << bin_to_dec(binB.substr(1, 8)) << "\n"
         << "ипB(10) = " << bin_to_dec(binB.substr(1, 8)) - 127 << "\n"
         << "mB = " << get_matisse(binB) << "\n"
         << "\n";

p4:
    cout << "Введите номер выполняемой операции m:\n"
         << "1 A+B\n"
         << "2 A-B\n" 
         << "3 A*B\n"
         << "4 A/B\n";

p5:
    if (!int_input("m = ", m) || m < 1 || 4 < m) {
        cout << "\nОшибка ввода номера выполняемой операции\n\n";
        goto p4;
    }
    if (m != 3) {
        cout << "\nОперация не реализована\n\n";
        goto p4;
    }

pOPERATION:
    // "да да да, это не шутки" - (c) Сидоров
    // "а кто такая Соня Маремеладова? Сонечка, то? - прАстИтуткА" - (c) Сидоров
    // ""

    cout << "\n3 A*B\n";
    cout << "zR = zA (+) zB = "
    << binA[0] << " (+) " << binB[0]
    << " = " 
    << ((binA[0] - '0') + (binB[0] - '0') == 1)
    << "\n";
    
    cout << "     ипА(2)         ипB(2)\n";
    cout << "ПК  ";
    cout << "OК  ";
    cout << "ДК  ";
    cout << "МДК  ";
    cout << "\n";
    // какое-то сложение порядков
    // ...
    cout << "ипA(МДК) = ";
    cout << "ипB(МДК) = ";
    cout << "ипR(МДК) = ";
    cout << "ипR(2) = "; // может быть и плюс и минус
    cout << "ипR(10) = ";
    
    
pOUT:
    
    // "mA  "
    // "mB  "
    // "------"
    // "mR = "
    // запросов на продолжения деления не будет
p6:
    cout << "Продолжить деление?\n"; 
    response = char_input("(Y - да / N - нет)\n");

    switch (response)
    {
    case 'Y':
        goto pOUT;
    case 'N':
        goto p7;
    default:
        cout << "Ошибка ввода запроса на продолжение деления\n";
        goto p6;
    }

p7:
    // Если требуется нормализация, то выводим
    cout << "mRн = "
         << "ИПRн(10) = "
         << "СПR(10) = "
         << "СПR(2) = "
         << "R(2) = "
         << "R(16) = ";

    
    cout << "zR = zA (+) zB = "
    << ((a < 0) ? "1" : "0")
    << " (+) "
    << ((b < 0) ? "1" : "0")
    << " = "
    << ((a*b < 0) ? "1" : "0")
    << " => R " << ((a*b < 0) ? "< 0" : "> 0") << "\n";
    while (R.size() > 1 && R[R.size() - 1] == '0')
        R.pop_back();
    
    cout << "R(2) = " << ((a*b < 0) ? "-" : "") << R[0];
    if (!R.substr(1).empty())
        cout << '.' << R.substr(1);
    cout << "\n";

    cout << "R(10) = " << ((a*b < 0) ? "-" : "");
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
p9:
    cout << "Завершить работу программы?\n";
    response = char_input("(Y - да / N - нет)\n");
    switch (response)
    {
    case 'Y':
        break;
    case 'N':
        goto p1;
    default:
        cout << "Ошибка ввода запроса на завершение программы\n";
        goto p9;
    }
    return 0;
}