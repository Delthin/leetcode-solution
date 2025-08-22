#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, m;
    cin >> n >> m;
    m++;
    vector<vector<int>> adj(n + 1);
    vector<int> weight(n + 1);
    for (int v = 1; v <= n; v++) {
        int u, w;
        cin >> u >> w;
        adj[u].emplace_back(v);
        weight[v] = w;
    }
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));// 节点i为根的子树中，选择j个节点（必须包括i本身）的最大值
    function<void(int)> dfs = [&](int u) {
        dp[u][1] = weight[u];
        for (auto v: adj[u]) {
            dfs(v);
            for (int j = m; j >= 1; j--) {
                for (int k = 1; k <= j - 1; k++) {
                    dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[v][k]);
                }
            }
        }
    };
    dfs(0);
    cout << dp[0][m] << endl;
    return 0;
}
