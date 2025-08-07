#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> vertex(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> vertex[i];
    }
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].emplace_back(v, c);
    }
    vector<vector<int>> dp(n + 1, vector<int>(802, 0));
    // 起点为u，花了c的最大值
    for (int i = 1; i <= n; i++) {
        dp[i][0] = vertex[i];
    }
    for (int c = 1; c <= 800; c++) {
        for (int i = 1; i <= n; i++) {
            dp[i][c] = max(dp[i][c], dp[i][c - 1]);
            for (auto [v, cost]: adj[i]) {
                if (c - cost < 0) continue;
                dp[i][c] = max(dp[i][c], dp[v][c - cost] + vertex[i]); 
            }
        }
    }
    while(q--) {
        int u, c;
        cin >> u >> c;
        cout << dp[u][c] << endl;
    }
    return 0;
}