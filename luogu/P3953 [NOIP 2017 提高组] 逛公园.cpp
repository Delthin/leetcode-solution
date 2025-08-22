//统计“路径长度比最短路多k”的方案数，(u, k)进行记忆化搜索，搜索过程中检测导致无限解的零环(访问的状态必然合法)。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, m, k, p;
    cin >> n >> m >> k >> p;
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<vector<pair<int, int>>> adj_r(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj_r[v].emplace_back(u, w);
    }
    vector<ll> dist(n + 1, 1e18);
    auto dijkstra = [&] () {
        dist[1] = 0;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        pq.emplace(0, 1);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) {
                continue;
            }
            for (auto [v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
    };
    dijkstra();

    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, -2)); // 从1到点i，花费k额外代价的方案数
    vector<vector<bool>> vis(n + 1, vector<bool>(k + 1, false));
    function<ll(int, ll)> dfs = [&] (int v, ll cost) {
        if (cost < 0 || cost > k) {
            return 0LL;
        }
        if (dp[v][cost] != -2) {
            return dp[v][cost];
        }
        if (vis[v][cost]) {
            return -1LL;// 有零环
        }
        vis[v][cost] = true;
        ll res = 0;
        if (v == 1 && cost == 0) {
            res = 1; // 有效的一种方案
        }

        for (auto[u, w]: adj_r[v]) {
            ll prev_cost = cost - (dist[u] + w - dist[v]);
            if (prev_cost < 0) {
                continue;
            }
            ll ret = dfs(u, prev_cost);
            if (ret == -1) {
                // 一路返回就行，能dfs到的点，都是合法的
                vis[v][cost] = false;
                return dp[v][cost] = -1LL;
            }
            res = (res + ret) % p;
        }
        vis[v][cost] = false;
        return dp[v][cost] = res;
    };
    bool infinite = false;
    ll total = 0;
    for (int cost = 0; cost <= k; cost++) {
        ll ret = dfs(n, cost);
        if (ret == -1) {
            infinite = true;
            break;
        }
        total = (total + ret) % p;
    }
    if (infinite) {
        cout << -1 << endl;
    }
    else {
        cout << total << endl;
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}