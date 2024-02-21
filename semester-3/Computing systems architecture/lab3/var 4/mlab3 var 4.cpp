#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <string>


using namespace std;

#define MINUS_ZERO_DOESNT_EXIST "Значения '-0' в данном коде не существует"

bool isValidNum(std::string temp) {

    if (temp.length() == 0)
        return false;

    for (int i = 0; i < temp.length(); i++)
        if (!(((temp[i] >= '0' && temp[i] <= '9') || (temp[0] == '-' && temp.length() > 1 && temp[i + 1] >= '0' && temp[i + 1] <= '9')) && temp.length() <= 9))
            return false;

    return true;
}

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

string mdk_code_move_right(string code, char add_left) {
    return code.substr(0, 3) + add_left + code.substr(3, code.size() - 4);
}

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
    setlocale(LC_ALL, "rus");

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
        cout << "\nДеление на ноль невозможно!\n\n";
        goto p1;
    }
    if (stra == "0") {
        cout << "\nzR = zA (+) zB = 0 (+) 0 = 0 => R > 0\n"
             << "R(2) = 0\nR(10) = 0\n\n";
        goto p1;
    }
    if (isValidNum(stra) && isValidNum(strb)) {
        a = stoi(stra); b = stoi(strb);
        if (abs(a) > abs(b)) {
            cout << "\nОшибка ввода исходных чисел\n\n";
            goto p1;
        }
    }
    else {
        cout << "\nОшибка ввода исходных чисел\n\n";
        goto p1;
    }
    


p3:

    cout << "\nВведите номер способа деления:\n"
        << "1 C восстановлением и сдвигом остатка\n"
        << "2 C восстановлением остатка и сдвигом делителя\n"
        << "3 Без восстановления остатка со сдвигом остатка\n"
        << "4 Без восстановления остатка со сдвигом делителя\n";

p4:
    if (!int_input("M = ", m) || m < 1 || 4 < m) {
        cout << "\nОшибка ввода номера способа деления\n\n";
        goto p3;
    }
    switch(m){
    case 1:
        cout << "\nCпособ деления c восстановлением и сдвигом остатка не реализован\n";
        goto p3;
    case 2:
        cout << "\nCпособ деления c восстановлением остатка и сдвигом делителя не реализован\n";
        goto p3;
    case 3:
        cout << "\nCпособ деления без восстановления остатка со сдвигом остатка не реализован\n";
        goto p3;
    }

p5:
    


    cout << "\nБез восстановления остатка со сдвигом делителя\n";
    bitset<16> bits_a(abs(a)); bitset<16> bits_b(abs(b));
    stra = bits_a.to_string(); strb = bits_b.to_string();
    int cut = min(stra.find_first_of('1'), strb.find_first_of('1'));

    stra = stra.substr(cut); strb = strb.substr(cut);
    // SHOULD I MAKE OUTPUT LIKE THIS?

    string MDK_B = code_add_one(code_reverse(strb)); // REMEMBER IT DOESNT HAVE "11." or "00."
    
    cout << setw(stra.length() / 2 + 9) << "|B|" << setw(strb.length() / 2 + stra.length() / 2 + 8) << "-|B|" << setw(strb.length() / 2 + stra.length() + 5) << "|A|\n";
    cout << "МПК   00." + strb << "    " << "11." + strb << "    " << "00." + stra << "\n";
    cout << "МОК   00." + strb << "    " << "11." + code_reverse(strb) << "    " << "00." + stra << "\n";
    cout << "МДК   00." + strb << "    " << "11." + MDK_B << "    " << "00." + stra << "\n\n";

    string MPK_FULL = "00." + strb; MPK_FULL = mdk_code_move_right(MPK_FULL, '0');
    string MDK_FULL = "11." + MDK_B; MDK_FULL = mdk_code_move_right(MDK_FULL, '1');
    string up = "00." + stra, down = "11." + MDK_B, res;

pOUT:
    if (output.empty())
        output.push_back(up + SPACING + MPK_FULL + " МПК ->");

    if (res.empty())
        output.push_back(down + SPACING + MDK_FULL + " МДК ->");
    else if (res[0] == '0')
        output.push_back(down + "   МДК  " + MDK_FULL + " МДК ->");
    else output.push_back(down + "   МПК  " + MDK_FULL + " МДК ->");

    output.push_back(string((stra.size() + 3) * 2 + SPACING.size() + 4, '-'));


    res = code_plus_code(up, down);
    output.push_back((res + ((res[0] == '0') ? "   > 0" : "   < 0") + "  " + mdk_code_move_right(MPK_FULL, '0') + " МПК ->"));

    cout << "\n";
    for (int i = 0; i < output.size()-1; i++)
        cout << output[i] << "\n";
    cout << output[output.size() - 1].substr(0, output[output.size()-1].size() / 2 ) << endl;
    // > 0
    up = res;
    if (res[0] == '0') { 
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
    

    if (R.size() == up.size() - 1) // is that so?
        goto p7;

    cout << "R = " << R[0] << '.' << R.substr(1) << "\n";

p6:
    cout << "\nПродолжить деление?\n";
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
    bool none_flag = false;
    if (R.length() == 1) {
        none_flag = true;
        cout << "\n|R| = " << R[0] << endl;
    }
    
    else 
        if (R.length() < strb.length()) {

            cout << "\n|R| = " << R[0] << '.' << R.substr(1, R.length() - 2) << R.substr(R.length() - 1) << "\n";
            R.erase(R.length() - 1, 1);
            if (R.length() == 1) {
                none_flag = true;
                cout << "|R| = " << R << "\n";
            }
            else
                cout << "|R| = " << R[0] << '.' << R.substr(1) << "\n";
        }

        else {
            cout << "\n|R| = " << R[0] << '.' << R.substr(1, R.length() - 2) << ';' << R.substr(R.length() - 1) << "\n";
            R.erase(R.length() - 1, 1);
            cout << "|R| = " << R[0] << '.' << R.substr(1) << "\n";

        }

    cout << "zR = zA (+) zB = "
        << ((a < 0) ? "1" : "0")
        << " (+) "
        << ((b < 0) ? "1" : "0")
        << " = "
        << ((a * b < 0) ? "1" : "0")
        << " => R " << ((a * b < 0) ? "< 0" : "> 0") << "\n";
    while (R.size() > 1 && R[R.size() - 1] == '0')
        R.pop_back();

    cout << "R(2) = " << ((a * b < 0) ? "-" : "") << R[0];
    if (!R.substr(1).empty())
        cout << ',' << R.substr(1);
    cout << "\n";

    cout << "R(10) = " << ((a * b < 0) ? "-" : "");
    double _res = 0;
    for (int i = 0; i < R.size(); ++i) {
        if (R[i] == '1')
            _res += (1 / pow(2, i));
    }
    string string_res = to_string((double)_res);
    string_res.erase(1, 1);
    string_res.insert(1, ",");

    for (int i = string_res.length() - 1; i > 0; i--)
        if (string_res[i] == '0') 
            string_res.pop_back();
        else
            break;

    if (none_flag)
        cout << string_res[0] << "\n";
    else
        cout << string_res << endl;
    
p8:
    cout << "\nВвести новые значение исходных чисел?\n";
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
        cout << "\nОшибка ввода запроса на изменение исходных чисел\n";
        goto p8;
    }
p9:
    cout << "Завершить работу\n";
    response = char_input("(Y - да / N - нет)\n");
    //string buf;
    //getline(cin, buf);
    //cin.clear();
    switch (response)
    {
    case 'Y':
        return 0;
    case 'N':
        goto p1;
        break;
    default:
        cout << "\nОшибка ввода запроса на завершение работы программы\n";
        goto p9;
    }
}