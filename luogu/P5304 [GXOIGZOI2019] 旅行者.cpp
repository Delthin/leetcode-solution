#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18;
using PII = pair<ll, int>; // {distance, vertex}
ll dijkstra(int n, const vector<vector<pair<ll, int>>>& adj) {
    vector<ll> dist(n + 3, INF);
    dist[n + 1] = 0;
    // 小根堆
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.emplace(0, n + 1);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue; // 剪枝：已找到更短的路径
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist[n + 2];
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<pair<ll, int>>> adj(n + 3);
        int s = n + 1, t = n + 2;
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].emplace_back(v, w);
        }
        vector<int> a(k);
        for (int i = 0; i < k; i++) {
            cin >> a[i];
        }
        ll ans = LONG_LONG_MAX;
        for (int i = 0; (1 << i) <= k; i++) {
            // 对每一位枚举，分别将1和0归到s和t
            for (int j = 0; j < k; j++) {
                if (j >> i & 1) {
                    adj[s].emplace_back(a[j], 0);
                } else {
                    adj[a[j]].emplace_back(t, 0);
                }
            }
            ans = min(ans, dijkstra(n, adj));
            for (int j = 0; j < k; j++) {
                if (j >> i & 1) {
                    adj[s].pop_back();
                } else {
                    adj[a[j]].pop_back();
                }
            }
            // 再反过来分配s和t跑一遍（因为单向路，第一遍分配不全）
            for (int j = 0; j < k; j++) {
                if (j >> i & 1) {
                    adj[a[j]].emplace_back(t, 0);
                } else {
                    adj[s].emplace_back(a[j], 0);
                }
            }
            ans = min(ans, dijkstra(n, adj));
            for (int j = 0; j < k; j++) {
                if (j >> i & 1) {
                    adj[a[j]].pop_back();
                } else {
                    adj[s].pop_back();
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}