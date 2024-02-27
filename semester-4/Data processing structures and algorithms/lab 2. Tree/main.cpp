
#include <bits/stdc++.h>

using namespace std;

struct BalancedTree {
    
    struct node {
        int val;
        node* left;
        node* right;
        int height;

        node(int key) {
            val = key;
            left = right = nullptr;
            height = 1;
        }
    };
    node *root;

    BalancedTree(int n) {
        BalancedTree(root, n, 1);
    }
    BalancedTree(node *cur, int n, int height) {
        if (!n)
            return;
        cur = new node(1);
        cur->height = height;
        BalancedTree(cur->left, n / 2, height + 1);
        BalancedTree(cur->right, (n + 1) / 2, height + 1);
    }
    void print(node* cur, int spaces) {
        if (!cur)
            return;
        print(cur->right, spaces++);
        cout << string(spaces, ' ') << "*" << "\n";
        print(cur->left, spaces--);
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    int n; cin >> n;
    BalancedTree bt(n);
    
    return 0;
}