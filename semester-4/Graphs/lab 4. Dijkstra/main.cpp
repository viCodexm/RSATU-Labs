
#include <bits/stdc++.h>

using namespace std;

struct myHeap {
    #define INF INT_MAX / 3
    const int WHITE = -1, BLACK = -2;

    int count = 0;
    vector<int> Heap, InHeap, parent, weight;
    vector<vector<pair<int, int>>> adj;

    myHeap(int n) {
        Heap.resize(n + 1, 0);
        InHeap.resize(n + 1, WHITE);
        parent.resize(n + 1, 0);
        weight.resize(n + 1, 0);
        adj.resize(n + 1, vector<pair<int, int>>(0));
    }

    void read() {
        int m; cin >> m;
        for (int i = 0; i < m; ++i) {
            int u, v, w; cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }

    void heap_swap(int i, int j) {
        if (i == j)
            return;
        swap(Heap[i], Heap[j]);
        InHeap[Heap[i]] = i;
        InHeap[Heap[j]] = j;
    }

    bool less(int i, int j) {
        return weight[Heap[i]] < weight[Heap[j]];
    }

    void goUp(int i) {
        while (i > 1 && less(i, i / 2)) {
            heap_swap(i, i / 2);
            i = i / 2;
        }
    }

    void goDown(int i) {
        while (2 * i  <= count) {
            int minIdx = 0;
            int left = 2 * i, right = left + 1;

            minIdx = (less(left, i)) ? left : i;

            if (right <= count && less(right, minIdx))
                minIdx = right;

            if (minIdx == i)
                return;

            heap_swap(minIdx, i);
            i = minIdx;
        }
    }

    void relax(int u, int v, int w) {
        if (weight[u] + w >= weight[v])
            return;

        parent[v] = u;
        weight[v] = weight[u] + w;
        if (InHeap[v] == WHITE) {
            InHeap[v] = ++count;
            Heap[count] = v;
        }
        goUp(InHeap[v]);
    }

    void relax_node(int u) { // релаксируем все дуги из узла
        for (auto v : adj[u])
            relax(u, v.first, v.second);
    }

    void print_path(int s, int t) {
        printf("%d-%d (%d): ", s, t, weight[t]);
        vector<int> path;
        int temp = t;
        while (temp != s) {
            path.push_back(temp);
            temp = parent[temp];
        }
        path.push_back(s);
        for (int num : path | views::reverse)
            cout << num << " ";
        cout << "\n";
    }

    void Dijkstra(int s, int t) {
        cout << "Путь из s в t: \n";
        for (int i = 1; i <= parent.size(); ++i) {
            weight[i] = INF;
            InHeap[i] = WHITE;
        }
        weight[s] = 0;
        count = InHeap[s] = 1;
        Heap[1] = s;
        while (count > 0 && InHeap[t] != BLACK) {
            int u = Heap[1];
            heap_swap(1, count);
            count--;
            goDown(1);
            InHeap[u] = BLACK;
            relax_node(u);
        }
        print_path(s, t);
    }

    void Dijkstra(int s) {
        cout << "\nПуть из s во все вершины: \n";
        for (int i = 1; i <= parent.size(); ++i) {
            weight[i] = INF;
            InHeap[i] = WHITE;
        }
        weight[s] = 0;
        count = InHeap[s] = 1;;
        Heap[1] = s;
        
        while (count > 0) {
            int u = Heap[1];
            heap_swap(1, count);
            count--;
            goDown(1);
            InHeap[u] = BLACK;
            relax_node(u);
        }
        for (int i = 1; i < parent.size(); ++i)
            if (i != s)
                print_path(s, i); 
    }
};

int main() {

    freopen("input.txt", "r", stdin);

    int n; cin >> n;
    myHeap heap(n);
    heap.read();
    int s, t; cin >> s >> t;
    heap.Dijkstra(s, t);
    heap.Dijkstra(s);
    
    return 0;
}