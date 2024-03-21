
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

    BalancedTree() {
        root = nullptr;
    }
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
        print(cur->right, spaces + 3);
        cout << string(spaces, ' ') << "*" << cur->val << "\n";
        print(cur->left, spaces + 3);
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


    TreeNode* deleteNode(int key) {
        return deleteNode(root, key);
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root)
            if (key < root->val) root->left = deleteNode(root->left, key);     //We frecursively call the function until we find the target node
            else if (key > root->val) root->right = deleteNode(root->right, key);
            else{
                if (!root->left && !root->right) return NULL;          //No child condition
                if (!root->left || !root->right)
                    return root->left ? root->left : root->right;    //One child contion -> replace the node with it's child
					                                                //Two child condition
                TreeNode* temp = root->left;                        //(or) TreeNode *temp = root->right;
                while(temp->right != NULL) temp = temp->right;     //      while(temp->left != NULL) temp = temp->left;
                root->val = temp->val;                            //       root->val = temp->val;
                root->left = deleteNode(root->left, temp->val);  //        root->right = deleteNode(root->right, temp);
            }
        return root;
    }

    void saveInFile(string filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Unable to open file for writing." << endl;
            return;
        }
        saveInFile(root, file);
        file.close();
    }

    void saveInFile(TreeNode* node, ofstream& file) {
        if (!node) {
            file << "NULL ";
            return;
        }
        file << node->val << " ";
        saveInFile(node->left, file);
        saveInFile(node->right, file);
    }

    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Unable to open file for reading." << endl;
            return;
        }
        root = loadFromFile(file);
        file.close();
    }

    TreeNode* loadFromFile(ifstream& file) {
        string value; file >> value;
        if (value == "NULL")
            return nullptr;

        TreeNode* node = new TreeNode(stoi(value));
        node->left = loadFromFile(file);
        node->right = loadFromFile(file);
        return node;
    }


    void insertNode(int key) {
        root = insertNode(root, key);
    }

    TreeNode* insertNode(TreeNode* node, int key) {
        if (!node)
            return new TreeNode(key);

        if (key < node->val)
            node->left = insertNode(node->left, key);
        else if (key > node->val)
            node->right = insertNode(node->right, key);
        return node;
    }

    void deleteTree() {
        deleteTree(root);
        root = nullptr;
    }

    void deleteTree(TreeNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    bool search(int key) {
        cout << "Root ";
        return search(root, key);
    }

    bool search(TreeNode* node, int key) {
        if (!node)
            return false;

        if (node->val > key) {
            cout << "Left ";
            return search(node->left, key);
        } else if (node->val < key) {
            cout << "Right ";
            return search(node->right, key);
        }
        return node->val == key;
    }
};
struct Solution {

    void solve() {
        cout << "Формирование идеально сбалансированного дерева:\n";
        //cout << "Введите n: "; int n; cin >> n;
        vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
        BalancedTree bt(v);
        bt.print();
        bt.deleteNode(bt.root, 14);
        cout << "Дерево после удаления узла:\n";
        bt.print();
        cout << "Высота дерева: " << bt.maxDepth() << "\n";
        cout << "Количество узлов: " << bt.countNodes() << "\n";
        cout << "Является деревом поиска: " << (bt.isValidBST() ? "Да" : "Нет") << "\n";
        cout << "Является сбалансированым: " << (bt.isBalanced() ? "Да" : "Нет") << "\n";
        int layer = 2;
        cout << "Сумма ключей на уровне " << layer << ": " << bt.layerSum(layer) << "\n";

        bt.saveInFile("output.txt");
        cout << "Удаление дерева, сохранение и чтение его же из файла.\n";
        bt.deleteTree();
        bt.loadFromFile("output.txt");
        bt.print();
    }

    void solve_custom() {
        vector<int> v = {50,30,10,31,61,54,52,59,57,58};
        BalancedTree bt;
        for (int num : v)
            bt.insertNode(num);
        bt.print();
        cout << endl;
        bt.search(58); cout << "\n";
        bt.insertNode(100);
        bt.insertNode(90);
        bt.insertNode(120);
        bt.deleteNode(61);
        bt.print();
        cout << "\n\n";
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    Solution a;
    a.solve_custom();


    return 0;
}
