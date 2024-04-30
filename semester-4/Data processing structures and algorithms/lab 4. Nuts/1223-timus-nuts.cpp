
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
    

void init(int k, int n) {
    int steps = 0;
    int root = 0;
    vector<int> leafs = { root };

    while (leafs.size() < n + 1) {
        int size = leafs.size();
        for (int leftCount : leafs) {
            if (leftCount >= k)
                leafs.push_back(leftCount);
            else {
                leafs.push_back(leftCount + 1);
                leafs.push_back(leftCount);
            }
        }
        leafs.erase(leafs.begin(), leafs.begin() + size);
        steps++;
    }
    cout << steps << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    int k = -1; int n = -1;
    while (true) {
        cin >> k >> n;
        if (k == 0 && n == 0)
            break;
        init(k, n);
    }
    return 0;
}
