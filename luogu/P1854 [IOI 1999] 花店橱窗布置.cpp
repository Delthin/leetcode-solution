#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> a(m + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MIN));// 前n个花瓶放了m朵花的最大
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= min(i, m); j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + a[j][i]);
        }
    }
    cout << dp[n][m] << endl;
    vector<int> ans(m + 1); // 每朵花放入的花瓶编号
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i - 1][j]) {
            i--;
        } else {
            ans[j] = i;
            i--;
            j--;
        }
    }
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << " \n"[i == m];
    }
    return 0;
}
