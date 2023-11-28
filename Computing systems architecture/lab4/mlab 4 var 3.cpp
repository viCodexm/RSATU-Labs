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
string dec_to_bin(int decimal) {
    bitset<32> bst(decimal);
    string binStr = bst.to_string();
    
    int idx = 0;
    while (idx < binStr.size() && binStr[idx] == '0')
        idx++;
    
    return binStr.substr(idx, binStr.size() - idx);
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
    int ipA10 = bin_to_dec(binA.substr(1, 8)) - 127;
    int ipB10 = bin_to_dec(binB.substr(1, 8)) - 127;
    string mA = get_matisse(binA);
    string mB = get_matisse(binB);
    // внимательно смотреть лишние нули
    cout << "\n"
         << "A(2) = " << space_wrapper(binA) << "\n"
         << "zA = " << binA[0] << "\n"
         << "спА(2) = " << space_wrapper(binA.substr(1, 8)) << "\n"
         << "спА(10) = " << bin_to_dec(binA.substr(1, 8)) << "\n"
         << "ипА(10) = " << ipA10 << "\n"
         << "mA = " << mA << "\n"
         << "\n"
         << "B(2) = " << space_wrapper(binB) << "\n"
         << "zB = " << binB[0] << "\n"
         << "спB(2) = " << space_wrapper(binB.substr(1, 8)) << "\n"
         << "спB(10) = " << bin_to_dec(binB.substr(1, 8)) << "\n"
         << "ипB(10) = " << ipB10 << "\n"
         << "mB = " << mB << "\n"
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

    cout << "\n3 A*B\n";
    char zR = ((binA[0] - '0') + (binB[0] - '0') == 1) ? '1' : '0';
    cout << "zR = zA (+) zB = "
    << binA[0] << " (+) " << binB[0]
    << " = " 
    << zR
    << "\n\n";
    

    string ipA = dec_to_bin(bin_to_dec(binA.substr(1, 8)) - 127);
    string ipB = dec_to_bin(bin_to_dec(binB.substr(1, 8)) - 127);
    make_same_size_leading_zero(ipA, ipB);
    int force_size = ipA.size();
    
    const int sw = 12;
    cout << "       ипА(2)              ипB(2)\n";
    cout << "ПК" << setw(sw) << to_straight_code(ipA10, ipA10 < 0, force_size)
     << setw(sw) << "    " << to_straight_code(ipB10, ipB10 < 0, force_size) << "\n";
    
    cout << "OК" << setw(sw) << to_reverse_code(ipA10, ipA10 < 0, force_size)
    << setw(sw) << "    " << to_reverse_code(ipB10, ipB10 < 0, force_size) << "\n";
    
    cout << "ДК" << setw(sw) << to_extended_code(ipA10, ipA10 < 0, force_size)
    << setw(sw) << "    " << to_extended_code(ipB10, ipB10 < 0, force_size) << "\n";

    string ipA_mdk = to_mod_extended_code(ipA10, ipA10 < 0, force_size);
    string ipB_mdk = to_mod_extended_code(ipB10, ipB10 < 0, force_size);

    cout << "МДК" << setw(sw-1) << ipA_mdk << setw(sw-1) << "    " << ipB_mdk << "\n";
    cout << "\n";

    // сложение порядков
    string ipR_mdk = code_plus_code(ipA_mdk, ipB_mdk);
    int ipR10 = ipA10 + ipB10;
    cout << "ипA(МДК) = " << ipA_mdk << "\n";
    cout << "ипB(МДК) = " << ipB_mdk << "\n";
    cout << "ипR(МДК) = " << ipR_mdk << "\n";
    cout << "ипR(2) = " << ((ipR10 < 0) ? "-" : "") << to_straight_code(ipR10, ipR10 < 0, 0).substr(2) << "\n"; // может быть и плюс и минус
    cout << "ипR(10) = " << ipR10 << "\n\n"; 
    
    
pOUT:
    // умножение
    const int ms = mA.size();//max(mA.size(), mB.size());
    cout << "mA" << setw(2 * ms - 4) << mA << "\n"
         << "mB" << setw(2 * ms - 4) << mB << "\n"
         << string(2 * ms - 2, '-') << "\n";
    
    mA = mA.substr(2);
    mB = mB.substr(2);
    string output = "";
    for (int i = mB.size() - 1; i >= 0; --i) {
        if (mB[i] == '1') {
            cout << setw(ms + i) << mA << "\n";
            string buf = mA + string(mB.size() - i - 1, '0');
            make_same_size_leading_zero(output, buf);
            output = code_plus_code(output, buf);
        }
        else cout << setw(ms + i) << string(mA.size(), '0') << "\n";
    }
    cout << string(2 * ms - 1, '-') << "\n";
    cout << "  " << output << "\n\n";
    int leading_zeros = 0;
    while (leading_zeros < output.size() && output[leading_zeros] == '0')
        leading_zeros++;
    cout << "mR = " << "0," + output.substr(leading_zeros) << "\n";
p6:
    
    string R2 = zR +/*спR +*/ output.substr(leading_zeros);
p7:
    // Если требуется нормализация, то выводим
    cout << "\n";
    cout << "mRн = " << "\n"
         << "ипRн(10) = " << "\n"
         << "спR(10) = " << "\n"
         << "спR(2) = " << "\n"
         << "R(2) = " << "\n"
         << "R(16) = " << bin_to_hex(R2) << "\n";

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