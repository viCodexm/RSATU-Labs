
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void solve_problem1() {
        cout << "Задача 1:\n";
        int n; cin >> n;
        vector<int> nums(n);
        for (int i = 0; i < n; ++i)
            cin >> nums[i];
        dpLIS(nums);
        //cout << "Длина: " << lengthOfLIS(nums) << "\n";
    }
    void dpLIS(vector<int>& nums) {
        const int n = nums.size();
        vector<int> dp(n + 1, 1);
        for (int i = 1; i < n; ++i)
            for (int j = 0; j < i; ++j)
                if (nums[i] > nums[j] && dp[i] < dp[j] + 1)
                    dp[i] = dp[j] + 1;
        
        cout << "Последовательность: ";
        int maxIdx = distance(dp.begin(), max_element(dp.begin(), dp.end()));
        int prevMax = dp[maxIdx];
        vector<int> path = {nums[maxIdx]};
        for (int i = maxIdx; i >= 0; --i) {
            if (dp[i] == prevMax - 1) {
                path.push_back(nums[i]);
                prevMax--;
            }
        }
        for (int e : path | views::reverse)
            cout << e << " ";
        cout << "\n";
    }

    int lengthOfLIS(vector<int>& nums) {
        vector<int> temp = {nums[0]};
        const int n = nums.size();
        for (int i = 1; i < n; ++i) {
            if (nums[i] > temp.back())
                temp.push_back(nums[i]);
            else {
                int idx = lower_bound(temp.begin(),temp.end(),nums[i]) - temp.begin();
                temp[idx] = nums[i];
            }
        }
        return temp.size();
    }

    vector<int> pathOfLIS(vector<int>& nums) {
        //https://www.cs.princeton.edu/courses/archive/spring13/cos423/lectures/LongestIncreasingSubsequence.pdf
        int n = nums.size();
        vector<int> sub, subIndex; // Store index instead of value for tracing path purpose
        vector<int> trace(n, -1); // trace[i] point to the index of previous number in LIS
        for (int i = 0; i < n; ++i) {
            if (sub.empty() || sub[sub.size() - 1] < nums[i]) {
                if (!sub.empty()) 
                    trace[i] = subIndex[sub.size() - 1];
                sub.push_back(nums[i]);
                subIndex.push_back(i);
            } else {
                int idx = lower_bound(sub.begin(), sub.end(), nums[i]) - sub.begin();
                if (idx > 0)
                    trace[i] = subIndex[idx - 1];
                sub[idx] = nums[i];
                subIndex[idx] = i;
            }
        }
        vector<int> path;
        int t = subIndex[subIndex.size() - 1];
        while (t != -1) {
            path.push_back(nums[t]);
            t = trace[t];
        }
        reverse(path.begin(), path.end());
        return path;
    }

    void solve_problem2() {
        cout << "Задача 2:\n";
        int n, m; cin >> n >> m;
        vector<int> a(n + 1), b(m + 1);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i <= m; ++i)
            cin >> b[i];
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                dp[i][j] = (b[i] == a[j]) + max(dp[i - 1][j], dp[i][j - 1]);
        
        for (vector<int>& v : dp) {
            for (int e : v)
                cout << e << " ";
            cout << "\n";
        }
        cout << "Ответ: " << dp.back().back() << "\n";
        int sx = dp.size() - 1, sy = dp.back().size() - 1;
        vector<int> path;
        while (dp[sx][sy] != 0) {
            if (sx > 1) {
                if (dp[sx][sy] != dp[sx - 1][sy])
                    path.push_back(dp[sx][sy]);
                sx--;
            } else {
                if (dp[sx][sy] != dp[sx][sy - 1])
                    path.push_back(dp[sx][sy]);
                sy--;
            }
        }
        reverse(path.begin(), path.end());
        cout << "Последовательность: ";
        for (int e : path)
            cout << e << " ";
        cout << "\n";
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    Solution a;
    a.solve_problem1();
    a.solve_problem2();
    
    
    return 0;
}