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
    if (m != 2) {
        cout << "\nОперация не реализована\n\n";
        goto p4;
    }

pOPERATION:

    cout << "\n2 A-B\n";
    string zA = to_string(binA[0] - '0');
    string zB = to_string(binB[0] - '0');

    string zR = (((binA[0] - '0') + (binB[0] - '0') == 1) ? "1" : "0");
    cout << "zR = zA (+) zB = "
    << zA << " (+) " << zB
    << " = " 
    << zR
    << "\n\n";
    

    
    const int sw = 12;
    make_same_size(mA, mB, 2);
    int mA10 = bin_to_dec(mA);
    if (binA[0] == '1')
        mA10 = -mA10;
    int mB10 = bin_to_dec(mB);
    if (binB[0] == '0')
        mB10 = -mB10;
    
    int force_size = mA.size() - 1;
    
    cout << "       А              -B\n";
    cout << "ПК" << setw(sw) << with_comma(to_straight_code(mA10, mA10 < 0, force_size))
         << setw(sw) << "    " << with_comma(to_straight_code(mB10, mB10 < 0, force_size)) << "\n";
    
    string revA = to_reverse_code(mA10, mA10 < 0, force_size), revB = to_reverse_code(mB10, mB10 < 0, force_size);
    make_same_size(revA, revB, 2);
    cout << "OК" << setw(sw) << with_comma(revA) << setw(sw) << "    " << with_comma(revB) << "\n";
    
    string extA = to_extended_code(mA10, mA10 < 0, force_size), extB = to_extended_code(mB10, mB10 < 0, force_size);
    make_same_size(extA, extB, 2);
    cout << "ДК" << setw(sw) << with_comma(extA)
    << setw(sw) << "    " << with_comma(extB) << "\n";

    string mA_mdk = to_mod_extended_code(mA10, mA10 < 0, force_size);
    string mB_mdk = to_mod_extended_code(mB10, mB10 < 0, force_size);
    make_same_size(mA_mdk, mB_mdk, 3);

    cout << "МДК" << setw(sw-1) << with_comma(mA_mdk) << setw(sw-1) << "    " << with_comma(mB_mdk) << "\n";
    cout << "\n";

pOUT:
    // вычитание
    const int ms = max(mA_mdk.size(), mB_mdk.size()) + mB_mdk.size();
    int size_diff = abs((int)mA_mdk.size() - (int)mB_mdk.size());
    // выравнивание
    if (mA_mdk.size() > mB_mdk.size()) {
        cout << "A " << setw(ms + size_diff) << mA_mdk << "\n"
             << "B " << setw(ms) << mB_mdk << "\n"
             << string(ms + 2 + size_diff, '-') << "\n";
    }
    else {
        int x = 1;
        cout << "A " << setw(ms) << mA_mdk << "\n"
             << "B " << setw(ms + size_diff) << mB_mdk << "\n"
             << string(ms + 2 + size_diff, '-') << "\n";
    }
    
    
    mA_mdk = mA_mdk.substr(2);
    mB_mdk = mB_mdk.substr(2);
    string output = zR+zR+"."+code_plus_code("0"+mA_mdk,mB_mdk+"0");
    int mR10 = bin_to_dec(output.substr(3));
    if (output[0] == '1')
        mR10 = -mR10;
    
    cout << setw(ms + 2 + size_diff) << with_comma(output) << "\n\n";
    
    
    cout << "mR = " << with_comma(output) << "\n";
    if (zR == "1") {
        cout << "R(МДК) = " << with_comma(to_mod_extended_code(mR10, mR10 < 0, force_size)) << "\n";
        cout << "R(ДК) = " << with_comma(to_extended_code(mR10, mR10 < 0, force_size)) << "\n";
        cout << "R(ОК) = " << with_comma(to_reverse_code(mR10, mR10 < 0, force_size)) << "\n";
        cout << "R(ПК) = " << with_comma(to_straight_code(mR10, mR10 < 0, force_size)) << "\n";
    }
    
    int spR10 = max(ipA10, ipB10) + 127;
    cout << "спR(2) = " << to_straight_code(spR10, spR10 < 0, force_size).substr(2) << "\n";
    cout << "спR(10) = " << spR10 << "\n";


    string mR = to_straight_code(mR10, mR10 < 0, force_size).substr(2);
    int leading_zeros = 0;
    while (leading_zeros < mR.size() && mR[leading_zeros] == '0')
        leading_zeros++;

    string R2 = zR + to_straight_code(spR10, spR10 < 0, force_size).substr(2) + mR.substr(leading_zeros);
    int diff = 32 - R2.size();
    if (diff > 0)
        R2 += string(diff, '0');

    cout << "R(2) = " << space_wrapper(R2) << "\n";
    cout << "R(16) = " << space_wrapper(bin_to_hex(R2)) << "\n";
    
p7:
    // Если требуется нормализация, то выводим
 /*   bool need_normalization = output[0] == '0';
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
*/
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