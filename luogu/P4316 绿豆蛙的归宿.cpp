#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> in_degree(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        in_degree[v]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        order.push_back(u);
        q.pop();
        for (auto[v, w] : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    vector<pair<double, double>> dp(n + 1, {0, 0}); // 到每个节点的期望长度和概率
    dp[1] = {0, 1};
    for (int i = 0; i < n; i++) {
        int u = order[i];
        int size = adj[u].size();
        for (auto[v, w] : adj[u]) {
            dp[v].first += (dp[u].first + dp[u].second * w) / size;
            dp[v].second += dp[u].second / size;
        }
    }
    cout << fixed << setprecision(2) << dp[n].first << endl;
    return 0;
}

