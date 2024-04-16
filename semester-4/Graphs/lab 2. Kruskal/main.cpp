
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// `1 <= n` indexation
class DisjointSet {
public:
	vector<int> parent;

	DisjointSet(int n) {
		parent.resize(n + 1);
		for (int i = 1; i <= n; ++i)
			parent[i] = i;
	}
	int getRep(int i) {
		if (parent[i] != i)
			parent[i] = getRep(parent[i]);
		return parent[i];
	}
	void join(int u, int v) {
		int RepU = getRep(u);
		int RepV = getRep(v);
		if (RepU == RepV) return;
		if (rand() % 2)
			parent[RepU] = RepV;
		else parent[RepV] = RepU;
	}
};

struct ftw {
    int from, to, weight;
};

int Kruskall(vector<ftw>& input, int n) {
    DisjointSet ds(n);

    sort(input.begin(), input.end(), [](const ftw& left, const ftw& right) {
		return left.weight < right.weight;
	});
	
	int totalWeight = 0;
	for (ftw& edge : input) {
		if (ds.getRep(edge.from) != ds.getRep(edge.to)) {
			ds.join(edge.from, edge.to);
            cout << edge.from << " " << edge.to << "\n";
			totalWeight += edge.weight;
		}
	}
    return totalWeight;
}


int main() {
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	
    freopen("input.txt", "r", stdin);
    int n, k; cin >> n >> k;
	
    vector<ftw> input;
    for (int i = 0; i < k; ++i) {
        ftw edge; cin >> edge.from >> edge.to >> edge.weight;
        input.push_back(edge);
    }

	cout << Kruskall(input, n) << "\n";

	return 0;
}