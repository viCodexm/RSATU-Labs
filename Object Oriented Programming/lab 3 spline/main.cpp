
#include <bits/stdc++.h>
#include "TKSpl.hpp"
#include "TLinSpl.hpp"

using namespace std;

int main() {
    
    string file_name = "input.o";
    fstream file(file_name);
    
    TDat dat;
    TLinSpl linspl;
    TKSpl tkspl;

    cout << "Tdat:\n"; dat.print_values();
    while (true) {
        cout << "\nВведите x: "; int x; cin >> x;
        cout << "Tdat: "; dat.print(x);
        cout << "TLinSpl: "; linspl.print(x);
        cout << "TKSpline: "; tkspl.print(x);
    }
    return 0;
}