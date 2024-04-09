
#include <bits/stdc++.h>

using namespace std;


void recHanoi(int height, char fromPole, char toPole, char withPole) {
    if (height < 1)
        return;
    recHanoi(height-1, fromPole, withPole, toPole);
    printf("%c -> %c\n", fromPole, toPole);
    recHanoi(height-1, withPole, toPole, fromPole);
}

stack<int> a, b, c;
string state;
int moves;
void recHanoi_output(int height, char fromPole, char toPole, char withPole) {
    if (height < 1 || moves < 1)
        return;

    moves--;
    recHanoi_output(height-1, fromPole, withPole, toPole);
    
    int disk;
    if (fromPole == 'A') {
        disk = a.top(); a.pop();
    }
    else if (fromPole == 'B') {
        disk = b.top(); b.pop();
    }
    else { disk = c.top(); c.pop(); }

    if (toPole == 'A')
        a.push(disk);
    else if (toPole == 'B')
        b.push(disk);
    else c.push(disk);
    
    state[disk-1] = toPole;
    for (char c : state) cout << c; cout << "\n";
    recHanoi_output(height-1, withPole, toPole, fromPole);
}

void recHanoi_output(int n, int _moves) {
    for (int i = n; i > 0; --i)
        a.push(i);
    state = string(n, 'A');
    cout << state << "\n";
    moves = _moves;
    recHanoi_output(n, 'A', 'B', 'C');
}


void iterHanoi(int i, int j, int k) {
    int max_nodes = (1 << k) - 1 ;
    int root = 1 << (k - 1);
    int node;
    for (node = 1; node <= max_nodes; ++node) {
        int a = i, b = j ;
        int current = root ;
        int ind = root / 2 ;
        
        while (node != current) {
            if (node < current) {
                // левое поддерево
                b = 6-a-b ;
                current -= ind;
            }
            else {
                // правое поддерево.
                a = 6-a-b ;
                current += ind;
            }
            ind /= 2;
        }
        printf("%d -> %d\n", a, b);
    }
}

//void displayAfterMove(int n, int moves) {
//    int numbits = log2(moves) + 1;
//    string binary = bitset<32>(moves).to_string().substr(32 - numbits, numbits);
//    
//    vector<string> matr;
//    matr.push_back("ABC");
//    for (char c : binary | views::reverse) {
//        if (c == '1') {
//            string prev = matr.back();
//            matr.push_back({prev[2], prev[1], prev[0]});
//        }
//        else {
//            string prev = matr.back();
//            matr.push_back({prev[0], prev[2], prev[1]});
//        }
//    }
//    for (string& s : matr)
//        cout << s << "\n";
//    
//}



//void moveTowerwithDisplay(int height, int fromPole, int toPole, int withPole, string& state) {
//    if (height >= 1) {
//        moveTowerwithDisplay(height-1, fromPole, withPole, toPole, state);
//        swap(state[fromPole], state[toPole]);
//        for (char c : state) cout << c << " "; cout << endl;
//        moveTowerwithDisplay(height-1, withPole, toPole, fromPole, state);
//    }
//}
//
//
//char newState(int odd, char c) {
//    if (odd) {
//        if (c == 'A') return 'B';
//        if (c == 'B') return 'C';
//        if (c == 'C') return 'A';
//    }
//    else {
//        if (c == 'A') return 'C';
//        if (c == 'B') return 'A';
//        if (c == 'C') return 'B';
//    }
//    return c;
//}


//stack<int> sGRod;
//stack<int> mGRod;
//stack<int> eGRod;
//
//deque<int> sGDRod;
//deque<int> mGDRod;
//deque<int> eGDRod;
//
//string currentPlacement = "";
//int discsOnBoard = 0;
//
//void recWithStacks(int n, deque<int>& sRod, deque<int>& mRod, deque<int>& eRod, char sPos, char mPos, char ePos) {
//    if (!n)
//        return;
//
//    recWithStacks(n - 1, sRod, eRod, mRod, sPos, mPos, ePos);
//    eRod.push_back(sRod.back()); sRod.pop_back();
//    
//    for (int j = 0; j < eRod.back(); j++) {
//        for (int i = j; i < discsOnBoard; i++) {
//            if (find(sGDRod.begin(), sGDRod.end(), i + 1) != sGDRod.end()) {
//                currentPlacement[j] = sPos;
//                break;
//            }
//            else if (find(mGDRod.begin(), mGDRod.end(), i + 1) != mGDRod.end()) {
//                currentPlacement[j] = mPos;
//                break;
//            }
//            else if (find(eGDRod.begin(), eGDRod.end(), i + 1) != eGDRod.end()) {
//                currentPlacement[j] = ePos;      
//                break;
//            }
//        }
//    }
//
//    cout << currentPlacement << endl;
//    recWithStacks(n - 1, mRod, sRod, eRod, sPos, mPos, ePos);
//    return;
//}
//
//
//
//void moveToDesiredState(string desire) {
//    string str = string(desire.size(), 'A');
//    char mid = ' ', start = 'A';
//    for (int i = str.size() - 1; i >= 0; i--) {
//        if (currentPlacement[i] == str[i])
//            continue;
//            
//        if (start == 'A') {
//
//            if (str[i] == 'B') {
//                mid = 'C';
//                recWithStacks(i, sGDRod, mGDRod, eGDRod, start, str[i], mid);
//                recWithStacks(1, sGDRod, eGDRod, mGDRod, start, str[i], mid);
//            }
//            else {
//                mid = 'B';
//                recWithStacks(i, sGDRod, eGDRod, mGDRod, start, mid, str[i]);
//                recWithStacks(1, sGDRod, mGDRod, eGDRod, start, mid, str[i]);
//            }
//        }
//        else if (start == 'B') {
//
//            if (str[i] == 'A') {
//                mid = 'C';
//                recWithStacks(i, mGDRod, sGDRod, eGDRod, str[i], start, mid);
//                recWithStacks(1, mGDRod, eGDRod, sGDRod, str[i], start, mid); 
//            }
//            else {
//                mid = 'A';
//                recWithStacks(i, mGDRod, eGDRod, sGDRod, mid, start, str[i]);
//                recWithStacks(1, mGDRod, sGDRod, eGDRod, mid, start, str[i]);
//            }
//        }
//        else {
//            if (str[i] == 'A') {
//                mid = 'B';
//                recWithStacks(i, eGDRod, sGDRod, mGDRod, str[i], mid, start);
//                recWithStacks(1, eGDRod, mGDRod, sGDRod, str[i], mid, start);
//            }
//            else {
//                mid = 'A';
//                recWithStacks(i, eGDRod, mGDRod, sGDRod, mid, str[i], start);
//                recWithStacks(1, eGDRod, sGDRod, mGDRod, mid, str[i], start);
//            }
//        }
//        start = mid;
//    }
//}

int main() {

    cout << "Рекурсивное решение:\n";
    recHanoi(4, '1', '2', '3');
    cout << "\nИтерационное решение:\n";
    iterHanoi(1, 2, 4);

    cout << "\nРасположение дисков после заданного числа ходов:\n";
    recHanoi_output(44, 33);
    //cout << "\n";
    //string state = "BBBBBB";
    //moveTowerwithDisplay(3, 0, 1, 2, state);


    //moveToDesiredState("ABBC");
    //int n = 5, move = 18;
    //printf("\nРасположение %d колец после %d шага:\n", n, move);
    //displayAfterMove(n, move);
    //cout << "\n\n";

    

    return 0;
}
