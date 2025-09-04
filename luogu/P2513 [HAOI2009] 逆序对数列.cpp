#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, 0));// 表示i个自然数，逆序对为j的方案数
    // 每次相当于插入最新的数，插入的位置不同，新增逆序对数量也不同
    dp[1][0] = 1;
    const int MOD = 10000;
    for (int i = 2; i <= n; i++) {
        for (int idx = 0; idx < i; idx++) {
            // 插入idx位置，新增i - 1 - idx个逆序对
            for (int j = 0; j <= k - (i - 1 - idx); j++) {
                dp[i][j + (i - 1 - idx)] += dp[i - 1][j];
                dp[i][j + (i - 1 - idx)] %= MOD;
            }
        }
    }
    cout << dp[n][k] << endl;
    return 0;
}