#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> sz; // 可选：用于按秩合并

    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0); // iota: parent[i] = i
        sz.assign(n + 1, 1);
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // 路径压缩
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            // 按秩合并(可选，通常路径压缩已足够快)
            if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
            return true;
        }
        return false; // 已经在同一集合中
    }
};

int main() {
    int m, k;
    cin >> m >> k;
    // 1. 并查集判断是否为树
    // 2. 每个节点的度数是否不超过k+1，在度数小于k+1的节点中挑最小的序号
    vector<pair<int, int>> edges(m);
    vector<int> degree(m + 1, 0);
    DSU dsu(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].first >> edges[i].second;
        degree[edges[i].first]++;
        degree[edges[i].second]++;
        if (!dsu.unite(edges[i].first, edges[i].second)) {
            cout << "It's not a tree!" << endl; // 如果有环
            return 0;
        }
    }
    // 判断连通性
    int root = dsu.find(1);
    for (int i = 2; i <= m; ++i) {
        if (dsu.find(i) != root) {
            cout << "It's not a tree!" << endl; // 如果不连通
            return 0;
        }
    }

    int min_node = -1;
    for (int i = 0; i <= m; ++i) {
        if (degree[i] > k + 1) {
            cout << "No such a node!" << endl; // 如果有节点度数超过k+1
            return 0;
        } else if (degree[i] < k + 1) {
            if (min_node == -1 || i < min_node) {
                min_node = i; // 找到度数小于等于k+1的最小节点
            }
        }
    }
    cout << min_node << endl;

    return 0;
}