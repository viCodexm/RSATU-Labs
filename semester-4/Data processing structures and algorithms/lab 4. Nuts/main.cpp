
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct BinaryTree {
    struct TreeNode {
        int val = 0, leftCount = 0, rightCount = 0;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), leftCount(0), rightCount(0), left(nullptr), right(nullptr) {}
        TreeNode(int x, int lval, int rval) : val(x), leftCount(lval), rightCount(rval), left(nullptr), right(nullptr) {}
    };
    TreeNode *root;

    

    void init(int k, int n) {
        root = new TreeNode();
        vector<TreeNode*> leafs;
        leafs.push_back(root);
        while (leafs.size() < n + 1) {
            vector<TreeNode*> fixed = leafs;
            for (TreeNode* cur : fixed) {
                if (leafs.size() >= n + 1)
                    break;

                if (cur->leftCount < k) {
                    cur->left = new TreeNode(0, cur->leftCount + 1, cur->rightCount);
                    leafs.erase(find(begin(leafs), end(leafs), cur));
                    leafs.push_back(cur->left);
                    
                    cur->right = new TreeNode(0, cur->leftCount, cur->rightCount + 1);
                    leafs.push_back(cur->right);
                }
            }
        }
    }
    int count = 0;
    void fill_leafs() {
        fill_leafs(root);
    }
    void fill_leafs(TreeNode* cur) {
        if (!cur->left && !cur->right) {
            cur->val = count++;
        }
        if (cur->left) fill_leafs(cur->left);
        if (cur->right) fill_leafs(cur->right);
    }

    void fill() {
        fill(root);
    }

    int fill(TreeNode* cur) {
        if (!cur->left && !cur->right) return cur->val;
        int res = fill(cur->left) + fill(cur->right);
        res += res & 1;
        return cur->val = res / 2;
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

    int height() {
        return height(root, 0);
    }
    int height(TreeNode* cur, int h) {
        if (!cur) return h - 1;
        int leftHeight = height(cur->left, h + 1);
        int rightHeight = height(cur->right, h + 1);
        return max(leftHeight, rightHeight);
    }


    // блин, тут же надо bfs ...
    int dfs(int k, int n) {
        return dfs(0, 0, 0, 0, k, n);
    }
    int leafs = 0;
    int dfs(bool isLeft, int leftCount, int rightCount, int k, int n) {
        if (leftCount == k || rightCount == n)
            return height;
        int height = leftCount + rightCount;
        int lheight = dfs(1, leftCount + 1, rightCount);
        int rheight = dfs(0, leftCount, rightCount + 1);
        return max(lheight, rheight);
    }

    void interactive() {
        interactive(root);
    }
    void interactive(TreeNode* cur) {
        if (!cur->left && !cur->right) {
            cout << "Прочность ореха: " << cur->val << "\n";
            return;
        }
        cout << "Разбился с " << cur->val << " ? (y/n)\n";
        char ans; cin >> ans;
        if (ans == 'y')
            interactive(cur->left);
        else interactive(cur->right);
    }
};

int main() {
    
    BinaryTree tree;
    int k = -1; int n = -1;
    while (true) {
        cin >> k >> n;
        if (k == 0 && n == 0)
            break;
        tree.init(k, n);
        tree.fill_leafs();
        tree.fill();
        cout << tree.height() << "\n";
    }
    return 0;
}