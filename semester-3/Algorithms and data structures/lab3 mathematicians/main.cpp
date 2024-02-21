
#include <bits/stdc++.h>

using namespace std;


#define print(v)    for (auto& e : v) cout << e << " "; cout << "\n";
#define read(v)		for (auto& e : v) cin >> e;
#define all(v)      v.begin(), v.end()
#define range(i, a, b) for (int i = a; i < b; ++i)
#define vec         vector
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

typedef vector<char> vc;
typedef vector<vc> vvc;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef vector<vpi> vvpi;
typedef vector<vvpi> vvvpi;

/**/
class Solution {
public:
	struct PairInfo {
		int first, second, sum, product;
	};
	void filter(vector<PairInfo>& pairs, unordered_map<int, vi>& sums, unordered_map<int, vi>& prods, vi& v) {
		const PairInfo& pair = pairs[v[0]];
		const int del = v[0];
		const int& s = pair.sum;
		const int& p = pair.product;

		unordered_map<int, vi>::iterator it = sums.find(s);
		if (it != sums.end()) {
			if (sums[s].size() == 1)
				sums.erase(it);
			else sums[s].erase(find(sums[s].begin(), sums[s].end(), del));
		}

		unordered_map<int, vi>::iterator it2 = prods.find(p);
		if (it2 != prods.end()) {
			if (prods[p].size() == 1)
				prods.erase(it2);
			else prods[p].erase(find(prods[p].begin(), prods[p].end(), del));
		}
	}
	void regret(unordered_map<int, vi>& who, vector<PairInfo>& pairs, unordered_map<int, vi>& sums, unordered_map<int, vi>& prods) {
		for (auto& [key, v] : unordered_map<int, vi>(who.begin(), who.end()))
			if (v.size() == 1)
				filter(pairs, sums, prods, v);
	}
	void knows(unordered_map<int, vi>& who, vector<PairInfo>& pairs, unordered_map<int, vi>& sums, unordered_map<int, vi>& prods) {
		for (auto& [key, v] : unordered_map<int, vi>(who.begin(), who.end())) {
			const int vsize = v.size();
			if (vsize > 1) {
				for (int i = 0; i < vsize; ++i) {
					const PairInfo& pair = pairs[v[i]];
					const int del = v[i];
					const int& s = pair.sum;
					const int& p = pair.product;

					unordered_map<int, vi>::iterator it = sums.find(s);
					if (it != sums.end()) {
						if (sums[s].size() == 1)
							sums.erase(it);
						else sums[s].erase(find(sums[s].begin(), sums[s].end(), del));
					}

					unordered_map<int, vi>::iterator it2 = prods.find(p);
					if (it2 != prods.end()) {
						if (prods[p].size() == 1)
							prods.erase(it2);
						else prods[p].erase(find(prods[p].begin(), prods[p].end(), del));
					}
				}
			}
		}
	}
	void solve(int n) {
		unordered_map<int, vi> sums, prods; // whey store indexes from pairs vector
		vector<PairInfo> pairs(n * (n - 1) / 2 + n); // this formula works :)
		int idx = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = i; j <= n; ++j) {
				pairs[idx] = { i, j, i+j, i*j };
				sums[pairs[idx].sum].push_back(idx);
				prods[pairs[idx].product].push_back(idx);
				idx++;
			}
		char who_is_talking = NULL;
		cout << "Who is talking first: (p/s)?\n";
		cin >> who_is_talking;

		vector<char> dialog;
		char speech = NULL;
		while (cin >> speech && speech != '.')
			dialog.push_back(speech);

		for (char& speech : dialog) {
			if (speech == 'n')
				if (who_is_talking == 'p')
					regret(prods, pairs, sums, prods);
				else regret(sums, pairs, sums, prods);
			else {
				if (who_is_talking == 'p')
					knows(prods, pairs, sums, prods);
				else knows(sums, pairs, sums, prods);
			}

			
			who_is_talking = who_is_talking == 'p' ? 'c' : 'p';
			/*
			for (auto& e : prods) {
				for (int& idx : e.second)
					cout << pairs[idx].first << " " << pairs[idx].second << "\n";
			}
			cout << "\n\n";
			/**/
		}
		cout << "\nAnswer:\n";
		int count = 0;
		for (auto& e : prods) {
			for (int& idx : e.second)
				//count++;
				cout << pairs[idx].first << " " << pairs[idx].second << "\n";
		}
		//cout << count;
		cout << "\n\n";
	}
};
/**/

int main() {
	ios_base::sync_with_stdio(false);
	/**/
	int n; cin >> n;
	Solution a; a.solve(n);
	/**/


	cout << "\nYAY\n";

	return 0;
}