
#include <bits/stdc++.h>

using namespace std;

struct edge {
    int color = 0, number = 0;
    vector<int> to;
};

struct Solution {
    const int WHITE = 0, GREY = 1, BLACK = 2;
    int number = 0;

    void solve_tests() {
        freopen("input.txt", "r", stdin);
        int tests; cin >> tests;
        while (tests --> 0)
            solve();
        
    }

    void solve() {
        vector<edge> graph;
        read_graph(graph);

        cout << "\n M нумерация: ";
        number = 1;
        for (int i = 1; i < graph.size(); ++i)
            if (graph[i].color == WHITE)
                dfs_m(i, graph);

        print_numeration(graph);
        clean(graph);

        cout << "\n N нумерация: ";
        number = graph.size() - 1;
        for (int i = 1; i < graph.size(); ++i)
            if (graph[i].color == WHITE)
                dfs_n(i, graph);
                
        print_numeration(graph);
        cout << "\n";
    }

private:
    void read_graph(vector<edge>& graph) {
        cout << "Введите n и k:\n";
        int n, k; cin >> n >> k;
        graph.resize(n + 1);
        cout << "Введите k пар:\n";    
        for (int i = 0; i < k; ++i) {
            int from, to; cin >> from >> to;
            graph[from].to.push_back(to);   
        }
    }

    void dfs_m(int cur, vector<edge>& graph) {
        graph[cur].color = GREY;
        graph[cur].number = number++;
        for (int to : graph[cur].to)
            if (graph[to].color == WHITE)
                dfs_m(to, graph);
        
        graph[cur].color = BLACK;
    }

    void dfs_n(int cur, vector<edge>& graph) {
        graph[cur].color = GREY;
        for (int to : graph[cur].to)
            if (graph[to].color == WHITE)
                dfs_n(to, graph);
        
        graph[cur].color = BLACK;
        graph[cur].number = number--;
    }

    void clean(vector<edge>& graph) {
        for (auto& edge : graph) {
            edge.color = WHITE;
            edge.number = NULL;
        }
    }
    void print_numeration(vector<edge>& graph) {
        for (int i = 1; i < graph.size(); ++i)
            cout << graph[i].number << " ";
        cout << "\n";
    }
};

int main() {

    Solution a;
    a.solve_tests();
    
    return 0;
}
