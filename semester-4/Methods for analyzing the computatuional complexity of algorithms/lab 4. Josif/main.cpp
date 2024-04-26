
#include <iostream>
#include <vector>

using namespace std;

struct LinkedList {
    struct node {
        int number;
        node* next, *prev;
        node(int num) {
            number = num;
            next = prev = this;
        }
    };
    

    node* root;
    
    void create(int n) {
        root = new node(1);
        node* cur = root;
        for (int i = 2; i <= n; ++i) {
            cur->next = new node(i);
            cur->next->prev = cur;
            cur = cur->next;

            cur->next = root;
        }
        cur->next = root;
    }
    void killcurrent(node* cur) {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
    }
    int killThem(int k) {
        node* cur = root;
        int count = 1;
        while (cur->next != cur) {
            if (count == k) {
                //cout << "\e[1mУбили номер: " << cur->number << "\e[0m\n";
                killcurrent(cur);
                count = 0; // 1?
            }
            cur = cur->next;
            count++;
        }
        return cur->number;
    }
    void print() {
        node* cur = root;
        cout << "Вывод списка: " << root->number;
        cur = cur->next;
        while (cur != root) {
            cout << " " << cur->number;
            cur = cur->next;
        }
        cout << "\n";
    }
};

int iterative(int n, int k) {
    int surv = 1, cur = 1;
    while (cur != n) {
        cur++;
        surv = (surv + k) % cur;
        if (!surv) surv = cur;
    }
    return surv;
}

int S(int n, int k) {
    if (k <= n)
        return k;
    return (k % n == 0) ? n : k % n;
}
int rec(int n, int k) {
    if (n == 1)
        return n;
    
    int f = S(n, k) + rec(n - 1, k);
    if (f <= n)
        return f;
    return f - n;
}

int main() {
    //int n, k; cout << "N: "; cin >> n; cout << "K: "; cin >> k;
    //LinkedList ln;
    //ln.create(n);
    //cout << "Моделирование кольцевой структурой: ";
    //cout << ln.killThem(k) << "\n";

    cout << "Рекурсия: \n";
    
        for (int i = 1; i <= 500000; ++i)
            if (rec(i, 375) == 17)
                cout << i << endl;
    
    
    //cout << rec(n, k) << "\n";
    
    //cout << "Итерация: ";
    //cout << iterative(n, k) << "\n";
    return 0;
}