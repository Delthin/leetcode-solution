// 有两个测试点没过，不知道啥原因

#include <bits/stdc++.h>
using namespace std;

vector<int> topological_sort(vector<vector<int>>& adj, vector<int>& in_degree, vector<int>& items) {
    queue<int> q;
    vector<int> topo_order;
    // 1. 将所有入度为0的节点入队
    for (auto& item : items) {
        if (in_degree[item] == 0) {
            q.push(item);
        }
    }


    // 2. BFS过程
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);

        // 遍历 u 的所有邻接点 v
        for (int v : adj[u]) {
            in_degree[v]--; // 将 v 的入度减1
            if (in_degree[v] == 0) {
                q.push(v); // 如果 v 的入度变为0，则入队
            }
        }
    }

    // 3. 判断是否有环
    // 如果拓扑序列中的节点数等于图的总节点数，说明无环
    return topo_order.size() == items.size() ? topo_order : vector<int>();
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> cost(n);
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }
    vector<int> items(n);
    iota(items.begin(), items.end(), 0);
    // 正向拓扑求最早开始
    // 反向拓扑求最晚开始
    vector<vector<int>> adj(n);
    vector<vector<int>> adj_reverse(n);
    vector<int> in_degree(n, 0);
    vector<int> out_degree(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj_reverse[v - 1].push_back(u - 1);
        in_degree[v - 1]++;
        out_degree[u - 1]++;
    }
    vector<int> topo_order = topological_sort(adj, in_degree, items);
    vector<int> topo_order_reverse = topological_sort(adj_reverse, out_degree, items);
    vector<int> earliest(n, 0);
    for (int u : topo_order) {
        for (int v : adj[u]) {
            earliest[v] = max(earliest[v], earliest[u] + cost[u]);
        }
    }
    int end_time = 0;
    for (int i = 0; i < n; i++) {
        end_time = max(end_time, earliest[i] + cost[i]);
    }

    vector<int> latest(n, end_time);
    for (int i = 0; i < n; i++) {
        latest[i] -= cost[i];
    }
    for (int u : topo_order_reverse) {
        for (int v : adj_reverse[u]) {
            latest[v] = min(latest[v], latest[u] - cost[v]);
        }
    }
    const int MOD = 1e9 + 7;
    long long ans = 1;
    for (int i = 0; i < n; i++) {
        ans = ans * (long long)(latest[i] - earliest[i] + 1) % MOD;
    }
    cout << end_time << endl;
    cout << ans << endl;
    return 0;
}

