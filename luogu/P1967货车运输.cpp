// 最大生成树加lca
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
int N = 5005;
vector<int> parent;

struct Edge {
    int u, v, w;
    bool operator < (const Edge & other) const {
        return w > other.w;
    }
};

vector<Edge> edges;
vector<vector<pair<int, int>>> adj;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

const int LOGN = 16;
vector<vector<int>> fa;
vector<vector<int>> weight; // 从自己lca往上跳的最大载重
vector<int> depth;

void dfs_lca(int u, int p, int d, int w) {
    depth[u] = d;
    fa[u][0] = p;
    weight[u][0] = w;
    for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        dfs_lca(v, u, d + 1, w);
    }
}

void preprocess_lca() {
    depth.resize(n + 1, 0);
    fa.resize(n + 1, vector<int>(LOGN, 0));
    weight.resize(n + 1, vector<int>(LOGN, 0));
    // 对每个连通块进行lca
    vector<int> roots;
    for (int i = 1; i <= n; i++) {
        if (parent[i] == i) {
            roots.push_back(i);
        }
    }
    for (int root : roots) {
        dfs_lca(root, 0, 0, 0);
    }
    for (int i = 1; i < LOGN; i++) {
        for (int u = 1; u <= n; u++) {
            int p = fa[u][i - 1];
            if (p == 0) continue;
            fa[u][i] = fa[p][i - 1];
            // 一起跳
            weight[u][i] = min(weight[u][i - 1], weight[p][i - 1]);
        }
    }
}

int lca(int u, int v) {
    // 返回u->l和l->v的最大载重
    if (depth[u] < depth[v]) swap(u, v);
    int res = INT_MAX;
    for (int j = LOGN - 1; j >= 0; --j) {
        if (depth[u] - (1<<j) >= depth[v]) {
            res = min(res, weight[u][j]);
            u = fa[u][j];
        }
    }
    if (u == v) return res;
    for (int j = LOGN - 1; j >= 0; --j) {
        // 此时在同一层
        if (fa[u][j] != 0 && fa[u][j] != fa[v][j]) {
            res = min(res, weight[u][j]);
            res = min(res, weight[v][j]);
            u = fa[u][j];
            v = fa[v][j];
        }
    }
    if (fa[u][0] != fa[v][0] || (fa[u][0] == 0 && fa[v][0] == 0)) return INT_MAX;
    // 最后跳一次
    return min({res, weight[u][0], weight[v][0]});
}

void kruskal() {
    sort(edges.begin(), edges.end());
    parent.resize(n + 1);
    adj.resize(n + 1);
    iota(parent.begin(), parent.end(), 0);
    for (int i = 0; i< m; i++) {
        auto[u, v, w] = edges[i];
        int rootU = find(u), rootV = find(v);
        if (rootU != rootV) {
            parent[rootU] = rootV;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }
}

int main() {
    cin >> n >> m;
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    kruskal();
    preprocess_lca();
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        int res = lca(u, v);
        cout << (res == INT_MAX ? -1 : res) << endl;
    }
    return 0;
}