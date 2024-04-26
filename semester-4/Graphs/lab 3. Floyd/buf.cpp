
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	
    freopen("input.txt", "r", stdin);
    int n, k; cin >> n >> k;

    vector<vector<int>> C(n + 1, vector<int>(n + 1, INT_MAX / 3));
    vector<vector<int>> Q(n + 1, vector<int>(n + 1, INT_MAX / 3));

    for (int i = 1; i <= n; ++i)
        Q[i][i] = C[i][i] = 0;

    for (int i = 0; i < k; ++i) {
        int f, t, w; cin >> f >> t >> w;
        C[t][f] = C[f][t] = min(w, C[f][t]);
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (C[i][j] != INT_MAX / 3 && i != j) 
                Q[i][j] = j;
            else Q[i][j] = -1;
        

    // Floyd
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                if (C[i][j] > C[i][k] + C[k][j] ) {
                    C[i][j] = C[i][k] + C[k][j];
                    Q[i][j] = Q[i][k];
                }
            }

    // Paths
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (Q[i][j] != j) {
                cout << "Путь из " << i << " в " << j << ":  ";
                int t = i;
                while (t != j) {
                    cout << " " << t;
                    t = Q[t][j];
                };
                cout << " " << t << endl;
            }

    return 0;
}