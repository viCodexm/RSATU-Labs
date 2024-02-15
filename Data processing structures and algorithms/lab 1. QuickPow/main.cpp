
#include <bits/stdc++.h>

using namespace std;

template<typename T>
pair<T, int> BinaryPow(T x, unsigned int k)
{
	T res = 1; int count = 0;
	while (k)
	{
		if (k & 1) {
			res *= x;
            count++;
        }
		x *= x;
		k /= 2;
        count++;
	}
	return {res, count};
}

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //for (int i = 1; i <= 1000; ++i)
    //    cout << BinaryPow(1.5, i).second << "\n";
    int n; cin >> n; n++;
    vector<double> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cout << endl << endl;
    reverse(a.begin(), a.end());
    double x = 0.98, ans = a[0], count = 0;
    for (int i = 1; i < n; ++i) {
        ans += a[i] * x;
        x *= x;
        count += 2;
    }
    
    cout << "\nОтвет через быстрое возведение в степень: " << BinaryPow(1.5, 10).first;
    cout << "\nОтвет через экспоненту: " << pow(exp(1), 10*log(1.5));

    cout << "\n\nОтвет: " << ans << "\n";
    cout << "Количество умножений: " << count;
    return 0;
}