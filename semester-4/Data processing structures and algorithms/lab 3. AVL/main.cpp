
#include <iostream>

using namespace std;

#include <bits/stdc++.h>

using namespace std;

long long ins_rotates = 0, del_rotates = 0;


struct AVL {

    struct TreeNode {
        int val, height;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int key) : val(key), height(1), left(nullptr), right(nullptr) {}
    };
    TreeNode *root;

    AVL() { root = nullptr; }


    void print() { print(root, 0); }

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
        if (balance > 1 && key < node->left->val) {
            ins_rotates++;
            return rotateRight(node);
        }

        if (balance < -1 && key > node->right->val) {
            ins_rotates++;
            return rotateLeft(node);
        }

        if (balance > 1 && key > node->left->val) {
            ins_rotates += 2;
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->val) {
            ins_rotates += 2;
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
    TreeNode* rotateLeft(TreeNode* node) {
        if (node->right) {
            TreeNode *tmp = node->right;
            node->right = tmp->left;
            tmp->left = node;

            node->height = max(height(node->left), height(node->right)) + 1;
            tmp->height = max(height(tmp->left), node->height) + 1;
            return tmp;
        }
        return node;
    }

    TreeNode* rotateRight(TreeNode* node) {
        if (node->left) {
            TreeNode *tmp = node->left;
            node->left = tmp->right;
            tmp->right = node;

            node->height = max(height(node->left), height(node->right)) + 1;
            tmp->height = max(height(tmp->left), node->height) + 1;
            return tmp;
        }
        return node;
    }
    int height(TreeNode* node) { return node ? node->height : 0; }

    TreeNode* findNode(int key) {
        return findNode(root, key);
    }
    TreeNode* findNode(TreeNode* cur, int key) {
        if (!cur || cur->val == key)
            return cur;
        return findNode((cur->val > key) ? cur->left : cur->right, key);
    }


    TreeNode* findNodeParent(int key) { return findNodeParent(root, key); }

    TreeNode* findNodeParent(TreeNode* cur, int key) {
        if (!cur || cur->left->val == key || cur->right->val == key)
            return cur;
        return findNodeParent((cur->val > key) ? cur->left : cur->right, key);
    }
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* cur = node;
        while (cur->left)
            cur = cur->left;
        return cur;
    }

    TreeNode* deleteNode(int key) { return deleteNode(root, key); }

    TreeNode* deleteNode(TreeNode* node, int key) {
        if (!node)
            return node;
        if (key < node->val)
            node->left = deleteNode(node->left, key);

        else if (key > node->val)
            node->right = deleteNode(node->right, key);
        
        else {
            if (!node->left || !node->right) {
                TreeNode* tmp = (node->left) ? node->left : node->right;

                if (!tmp) {
                    tmp = node;
                    node = NULL;
                } else *node = *tmp;
                free(tmp);
            }
            else {
                TreeNode* tmp = minValueNode(node->right);
                node->val = tmp->val;
                node->right = deleteNode(node->right, tmp->val);
            }
        }


        if (!node)
            return node;
        
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);
        if (balance > 1 && getBalance(node->left) >= 0) {
            del_rotates++;
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0) {
            del_rotates++;
            return rotateLeft(node);
        }

        if (balance > 1 && getBalance(node->left) < 0) {
            del_rotates += 2;
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            del_rotates += 2;
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
    
};
struct Solution {
    
    unordered_set<int> generate_keys(int amount, int max_range) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, max_range);

        unordered_set<int> unique_numbers;
        while (unique_numbers.size() < amount)
            unique_numbers.insert(dis(gen));
        
        //for (const auto& num : unique_numbers)
        //    cout << num << " ";
        //cout << "\n";
        return unique_numbers;
    }
    void solve_custom() {
        //vector<int> v = {50, 70, 30, 10, 5, 60};
        vector<int> v = {50, 25, 75, 15, 35, 60, 120, 10, 68, 90, 125, 83, 100};

        AVL bt;
        for (int num : v) {
            bt.insertNode(num);
            bt.print();
            cout << "\n\n";
        }
        //bt.insertNode(65);
        bt.print();
        cout << "\nУдаление:\n";
        vector<int> del = {60, 15, 120, 50};
        for (int d : del) {
            bt.deleteNode(d);
            bt.print();
            cout << "\n\n";
        }
        cout << "\n";
    }
    void solve_ins_del() {
        unordered_set<int> nums = generate_keys(1000, INT_MAX);
        AVL bt;
        for (int n : nums)
            bt.insertNode(n);

        //nums.shuffle()
        vector<int> del;
        for (int n : nums)
            del.push_back(n);

        random_device rd;
        mt19937 g(rd());
        //shuffle(del.begin(), del.end(), g);
        for (int i = 0; i < del.size() - 1; ++i)
            bt.deleteNode(del[i]);

        
        cout << "Количество поворотов при вставке: " << ins_rotates << " удалении: " << del_rotates << "\n";
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    Solution a;
    a.solve_ins_del();

    return 0;
}