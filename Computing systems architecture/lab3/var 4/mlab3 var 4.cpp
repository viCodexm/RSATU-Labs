
#include <bits/stdc++.h>
#include "converter.hpp"

using namespace std;

#define MINUS_ZERO_DOESNT_EXIST "Значения '-0' в данном коде не существует"
const string SPACING = "        ";

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

int main() {

p1:
    //string test = "00.01101";
    //cout << test << "\n" << (test = mdk_code_move_right(test)) << "\n";
    //cout << (test = mdk_code_move_right(test)) << "\n" << (test = mdk_code_move_right(test)) << "\n" << (test = mdk_code_move_right(test)) << "\n";
    
    int a, b, m, code_type, i_ans;
    char response;
    string stra, strb, str_ans, R;
    vector<string> output;
    bool f1, f2;

    cout << "Введите два целых числа (A < B)\n";
    cout << "A = "; getline(cin, stra);
    cout << "B = "; getline(cin, strb);
    
p2:
    if (strb == "0" || strb == "-0") {
        cout << "\nДеление на ноль невозможно!\n";
        goto p1;
    }
    if (_stoi(stra, &a) != 0 || _stoi(strb, &b) != 0 || abs(a) >= abs(b))  {
        cout << "\nОшибка ввода исходных чисел\n\n";
        goto p1;
    }
    
p3:
    cout << "Введите номер способа деления:\n"
         << "1 C восстановлением и сдвигом остатка\n"
         << "2 C восстановлением остатка и сдвигом делителя\n" 
         << "3 Без восстановления остатка со сдвигом остатка\n"
         << "4 Без восстановления остатка со сдвигом делителя\n";

p4:
    if (!int_input("M = ", m) || m < 1 || 4 < m) {
        cout << "\nОшибка ввода номера способа деления\n\n";
        goto p3;
    }
    if (m != 4) {
        cout << "\nCпособ деления не реализован\n\n";
        goto p3;
    }

p5: 
    // CHECK THIS SHIT: 0/any, any/0, 0/0;
    
    
    cout << "4 Без восстановления остатка со сдвигом делителя\n";
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

    string MPK_FULL = "00."+strb; MPK_FULL = mdk_code_move_right(MPK_FULL, '0');
    string MDK_FULL = "11."+MDK_B; MDK_FULL = mdk_code_move_right(MDK_FULL, '1');
    string up = "00."+stra, down = "11."+MDK_B, res;
pOUT:
    if (output.empty())
        output.push_back(up + SPACING + MPK_FULL + " МПК");

    if (res.empty())
        output.push_back(down + SPACING + MDK_FULL + " МДК");
    else if (res[0] == '0')
        output.push_back(down + "   МДК  " + MDK_FULL + " МДК");
    else output.push_back(down + "   МПК  " + MDK_FULL + " МДК");

    output.push_back(string((stra.size() + 3) * 2 + SPACING.size() + 4, '-'));


    res = code_plus_code(up, down);
    output.push_back((res + ((res[0] == '0') ? "   > 0" : "   < 0") + "  " + mdk_code_move_right(MPK_FULL, '0') + " МПК"));

    cout << "\n";
    for (string& s : output)
        cout << s << "\n";

    // > 0
    up = res;
    if (res[0] == '0') { // бля, надеюсь прокатит. какая же ёбань.
        down = MDK_FULL;
        MPK_FULL = mdk_code_move_right(MPK_FULL, '0');
        MDK_FULL = mdk_code_move_right(MDK_FULL, '1');
    }
    // < 0
    else {
        down = MPK_FULL;
        MPK_FULL = mdk_code_move_right(MPK_FULL, '0');
        MDK_FULL = mdk_code_move_right(MDK_FULL, '1');
        
    }
    R += (res[0] == '0') ? '1' : '0';
    cout << "R = " << R[0] << ',' << R.substr(1) << "\n";
    
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
    return 0;
}