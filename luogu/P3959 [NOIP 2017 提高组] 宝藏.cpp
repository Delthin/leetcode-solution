#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, m;
vector<vector<pair<int, int>>> adj;
vector<vector<int>> dis;

void solve1() {
    // 保证输入是一棵树
    function<int(int, int, int)> dfs = [&](int u, int p, int d) {
        int res = 0;
        for (auto [v, w] : adj[u]) {
            if (v == p) {
                continue;
            }
            res += d * w;
            res += dfs(v, u, d + 1);
        }
        return res;
    };
    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dfs(i, 0, 1));
    }
    cout << ans << endl;
}

const int INF = 1e9;
using PII = pair<int, int>;
vector<int> dijkstra(int start, const vector<vector<pair<int, int>>>& adj) {
    int n = adj.size();
    vector<int> dist(n + 1, INF);
    dist[start] = 0;
    // 小根堆
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue; // 剪枝：已找到更短的路径
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

void solve2() {
    // 保证所有v相等，直接跑dijkstra就行
    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
        auto dist = dijkstra(i, adj);
        int cost = 0;
        for (int j = 1; j <= n; j++) {
            cost += dist[j];
        }
        ans = min(ans, cost);
    }
    cout << ans << endl;
}

void solve() {
    vector<vector<int>> cost(1 << n, vector<int>(1 << n, INF));
    for (int s = 1; s < (1 << n); s++) {
        for (int sub = s; sub > 0; sub = (sub - 1) & s) {
            if (sub == s) continue;
            cost[sub][s] = 0;
            for (int u = 1; u <= n; u++) {
                int tmp = INF;
                if ((s ^ sub) & (1 << (u - 1))) {
                    // 将s切为sub和s - sub，u在s-sub中，v在sub中
                    // 将所有的u用最短的边连接到sub里的所有点v，他们的开销之和就是cost[sub][s]
                    for (int v = 1; v <= n; v++) {
                        if (sub & (1 << (v - 1))) {
                            tmp = min(tmp, dis[u][v]);
                        }
                    }
                    if (tmp == INF) {
                        cost[sub][s] = INF;
                        break;
                    }
                    cost[sub][s] += tmp;
                }
            }
        }
    }
    // 状压dp，对每个可能的n集合，每一步计算可连接的下一条边最小值，然后更新dp，复杂度 3^n * n^2
    ll ans = LONG_LONG_MAX;
    for (int i = 1; i <= n; i++) {
        vector<vector<ll>> dp(1 << n, vector<ll>(n + 1, LONG_LONG_MAX)); // dp[s][d] 表示当前集合为s，且深度为d时的最小代价
        // dp[s][d + 1] = dp[sub][d] + cost[sub][s] // 从打通d+1层节点集合t和d层节点集合s的代价
        // 从考虑链接一个节点转化为考虑链接一层的节点
        dp[1 << (i - 1)][0] = 0;
        for (int d = 1; d < n; d++) {
            for (int s = 1; s < (1 << n); s++) {
                for (int sub = s; sub > 0; sub = (sub - 1) & s) {
                    if (sub == s || dp[sub][d - 1] == LONG_LONG_MAX) continue;
                    dp[s][d] = min(dp[s][d], dp[sub][d - 1] + (ll)cost[sub][s] * d);
                }
            }
            ans = min(ans, dp[(1 << n) - 1][d]);
        }
    }
    if (n == 1) ans = 0;
    cout << ans << endl;
}

int main() {
    cin >> n >> m;
    adj.resize(n + 1);
    dis.resize(n + 1, vector<int>(n + 1, INF));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        dis[u][v] = dis[v][u] = min(w, dis[v][u]);
    }
    solve();
    return 0;
}