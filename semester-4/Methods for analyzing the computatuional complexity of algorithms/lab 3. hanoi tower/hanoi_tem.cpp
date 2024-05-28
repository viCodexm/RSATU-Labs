#include <bits/stdc++.h>

using namespace std;

void HanoiRec(int n, char source, char destination, char auxiliary)
{
    if (n >= 1)
    {
        HanoiRec(n - 1, source, auxiliary, destination);
        cout << source << " -> " << destination << endl;
        HanoiRec(n - 1, auxiliary, destination, source);
    }
}

char Symbol(char symbol, int rotation)
{
    if (rotation)
    {
        switch (symbol)
        {
        case 'A': return 'B';
        case 'B': return 'C';
        case 'C': return 'A';
        }
    }
    else
    {
        switch (symbol)
        {
        case 'A': return 'C';
        case 'B': return 'A';
        case 'C': return 'B';
        }
    }

}

int Ostat(int step)
{
    int step_ = step;
    int res = 0;
    while (!(step_ % 2))
    {
        step_ = step_ / 2;
        res++;
    }
    return res;
}


void HanoiIter(int n, char source, char destination, char auxiliary, vector<char>& outMas)
{
    outMas.clear();

    for (int i = 0; i < n; i++)
    {
        outMas.push_back('A');
    }

    for (int i = 0; i < outMas.size(); i++) cout << outMas[i] << ' ';
    cout << endl;

    int curStep = 1;
    bool rotate;
    while (curStep != pow(2, n))
    {
        if (n % 2)
        {
            rotate = !(Ostat(curStep) % 2);
        }
        else  rotate = (Ostat(curStep) % 2);

        if (curStep % 2) outMas[0] = Symbol(outMas[0], n % 2);
        else outMas[Ostat(curStep)] = Symbol(outMas[Ostat(curStep)], rotate);

        for (int i = 0; i < outMas.size(); i++) cout << outMas[i] << ' ';
        cout << endl;
        curStep++;
    }
}

int curStep;
bool flag = 0;

int findValue(vector<char>& mas, char value)
{
    auto result = find(mas.begin(), mas.end(), value);
    return (result - mas.begin());
}


void SearchStep(int n, char source, char destination, char auxiliary, vector<char>& outMas, int step)
{
    if (flag || !n) return;

    SearchStep(n - 1, source, auxiliary, destination, outMas, step);
    if (flag) return;
    int cur = findValue(outMas, source);
    outMas[cur] = destination;
    for (int i = 0; i < outMas.size(); i++) cout << outMas[i] << ' ';
    cout << endl;
    curStep++;

    if (step == curStep) {
        flag = 1;
        return;
    }
    SearchStep(n - 1, auxiliary, destination, source, outMas, step);
}


void BinaryHanoi(int n, char source, char destination, char auxiliary, int step, stack<char> stack)
{
    curStep = n - 1;

    while (curStep != -1) {
        
        if ((step >> curStep) & 1) {
            
            stack.push(destination);
            swap(source, auxiliary);
        }
        else {
            stack.push(source);
            swap(destination, auxiliary);
        }
        curStep--;
    }
    while (!stack.empty())
    {
        char sym = stack.top();
        cout << sym << ' ';
        stack.pop();
    }
    cout << endl;
    
}

int main()
{
    setlocale(LC_ALL, "ru");
    int n = 10;
    int step;
    cout << "1.Рекурсия\n2.Итерация\n3.Поиск любого хода\n4.Поиск введенного хода(при стандартном решении,рекурсия)\n5.Поиск введенного хода(бинарное решение)\n6.Выход";
    cout << "\nВыберите действие : ";
    cin >> step;
    vector<char> outMas;
    vector<char> searchMas;
    int index;
    char cur;
    char aux;
    char start;

    while (step != 6)
    {
        switch (step)
        {
        case 1:
            HanoiRec(n, 'A', 'B', 'C');
            cout << endl;
            break;
        case 2:
            HanoiIter(n, 'A', 'B', 'C', outMas);
            cout << endl;
            break;
        case 3:
            outMas.clear();
            searchMas.clear();

            cout << "Введите шаг: ";
            for (int i = 0; i < n; i++)
            {
                cin >> cur;
                searchMas.push_back(cur);
            }

            for (int i = 0; i < n; i++) outMas.push_back('A');
            for (int i = 0; i < n; i++) cout << outMas[i] << ' ';
            cout << endl;

            index = n - 1;
            start = 'A';
            if (searchMas[index] == 'A') aux = 'A';
            if (searchMas[index] == 'B') aux = 'C';
            if (searchMas[index] == 'C') aux = 'B';

            step = pow(2, n) / 2;

            while (index != -1)
            {

                if (searchMas[index] == start || searchMas[index] == outMas[index])
                {
                    index--;
                    step = step / 2;
                    continue;
                }


                if (start == 'A')
                {
                    if (searchMas[index] == 'B') aux = 'C';
                    if (searchMas[index] == 'C') aux = 'B';
                }
                if (start == 'B')
                {
                    if (searchMas[index] == 'A') aux = 'C';
                    if (searchMas[index] == 'C') aux = 'A';
                }
                if (start == 'C')
                {
                    if (searchMas[index] == 'A') aux = 'B';
                    if (searchMas[index] == 'B') aux = 'A';
                }


                curStep = 0;
                flag = 0;
                SearchStep(index + 1, start, searchMas[index], aux, outMas, step);

                start = aux;
                index--;
                step = step / 2;
            }

            break;
        case 4:
            outMas.clear();
            cout << "Введите количество шагов: ";
            cin >> step;
            curStep = 0;
            flag = 0;
            for (int i = 0; i < n; i++) outMas.push_back('A');
            for (int i = 0; i < outMas.size(); i++) cout << outMas[i] << ' ';
            cout << endl;
            SearchStep(n, 'A', 'B', 'C', outMas, step);
            break;
        case 5:
            cout << "Введите ход: ";
            cin >> step;
            stack<char> stack;
            BinaryHanoi(n, 'A', 'B', 'C', step,stack);
           
            
            break;

        }
        cout << "1.Рекурсия\n2.Итерация\n3.Поиск любого хода\n4.Поиск введенного хода(при стандартном решении,рекурсия)\n5.Поиск введенного хода(бинарное решение)\n6.Выход";
        cout << "\nВыберите действие : "; cin >> step;
    }
    return 0;
}
