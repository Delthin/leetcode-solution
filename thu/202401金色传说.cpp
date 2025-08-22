//
// Created by lisiyi on 25-8-2.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<ll, ll>> nums(n);
    for (int i = 0; i < n; i ++) {
        cin >> nums[i].second >> nums[i].first;
    }
    sort(nums.begin(), nums.end());
    ll max_profit = -1e18;

    // for (int i = 0; i <= n - k; i ++) {
    //     priority_queue<ll, vector<ll>, greater<>> pq;
    //     ll sum_of_largest_A = 0;
    //     // 维护k-2个最大的A
    //     for (int l = i + 1; l <= i + k - 2; ++l) {
    //         pq.push(nums[l].second);
    //         sum_of_largest_A += nums[l].second;
    //     }
    //     for (int j = i + k - 1; j < n; j++) {
    //         ll current_profit = sum_of_largest_A + nums[i].first + nums[i].second + nums[j].second - nums[j].first;
    //         max_profit = max(max_profit, current_profit);
    //         if (j + 1 < n && k > 2) {
    //             ll new_a = nums[j].second;
    //             if (new_a > pq.top()) {
    //                 sum_of_largest_A -= pq.top();
    //                 pq.pop();
    //                 pq.push(new_a);
    //                 sum_of_largest_A += new_a;
    //             }
    //         }
    //     }
    // }
    vector<vector<ll>> dp(n, vector<ll>(k + 1, -1e18));// 前i个数里，选k个的最大利润
    dp[0][1] = nums[0].first + nums[0].second;
    for (int i = 1; i < n; i++) {
        dp[i][1] = max(dp[i - 1][1], nums[i].first + nums[i].second);
        for (int j = 2; j <= min(i + 1, k); j ++) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + nums[i].second);
        }
    }
    for (int i = k - 1; i < n; i ++) {
        max_profit = max(max_profit, dp[i][k] - nums[i].first);
    }
    cout << max_profit << endl;

    return 0;
}