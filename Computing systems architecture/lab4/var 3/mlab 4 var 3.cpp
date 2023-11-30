#include <bits/stdc++.h>
#include "converter.hpp"

using namespace std;

#define MINUS_ZERO_DOESNT_EXIST "Значения '-0' в данном коде не существует"

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
         << "ипB(10) = " << ipB10 << "\n";
         if (mB == "0,")
            cout << "mB = 0\n";
        else cout << "mB = " << mB << "\n";
        cout << "\n";

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
    if (hexA == "00000000" || hexB == "00000000") {
        cout << "R(2) = 0\nR(16) = 0\n";
        cin.ignore();
        goto p1;
    }

    cout << "\n3 A*B\n";
    char zR = ((binA[0] - '0') + (binB[0] - '0') == 1) ? '1' : '0';
    cout << "zR = zA (+) zB = "
    << binA[0] << " (+) " << binB[0]
    << " = " 
    << zR
    << "\n\n";
    

    string ipA = to_straight_code(ipA10, ipA10 < 0, false);
    string ipB = to_straight_code(ipB10, ipB10 < 0, false);
    make_same_size(ipA, ipB, 2);
    //int force_size = ipA.size();
    
    const int sw = 12;
    cout << "       ипА(2)              ипB(2)\n";
    cout << "ПК" << setw(sw) << ipA
     << setw(sw) << "    " << ipB << "\n";
    
    string revA = to_reverse_code(ipA10, ipA10 < 0, false), revB = to_reverse_code(ipB10, ipB10 < 0, false);
    make_same_size(revA, revB, 2);
    cout << "OК" << setw(sw) << revA << setw(sw) << "    " << revB << "\n";
    
    string extA = to_extended_code(ipA10, ipA10 < 0, false), extB = to_extended_code(ipB10, ipB10 < 0, false);
    make_same_size(extA, extB, 2);
    cout << "ДК" << setw(sw) << extA
    << setw(sw) << "    " << extB << "\n";

    string ipA_mdk = to_mod_extended_code(ipA10, ipA10 < 0, false);
    string ipB_mdk = to_mod_extended_code(ipB10, ipB10 < 0, false);
    make_same_size(ipA_mdk, ipB_mdk, 3);

    cout << "МДК" << setw(sw-1) << ipA_mdk << setw(sw-1) << "    " << ipB_mdk << "\n";
    cout << "\n";

    // сложение порядков
    string ipR_mdk = without_leading_zeroes(code_plus_code("0" + ipA_mdk, "0"+ipB_mdk));
    int ipR10 = ipA10 + ipB10;
    cout << "ипA(МДК) = " << ipA_mdk << "\n";
    cout << "ипB(МДК) = " << ipB_mdk << "\n";
    cout << "ипR(МДК) = " << ipR_mdk << "\n";
    string ipR2 = to_straight_code(ipR10, ipR10 < 0, 0).substr(2);
    ipR2 = without_leading_zeroes(ipR2);
    cout << "ипR(2) = " << ((ipR10 < 0) ? "-" : "") << (ipR2.empty() ? "0" : ipR2) << "\n"; // может быть и плюс и минус
    cout << "ипR(10) = " << ipR10 << "\n\n"; 
    
    
pOUT:
    // умножение
    const int ms = max(mA.size(), mB.size()) + mB.size() - 2;
    int size_diff = abs((int)mA.size() - (int)mB.size());
    // выравнивание
    if (mA.size() > mB.size()) {
        cout << "mA" << setw(ms + size_diff) << mA << "\n"
             << "mB" << setw(ms) << mB << "\n"
             << string(ms + 2 + size_diff, '-') << "\n";
    }
    else {
        int x = 1;
        cout << "mA" << setw(ms) << mA << "\n"
             << "mB" << setw(ms + size_diff) << mB << "\n"
             << string(ms + 2 + size_diff, '-') << "\n";
    }
    
    
    mA = mA.substr(2);
    mB = mB.substr(2);
    string output = "";
    int offset = 0;
    for (int i = mB.size() - 1; i >= 0; --i) {
        if (mB[i] == '1') {
            cout << setw(ms + 2 + size_diff - offset) << mA << "\n";
            string buf = '0' + mA + string(mB.size() - i - 1, '0');
            make_same_size(output, buf, 0);
            output = code_plus_code(output, buf);
        }
        else {
            string buf = "0" + output;
            make_same_size(output, buf, false);
        }
        offset++;
    }
    cout << string(ms + 2 + size_diff, '-') << "\n";
    cout << setw(ms + 2 + size_diff) << output << "\n\n";
    
    cout << "mR = " << "0," + output << "\n";
    
p7:
    // Если требуется нормализация, то выводим
    bool need_normalization = output[0] == '0';
    int leading_zeros = 0;
    while (leading_zeros < output.size() && output[leading_zeros] == '0')
        leading_zeros++;

    cout << "\n";
    if (need_normalization) // не учитывается сдвиг в другую сторону (нет примеров)
        cout << "mRн = " << "0," + output.substr(leading_zeros) << "\n"
            << "ипRн(10) = " << ipR10 + leading_zeros << "\n";

    int spR10 = ipR10 + 127 - leading_zeros; // leading_zeros - normalisation
    bitset<8> bst_spr(spR10);
    string spR2 = bst_spr.to_string();
    string R2 = zR + spR2 + output.substr(leading_zeros);
    int diff = 32 - R2.size();
    if (diff > 0)
        R2 += string(diff, '0');
    string R16 = bin_to_hex(R2);

    cout << "спR(10) = " << spR10 << "\n"
         << "спR(2) = " << spR2 << "\n"
         << "R(2) = " << space_wrapper(R2) << "\n"
         << "R(16) = " << space_wrapper(R16) << "\n";

p8:
    cout << "Изменить значения исходных чисел?\n";
    response = char_input("(Y - да / N - нет)\n");
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