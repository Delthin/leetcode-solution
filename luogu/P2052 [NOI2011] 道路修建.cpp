#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<int> dp(n + 1, 0);// 子树节点数
    ll ans = 0;
    function<void(int, int)> dfs = [&] (int u, int p) {
        for (auto [v, w] : adj[u]) {
            if (v == p) {
                continue;
            }
            dfs(v, u);
            dp[u] += dp[v];
            ans += 1LL * abs(dp[v] - (n - dp[v])) * w;
        }
        dp[u]++;
    };
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}
