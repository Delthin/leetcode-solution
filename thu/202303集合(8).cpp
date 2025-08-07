//
// Created by lisiyi on 25-8-5.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int LOGN = 4; // 根据n的大小调整, ceil(log2(n))
vector<vector<int>> adj;
vector<vector<int>> parent;
vector<int> depth;
vector<int> a;
vector<int> b;
int n;

void dfs_lca(int u, int p, int d) {
    depth[u] = d;
    parent[u][0] = p;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_lca(v, u, d + 1);
        }
    }
}

void preprocess_lca() {
    depth.assign(n + 1, 0);
    parent.assign(n + 1, vector<int>(LOGN, 0));
    dfs_lca(1, 0, 0);

    for (int j = 1; j < LOGN; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (parent[i][j-1] != 0) {
                parent[i][j] = parent[parent[i][j-1]][j-1];
            }
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int j = LOGN - 1; j >= 0; --j) {
        if (depth[u] - (1 << j) >= depth[v]) {
            u = parent[u][j];
        }
    }
    if (u == v) return u;
    for (int j = LOGN - 1; j >= 0; --j) {
        if (parent[u][j] != 0 && parent[u][j] != parent[v][j]) {
            u = parent[u][j];
            v = parent[v][j];
        }
    }
    return parent[u][0];
}

bool is_ancestor(int u, int v) {
    return depth[u] <= depth[v] && lca(u, v) == u;
}

bool is_good_set(int s) {
    // 提取所有的祖先后代对
    // if路径中所有点都在s中，则不合法直接返回
    // else检查条件b，是否有s中的点b值小于路径中非s内的点即s_min_b <= u->v中非s点的max_b
    int s_min_b = INT_MAX;
    for (int i = 1; i <= n; i++) {
        if (s >> (i - 1) & 1) {
            s_min_b = min(s_min_b, b[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && (s >> (i - 1) & 1) && (s >> (j - 1) & 1) && is_ancestor(i, j)) {
                // 检查路径中的所有点，如果都在s中就返回，同时也记录s_min_b和非s点的max_b
                int max_b = INT_MIN;
                for (int k = j; k != i; k = parent[k][0]) {
                    if (!(s >> (k - 1) & 1)) {
                        // 路径上有不在s中的点
                        max_b = max(max_b, b[k]);
                    }
                }
                if (s_min_b > max_b) {
                    return false;
                }
            }
        }
    }
    return true;
}

void solve_1() {
    int c, d;
    cin >> c >> d;
    ll max_score = 0;
    for (int s = 1; s < 1 << n; s++) {
        if (is_good_set(s)) {
            ll sum_a = 0;
            int min_b = INT_MAX;
            for (int i = 1; i <= n; i++) {
                if (s & (1 << (i - 1))) {
                    sum_a += a[i];
                    min_b = min(min_b, b[i]);
                }
            }
            max_score = max(max_score, sum_a * c + (ll)min_b * d);
        }
    }
    cout << max_score << endl;
}

int main() {
    int q;
    cin >> n >> q;
    adj.resize(n + 1);
    a.resize(n + 1, 0);
    b.resize(n + 1, 0);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    preprocess_lca();
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
    while (q--) {
        if (n <= 10 && q <= 10) solve_1();
    }
    return 0;
}