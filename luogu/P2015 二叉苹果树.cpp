#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    int q;
    cin >> q;
    vector<vector<int>> dp(n + 1, vector<int>(q + 1, 0));// 保留q条边的最大价值
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    function<void(int, int)> dfs = [&] (int u, int p) {
        dp[u][0] = 0;
        for (auto [v, w] : adj[u]) {
            if (v == p) {
                continue;
            }
            dfs(v, u);
            for (int j = q; j >= 1; j--) {
                for (int k = 0; k < j; k++) {
                    dp[u][j] = max(dp[u][j], dp[u][j - k - 1] + dp[v][k] + w);
                }
            }
        }
    };
    dfs(1, 0);
    cout << dp[1][q] << endl;
    return 0;
}