#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
int N = 5005;
vector<int> parent;

struct Edge {
    int u, v, w;
    bool operator < (const Edge & other) const {
        return w < other.w;
    }
};

vector<Edge> edges;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

int kruskal() {
    sort(edges.begin(), edges.end());
    parent.resize(n + 1);
    iota(parent.begin(), parent.end(), 0);
    int mst_weight = 0, edge_count = 0;
    for (int i = 0; i< m; i++) {
        auto[u, v, w] = edges[i];
        int rootU = find(u), rootV = find(v);
        if (rootU != rootV) {
            parent[rootU] = rootV;
            mst_weight += w;
            edge_count++;
        }
    }
    if (edge_count < n - 1) return INT_MAX;
    return mst_weight;
}

int main() {
    cin >> n >> m;
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    int res = kruskal();
    cout << (res == INT_MAX ? "orz" : to_string(res)) << endl;
    return 0;
}