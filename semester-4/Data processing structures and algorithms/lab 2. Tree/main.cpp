
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

    bool deleteNode(int val) {
        return deleteNode(root, val);
    }
    TreeNode* deleteNode(TreeNode* cur, int val) {
        if (!cur)
            return cur;
        if (val > cur->val)
            deleteNode(cur->right, val);
        else if (val < cur->val)
            deleteNode(cur->left, val);
        else {
            // one child or no child
            if (root->left == NULL) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            // two children
            //TreeNode* temp = minValueNode(root->right);
            //root->val = temp->val;
            //root->right = deleteNode(root->right, temp->val);
        }
    }

    TreeNode* deleteNode2(TreeNode* root, int key) {
        if(root) 
            if (key < root->val) root->left = deleteNode2(root->left, key);     //We frecursively call the function until we find the target node
            else if (key > root->val) root->right = deleteNode2(root->right, key);       
            else{
                if (!root->left && !root->right) return NULL;          //No child condition
                if (!root->left || !root->right)
                    return root->left ? root->left : root->right;    //One child contion -> replace the node with it's child
					                                                //Two child condition   
                TreeNode* temp = root->left;                        //(or) TreeNode *temp = root->right;
                while(temp->right != NULL) temp = temp->right;     //      while(temp->left != NULL) temp = temp->left;
                root->val = temp->val;                            //       root->val = temp->val;
                root->left = deleteNode2(root->left, temp->val);  //        root->right = deleteNode(root->right, temp);		
            }
        return root;
    }
};
struct Solution {
    
    void solve() {
        cout << "Формирование идеально сбалансированного дерева:\n";
        //cout << "Введите n: "; int n; cin >> n;
        vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
        BalancedTree bt(v);
        bt.print();
        bt.deleteNode2(bt.root, 14);
        cout << "Дерево после удаления узла:\n";
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

class Solution2 {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
};

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    Solution a;
    a.solve();
    //a.akkerman();

    return 0;
}