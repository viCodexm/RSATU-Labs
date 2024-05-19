
#include <iostream>

using namespace std;

template<typename T>
struct rbTree {
    static_assert(is_arithmetic<T>::value, "rbTree must be instantiated with arithmetic type");
    
    struct node {
        int val;
        bool black;
        node *parent, *left, *right;

        node(int val, bool black) : val(val), black(black), parent(NULL), left(NULL), right(NULL) {};
    };

    node *root;

    rbTree() : root(NULL);

    node* insert(T val) { return insert(root, val); }
    node* search(int key) { return search(root, key); }


    node* insert(node* cur, int key) {
        if (!cur)
            r
    }

    node* search(node* cur, int key) {
        if (!cur || cur->val == key)
            return cur;
        return search(((cur->val > key) ? cur->left : cur->right), key);
    }

    
};

int main() {
    rbTree<int> rbt;
    rbt.insert(15);

    return 0;
}