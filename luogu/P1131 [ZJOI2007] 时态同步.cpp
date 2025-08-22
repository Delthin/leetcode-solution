#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    int root;
    cin >> root;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<ll> dp(n + 1, 0);
    ll ans = 0;
    function<void(int, int)> dfs = [&] (int u, int p) {
        for (auto [v, w] : adj[u]) {
            if (v == p) {
                continue;
            }
            dfs(v, u);
            dp[u] = max(dp[u], dp[v] + w);
        }
        for (auto [v, w] : adj[u]) {
            if (v == p) {
                continue;
            }
            ans += max(0LL, dp[u] - dp[v] - w);
        }
    };
    dfs(root, 0);
    cout << ans << endl;
    return 0;
}