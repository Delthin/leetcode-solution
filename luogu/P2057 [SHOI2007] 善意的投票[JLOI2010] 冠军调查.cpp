// 纯纯最小割
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int to;      // 边的终点
    long long capacity; // 边的容量
    int rev;     // 反向边的索引
};

struct MaxFlow {
    int n; // 节点数量
    vector<vector<Edge>> adj;
    vector<int> level; // 节点在分层图中的层次
    vector<int> iter;  // 当前弧优化

    MaxFlow(int size) : n(size), adj(size + 1) {}
    // 添加一条从 u 到 v，容量为 cap 的边
    void add_edge(int u, int v, long long cap) {
        adj[u].push_back({v, cap, (int)adj[v].size()});
        adj[v].push_back({u, 0, (int)adj[u].size() - 1}); // 添加反向边，初始容量为0
    }
    // 通过 BFS 构建分层图
    bool bfs(int s, int t) {
        level.assign(n + 1, -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& edge : adj[u]) {
                if (edge.capacity > 0 && level[edge.to] < 0) {
                    level[edge.to] = level[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1;
    }
    // 通过 DFS 寻找增广路
    long long dfs(int u, int t, long long f) {
        if (u == t) return f;
        for (int& i = iter[u]; i < adj[u].size(); ++i) {
            Edge& e = adj[u][i];
            if (e.capacity > 0 && level[u] < level[e.to]) {
                long long d = dfs(e.to, t, min(f, e.capacity));
                if (d > 0) {
                    e.capacity -= d;
                    adj[e.to][e.rev].capacity += d;
                    return d;
                }
            }
        }
        return 0;
    }
    // 计算从 s 到 t 的最大流
    long long solve(int s, int t) {
        long long max_flow = 0;
        while (bfs(s, t)) {
            iter.assign(n + 1, 0);
            long long f;
            while ((f = dfs(s, t, 1e18)) > 0) {
                max_flow += f;
            }
        }
        return max_flow;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<bool> will(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        will[i] = x;
    }
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    MaxFlow mf(n + 2);
    int s = n + 1;
    int t = n + 2;
    for (int i = 1; i <= n; i++) {
        if (will[i]) {
            mf.add_edge(s, i, 1);
        } else {
            mf.add_edge(i, t, 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j : adj[i]) {
            mf.add_edge(i, j, 1);
        }
    }
    cout << mf.solve(s, t) << endl;
    return 0;
}
