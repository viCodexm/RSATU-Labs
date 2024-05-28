
#include <bits/stdc++.h>

using namespace std;

void HanoiRec(int n, char source, char destination, char auxiliary) {
    if (!n) return;
    HanoiRec(n - 1, source, auxiliary, destination);
    cout << source << " -> " << destination << endl;
    HanoiRec(n - 1, auxiliary, destination, source);
}

char Symbol(char symbol, int rotation) {
    switch (symbol) {
        case 'A': return (rotation) ? 'B' : 'C';
        case 'B': return (rotation) ? 'C' : 'A';
        case 'C': return (rotation) ? 'A' : 'B';
    }
    return '.';
}

int Ostat(int step) {
    int res = 0;
    while (step & 1) {
        step >>= 1;
        res++;
    }
    return res;
}

template<typename T>
void print(vector<T>& mas) {
    for (int i = 0; i < mas.size(); i++) cout << mas[i] << " "; cout << "\n";
}


void HanoiIter(int n, char source, char destination, char auxiliary, vector<char>& outMas)
{
    outMas.clear();
    fill(outMas.begin(), outMas.end(), 'A');
    print(outMas);

    for (int curStep = 1; curStep != pow(2, n); ++curStep) {
    
        int res = (Ostat(curStep) & 1);
        bool rotate = n & 1 ? !(res) : (res);

        if (curStep & 1) outMas[0] = Symbol(outMas[0], n & 1);
        else outMas[Ostat(curStep)] = Symbol(outMas[Ostat(curStep)], rotate);

        print(outMas);
    }
}

int curStep;
bool flag = 0;

int findValue(vector<char>& mas, char value) {
    return *find(mas.begin(), mas.end(), value);
}


void SearchStep(int n, char source, char destination, char auxiliary, vector<char>& outMas, int step)
{
    if (flag || !n)
        return;

    SearchStep(n - 1, source, auxiliary, destination, outMas, step);
    
    int cur = findValue(outMas, source);
    outMas[cur] = destination;

    print(outMas);
    curStep++;

    if (step == curStep) {
        flag = 1;
        return;
    }
    SearchStep(n - 1, auxiliary, destination, source, outMas, step);
}


void BinaryHanoi(int n, char source, char destination, char auxiliary, int step) {
    stack<char> st;
    for (int curStep = n - 1; curStep > 0; --curStep) {

        if ((step >>= curStep) & 1)
            swap(source, destination);

        st.push(source);
        swap(destination, auxiliary);
    }

    while (!st.empty()) {
        char sym = st.top(); st.pop();
        cout << sym << " ";
    }
    cout << "\n";
}

int main() {
    setlocale(LC_ALL, "ru");
    cout << "1.Рекурсия\n2.Итерация\n3.Поиск любого хода\n4.Поиск введенного хода (при стандартном решении, рекурсия)\n5.Поиск введенного хода (бинарное решение)\n6.Выход";

    int n = 10, step;
    vector<char> outMas(n), searchMas(n);
    char start, aux;

    while (true) {
        cout << "\nВыберите действие: "; int action; cin >> action;

        switch (action) {
        case 1:
            HanoiRec(n, 'A', 'B', 'C');
            cout << endl;
            break;
        case 2:
            HanoiIter(n, 'A', 'B', 'C', outMas);
            cout << endl;
            break;
        case 3:
            cout << "Введите шаг: ";
            for (int i = 0; i < n; ++i)
                cin >> searchMas[i];

            fill(outMas.begin(), outMas.end(), 'A');
            print(outMas);

            start = 'A';
            aux = searchMas.back() == 'A' ? 'A' 
                : searchMas.back() == 'B' ? 'C'
                : 'B';

            step = pow(2, n) / 2;

            for (int index = n - 1; index > 0; --index) {

                if (searchMas[index] == start || searchMas[index] == outMas[index]) {
                    index--;
                    step >> 1;
                    continue;
                }

                // aux = (start == 'A') ? (val == 'B') ? 'C' : 'B' : (start == 'B') ? (val == 'A') ? 'C' : 'A' : (val == 'A') ? 'B' : 'A';

                if (start == 'A') {
                    if (searchMas[index] == 'B') aux = 'C';
                    if (searchMas[index] == 'C') aux = 'B';
                }
                if (start == 'B') {
                    if (searchMas[index] == 'A') aux = 'C';
                    if (searchMas[index] == 'C') aux = 'A';
                }
                if (start == 'C') {
                    if (searchMas[index] == 'A') aux = 'B';
                    if (searchMas[index] == 'B') aux = 'A';
                }


                curStep = flag = 0;
                SearchStep(index + 1, start, searchMas[index], aux, outMas, step);

                start = aux;
                step >>= 1;
            }
            break;

        case 4:
            cout << "Введите количество шагов: "; cin >> step;
            curStep = flag = 0;

            fill(outMas.begin(), outMas.end(), 'A');
            print(outMas);

            SearchStep(n, 'A', 'B', 'C', outMas, step);
            break;
        case 5:
            cout << "Введите ход: "; cin >> step;
            BinaryHanoi(n, 'A', 'B', 'C', step);
            break;
        case 6:
            return 0;
        }
    }
    return 0;
}
