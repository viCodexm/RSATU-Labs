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
    // ипА < ипБ ?
    // сдвиг мантиссы -> результат меняется (?)
pOPERATION:

    cout << "\n2 A-B\n";
    string zA = to_string(binA[0] - '0');
    string zB = to_string(binB[0] - '0');

    string zR = "";
    
    if (binA > binB) { // из большего вычитаем меньшее
        if (zA == "1")
            zR = "1";
        else zR = "0";
    } else { // из меньшего большее вычитаем (складываем)
        if (zB == "1") // минус отрицательное == плюс положительное
            zR = "0"; 
        else zR = "1";
    }

        
    cout << "zR = zA (+) zB = "
    << zA << " (+) " << zB
    << " = " 
    << zR // (?)
    << "\n\n";
    if (zB == "0")
        zB = "1";
    else zB = "0";

    
    const int sw = 12;
    int m_size = 1 + max(mA.size(), mB.size());
    if (ipA10 < ipB10) { // надеюсь это правильно
        mA = mA.substr(0, 2)+string(m_size - mA.size(), '0') + mA.substr(2);
        mB += string(m_size - mB.size(), '0');
    } else {
        make_same_size(mA, mB, 2);
    }
    

    //int mA10 = bin_to_dec(mA);
    //int mB10 = bin_to_dec(mB);
        
    
    // если знак 0, то все опреации игнорируются и выводится просто mA(mB)
    // ((zB == "1") ? ... : ___ означает: если знак отрицательный делай это ? ... иначе делай это : ___
    cout << "       А              -B\n";
    cout << "ПК" << setw(sw) << zA+"."+mA << setw(sw) << zB+"."+mB << "\n";
    cout << "OК" << setw(sw) << zA+"."+((zA == "1") ? code_reverse(mA) : mA) << setw(sw) << zB+"."+((zB == "1") ? code_reverse(mB) : mB) << "\n";
    cout << "ДК" << setw(sw) << zA+"."+((zA == "1") ? code_add_one(code_reverse(mA)) : mA) << setw(sw) << zB+"."+((zB == "1") ? code_add_one(code_reverse(mB)) : mB) << "\n";
    cout << "МДК" << setw(sw-1) << zA+zA+"."+((zA == "1") ? code_add_one(code_reverse(mA)) : mA) << setw(sw-1) << zB+zB+"."+((zB == "1") ? code_add_one(code_reverse(mB)): mB) << "\n";
    cout << "\n";

pOUT:
    // вычитание
    string mdkA = zA+zA+"."+((zA == "1") ? code_add_one(code_reverse(mA)) : mA);
    string mdkB = zB+zB+"."+((zB == "1") ? code_add_one(code_reverse(mB)) : mB);
    string mdkR = code_plus_code("0"+mdkA, "0"+mdkB);
    cout << "A  " << setw(sw) << mdkA << "\n";
    cout << "B  " << setw(sw) << mdkB << "\n";
    cout << string(sw + m_size, '-') << "\n";
    cout << setw(3 + sw) << mdkR << "\n";

    // теперь если результат отрицательный - разворачиваем его обратно мдк->ок->пк->двоичка
    string mR = mdkR.substr(4, mdkR.size() - 4);
    if (mdkR[0] == '1') { // (?)
        cout << "R(МДК) = " << mdkR.substr(1) << "\n";
        cout << "R(ДК) = " << mdkR.substr(2) << "\n";
        mR = code_minus_one(mR);
        cout << "R(ОК) = " << zR+"."+mR << "\n";
        mR = code_reverse(mR);
        cout << "R(ПК) = " << zR+"."+mR << "\n";
    }
    cout << "\n";
    
    // нормализация (надеюсь тут сдвиг может быть только на один)
    int normalisation = 0;
    if (mR[0] == '1') {
        swap(mR[0], mR[1]); // поменяли запятую с единицей местами
        mR = "0" + mR;
        normalisation++;
    }
    
    int spR10 = max(ipA10, ipB10) + 127 + normalisation;
    string spR2 = without_leading_zeroes(to_straight_code(spR10, spR10 < 0, 8).substr(2));
    if (spR2.empty())
        spR2 = "0";
        
    cout << "спR(2) = " << space_wrapper(spR2) << "\n";
    cout << "спR(10) = " << spR10 << "\n";



    string R2 = zR + spR2 + mR.substr(2);
    int diff = 32 - R2.size();
    if (diff > 0)
        R2 += string(diff, '0');

    cout << "R(2) = " << space_wrapper(R2) << "\n";
    cout << "R(16) = " << space_wrapper(bin_to_hex(R2)) << "\n";

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