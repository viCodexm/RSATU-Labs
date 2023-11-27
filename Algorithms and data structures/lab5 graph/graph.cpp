
#include <bits/stdc++.h>

using namespace std;

//#define DEBUG 0

struct edge {
    unordered_set<int> to;
    unordered_set<int> in_me;
};

int main() {
    
    #ifdef DEBUG
        freopen("test.txt", "r", stdin);
    #endif

    cout << "Введите n и k:\n";
    int n, k; cin >> n >> k;
    cout << "Введите k пар:\n";
    unordered_map<int, edge> graph;
    for (int i = 0; i < k; ++i) {
        int from, to; cin >> from >> to;
        graph[from].to.insert(to);
        graph[to].in_me.insert(from);
    }
    // add edges that previously were not considered
    for (int i = 1; i <= n; ++i) 
        graph[i];

    vector<int> ans;
    vector<int> que;
    for (auto g : graph) {
        auto& [idx, links] = g;
        
        if (links.in_me.empty())
            que.push_back(idx);
    }


    while (true) {
        vector<int> del, qnext;

        for (int& idx : que) {
            auto links = graph[idx];
            
            if (links.in_me.empty()) {
                for (int to : links.to) {
                    graph[to].in_me.erase(idx);
                    if (graph[to].in_me.empty())
                        qnext.push_back(to);
                }
                del.push_back(idx);
            }
        }
        que = qnext;
        for (int& idx : del) {
            ans.push_back(idx);
            graph.erase(idx);
        }

        if (del.empty()) {
            break;
        }
    }
    if (ans.size() < n)
        cout << "Вывод частичного графа:\n"; 
    for (int& e : ans)
        cout << e << " ";

    return 0;
}
