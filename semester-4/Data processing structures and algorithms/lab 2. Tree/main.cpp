
#include <bits/stdc++.h>

using namespace std;

struct BalancedTree {
    
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int key) : val(key), left(nullptr), right(nullptr) {}
    };
    TreeNode *root;

    BalancedTree(vector<int>& v) {
        root = createBalancedTree(v, 0, v.size() - 1);
    }
    TreeNode* createBalancedTree(const vector<int>& arr, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        TreeNode* cur = new TreeNode(arr[mid]);

        cur->left = createBalancedTree(arr, start, mid - 1);
        cur->right = createBalancedTree(arr, mid + 1, end);
        return cur;
    }

    void print() {
        print(root, 0);
    }
    void print(TreeNode* cur, int spaces) {
        if (!cur)
            return;
        print(cur->right, spaces + 2);
        cout << string(spaces, ' ') << "*" << cur->val << "\n";
        print(cur->left, spaces + 2);
    }
    int maxDepth() {
        return maxDepth(root);
    }
    int maxDepth(TreeNode* cur) {
        if (!cur) return NULL;
        return 1 + max(maxDepth(cur->left), maxDepth(cur->right));
    }
    int countNodes() {
        return countNodes(root);
    }
    int countNodes(TreeNode* cur) {
        if (!cur) return NULL;
        return 1 + countNodes(cur->left) + countNodes(cur->right);
    }

    bool isValidBST() {
        return isValidBST(root, LONG_MIN, LONG_MAX);
    }
    bool isValidBST(TreeNode* root, long long min, long long max) {
        if (!root) return true;
        if (root->val <= min || root->val >= max)
            return false;
        return isValidBST(root->left, min, root->val) && isValidBST(root->right, root->val, max);
    }


    bool isBalanced() {
        return isBalanced(root);
    }
    bool isBalanced(TreeNode* root) {
        if (!root) return true;
        int left = dfs(root->left);
        int right = dfs(root->right);
        return abs(left - right) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }
    int dfs(TreeNode* root) {
        if (!root) return NULL;
        int left = dfs(root->left);
        int right = dfs(root->right);
        return max(left, right) + 1;
    }

    int layerSum(int targetLayer) {
        queue<TreeNode*> q; q.push(root);
        int layer = 0, sum = 0;
        while (!q.empty()) {
            layer++;
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* left = q.front()->left;
                TreeNode* right = q.front()->right;
                if (left) q.push(left);
                if (right) q.push(right);
                if (layer == targetLayer)
                    sum += q.front()->val;
                q.pop();
            }
            if (layer == targetLayer)
                return sum;
        }
        return 0;
    }
};
struct Solution {
    
    void solve() {
        cout << "Формирование идеально сбалансированного дерева:\n";
        //cout << "Введите n: "; int n; cin >> n;
        vector<int> v = {1, 2, 3, 4, 5, 6, 7};
        BalancedTree bt(v);
        bt.print();
        cout << "Высота дерева: " << bt.maxDepth() << "\n";
        cout << "Количество узлов: " << bt.countNodes() << "\n";
        cout << "Является деревом поиска: " << (bt.isValidBST() ? "Да" : "Нет") << "\n";
        cout << "Является сбалансированым: " << (bt.isBalanced() ? "Да" : "Нет") << "\n";
        int layer = 2;
        cout << "Сумма ключей на уровне " << layer << ": " << bt.layerSum(layer) << "\n";
    }
    void akkerman() {
        int m = 3, n = 10;
        cout << "Для аргументов " << m << " " << n << "\n";
        cout << "Ответ: " << a(m, n) << "\n";
    }
    map<pair<int, int>, int> cache;

    int a(int m, int n) {
        if (m == 0)
            return cache[{m, n}] = n + 1;

        if (cache.find({m, n}) != cache.end())
            return cache[{m, n}];

        if (n == 0)
            return cache[{m, n}] = a(m - 1, 1);

        if (n > 0)
            return cache[{m, n}] = a(m - 1, a(m, n - 1));
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    Solution a;
    //a.solve();
    a.akkerman();

    return 0;
}