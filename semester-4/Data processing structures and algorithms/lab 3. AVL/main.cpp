
#include <iostream>

using namespace std;

#include <bits/stdc++.h>

using namespace std;

struct AVL {

    struct TreeNode {
        int val, height;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int key) : val(key), height(1), left(nullptr), right(nullptr) {}
    };
    TreeNode *root;

    AVL() { root = nullptr; }


    void print() {
        print(root, 0);
    }
    void print(TreeNode* cur, int spaces) {
        if (!cur)
            return;
        print(cur->right, spaces + 3);
        cout << string(spaces, ' ') << cur->val << "\n";
        print(cur->left, spaces + 3);
    }

    int getBalance(TreeNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void insertNode(int key) { root = insertNode(root, key); }

    TreeNode* insertNode(TreeNode* node, int key) {
        if (!node)
            return new TreeNode(key);

        if (key < node->val)
            node->left = insertNode(node->left, key);
        else if (key > node->val)
            node->right = insertNode(node->right, key);
        else return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);
        if (balance > 1 && key < node->left->val)
            return rotateRight(node);
        if (balance < -1 && key > node->right->val)
            return rotateLeft(node);
        if (balance > 1 && key > node->left->val)
            return doubleRight(node);
        if (balance < -1 && key < node->right->val)
            return doubleLeft(node);
        return node;
    }
    TreeNode* rotateLeft(TreeNode* node) {
        if (node->right) {
            TreeNode *u = node->right;
            node->right = u->left;
            u->left = node;
            node->height = max(height(node->left), height(node->right)) + 1;
            u->height = max(height(u->left), node->height) + 1;
            return u;
        }
        return node;
    }

    TreeNode* rotateRight(TreeNode* node) {
        if (node->left) {
            TreeNode *u = node->left;
            node->left = u->right;
            u->right = node;
            node->height = max(height(node->left), height(node->right)) + 1;
            u->height = max(height(u->left), node->height) + 1;
            return u;
        }
        return node;
    }
    TreeNode* doubleLeft(TreeNode* node) {
        node->left = rotateRight(node->left);
        return rotateLeft(node);
    }
    TreeNode* doubleRight(TreeNode* node) {
        node->right = rotateLeft(node->right);
        return rotateRight(node);
    }
    int height(TreeNode* node) { return node ? node->height : 0; }
};
struct Solution {

    void solve_custom() {
        //vector<int> v = {50, 70, 30, 10, 5, 60, 65};
        vector<int> v = {50, 70, 75};
        AVL bt;
        for (int num : v) {
            bt.insertNode(num);
            bt.print();
            cout << "\n\n";
        }
        bt.print();
        cout << "\n";
    }
    void solve() {
        AVL avl;
        avl.insertNode(10);
        avl.insertNode(20);
        avl.insertNode(30);
        avl.insertNode(40);
        avl.insertNode(50);
        avl.insertNode(25);
        avl.print();
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    Solution a;
    //a.solve();
    //cout << "\n\nВариант 2:\n\n";
    a.solve_custom();

    return 0;
}