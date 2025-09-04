#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> books(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> books[i].first >> books[i].second;
    }
    sort(books.begin(), books.end());
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n - k + 1, vector<int>(201, 1e9)));// 表示前i本书保留j本,最后一个宽度是w的最小不整齐度
    for (int i = 1; i <= n; i++) {
        int cur = books[i].second;
        for (int j = 1; j <= min(i, n - k); j++) {
            // 不新增
            for (int w = 0; w <= 200; w++) {
                dp[i][j][w] = dp[i - 1][j][w];
            }
            if (j == 1) {
                dp[i][1][cur] = 0;
            }
            // 当前位置i新增
            for (int w = 0; w <= 200; w++) {
                dp[i][j][cur] = min(dp[i][j][cur], dp[i - 1][j - 1][w] + abs(cur - w));
            }
        }
    }
    int ans = 1e9;
    for (int w = 0; w <= 200; w++) {
        ans = min(ans, dp[n][n - k][w]);
    }
    cout << ans << endl;
    return 0;
}