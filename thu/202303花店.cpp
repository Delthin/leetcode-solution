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
    int n, m, k;
    ll V;
    cin >> n >> m >> k >> V;
    vector<ll> b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<ll> a(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    int day = m - k + 1;
    vector<ll> c(day + 1);
    for (int i = 1; i <= day; i++) {
        cin >> c[i];
    }
    MaxFlow mf(n + m + 2);
    int s = m + n + 1;
    int t = m + n + 2;
    ll total = 0;
    // 收益边
    for (int j = 1; j <= day; j++) {
        mf.add_edge(s, j, c[j]);
        total += c[j];
    }
    // 代价边
    for (int i = 1; i <= n; i++) {
        mf.add_edge(i + day, t, V - b[i]);
    }
    // 依赖边
    for (int j = 1; j <= day; j++) {
        // 对每个顾客j
        for (int time = j; time <= j + k - 1; time++) {
            int flower = a[time];
            if (b[flower] < V) {
                mf.add_edge(j, flower + day, LONG_LONG_MAX);
            }
        }
    }
    ll ans = total - mf.solve(s, t);
    cout << ans << endl;
    return 0;
}