#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
vector<int> parent;

struct Edge {
    int u, v, w;
    bool operator < (const Edge & other) const {
        return w > other.w;
    }
};

vector<Edge> edges;
vector<bool> occupied;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

ll kruskal() {
    sort(edges.begin(), edges.end());
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    ll mst_weight = 0, edge_count = 0;
    for (int i = 0; i< m; i++) {
        auto[u, v, w] = edges[i];
        int rootU = find(u), rootV = find(v);
        // 只有当一个连通分量本身包含一个初始被占据的节点
        if (rootU != rootV && !(occupied[rootU] && occupied[rootV])) {
            parent[rootU] = rootV;
            occupied[rootV] = occupied[rootV] || occupied[rootU];
            mst_weight += w;
            edge_count++;
        }
    }
    return mst_weight;
}

int main() {
    cin >> n;
    m = n - 1;
    edges.resize(m);
    occupied.resize(n, false);
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        occupied[x] = true;
    }
    ll total = 0;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        total += edges[i].w;
    }
    ll res = kruskal();
    cout << total - res << endl;
    return 0;
}