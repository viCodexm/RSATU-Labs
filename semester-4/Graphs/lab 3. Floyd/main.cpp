
#include <bits/stdc++.h>

using namespace std;


void Floyd(vector<vector<int>>& C, vector<vector<int>>& P, int n) {
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) {
                int path = C[i][k] + C[k][j];
                if (C[i][j] > path) {
                    C[i][j] = path;
                    P[i][j] = P[i][k];
                }
            }
}

void minPaths(vector<vector<int>>& C, vector<vector<int>>& P, int n) {
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (P[i][j] != j) {
                cout << "Путь из " << i << " в " << j << " (" << C[i][j] << "):  ";
                int t = i;
                while (t != j) {
                    cout << t << " ";
                    t = P[t][j];
                }
                cout << t << "\n";
            }
}

int main() {
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	
    freopen("input.txt", "r", stdin);
    int n, k; cin >> n >> k;

    vector<vector<int>> C(n + 1, vector<int>(n + 1, INT_MAX / 3));
    vector<vector<int>> P(n + 1, vector<int>(n + 1, INT_MAX / 3));
    
    for (int i = 1; i <= n; ++i)
        P[i][i] = C[i][i] = 0;

    for (int i = 0; i < k; ++i) {
        int from, to, weight; cin >> from >> to >> weight;
        C[to][from] = C[from][to] = min(weight, C[from][to]);
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (C[i][j] != INT_MAX / 3 && i != j)
                P[i][j] = j;
    
	Floyd(C, P, n);
    minPaths(C, P, n);

	return 0;
}