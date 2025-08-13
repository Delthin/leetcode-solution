// 并查集缩点，反向dp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

const int MOD = 998244353;
vector<ll> p2;// 预计算2的幂
void init_p2(int n) {
    p2.resize(n + 1);
    p2[0] = 1;
    for (int i = 1; i <= n; i++) {
        p2[i] = p2[i - 1] * 2 % MOD;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> back_edges;
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        if (z == 0) {
            dsu.unite(x, y);
        } else {
            back_edges.push_back({x, y});
        }
    }

    map<int, int> new_root_id;
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int root = dsu.find(i);
        if (new_root_id.find(root) == new_root_id.end()) {
            new_root_id[root] = cnt++;
        }
    }
    int back_edge_cnt = back_edges.size();
    if (m == n - 1) {
        // 一棵树，检查能不能联通就行
        for (auto& edge:back_edges) {
            int x = edge.first;
            int y = edge.second;
            dsu.unite(x, y);
        }
        for (int i = 1; i <= n; i++) {
            if (dsu.find(i) != dsu.find(1)) {
                cout << 0 << endl;
                return 0;
            }
        }
        cout << 1 << endl; // 必须全部连接才行
        return 0;
    }
    if (m <= 18) {
        ll ans = 0;
        int size = 1 << back_edge_cnt;
        for (int i = 0; i < size; i++){
            DSU d = dsu;
            int components = cnt;
            for (int j = 0; j < back_edge_cnt; j++) {
                if (i >> j & 1) {
                    if (d.unite(back_edges[j].first, back_edges[j].second)) {
                        components--;
                    }
                }
            }
            if (components == 1) {
                ans++;
            }
        }
        cout << ans << endl;
        return 0;
    }
    vector<vector<ll>> choses(cnt, vector<ll>(cnt, 0));// 从第i个连通块连接第j个连通块的方案数
    int new_edge_cnt = 0;// 能用来连接的边的数量
    for (int i = 0; i < back_edges.size(); i++) {
        int x = back_edges[i].first;
        int y = back_edges[i].second;
        if (dsu.find(x) != dsu.find(y)) {
            new_edge_cnt++;
            int new_x = new_root_id[dsu.find(x)];
            int new_y = new_root_id[dsu.find(y)];
            if (new_x > new_y) swap(new_x, new_y);
            choses[new_x][new_y]++;
        }
    }
    init_p2(m + 1);
    int size = 1 << cnt;
    vector<ll> edges_mask(size, 0); // 表示s中所有边的数量
    for (int s = 1; s < size; s++) {
        for (int i = 0; i < cnt; i++) {
            if (s >> i & 1) {
                for (int j = i + 1; j < cnt; j++) {
                    if (s >> j & 1) {
                        edges_mask[s] += choses[i][j];
                    }
                }
            }
        }
    }
    vector<ll> total(size, 0); // 表示s中所有方案总和
    for (int s = 1; s < size; s++) {
        total[s] = p2[edges_mask[s]];
    }
    vector<ll> dp(size, 0); // 表示使s联通的方案数
    for (int s = 1; s < size; s++) {
        dp[s] = total[s];// 初始化所有方案
        int p_mask = s & -s; // 用最小的做基准点，相当于遍历0-n, 1-n ......
        int s_without_p = s ^ p_mask;
        // 对该s下所有可能的子集分左右，左边必须包含p，右边不关心，这样就不重复了，割断左右
        for (int sub = s_without_p; sub >= 0; sub = (sub - 1) & s_without_p) {
            // 枚举所有不包含基准点p的子集，将他们与p连接的部分提取
            int t = sub | p_mask; // T是包含基准点p的s的真子集
            ll bad_cnt = (dp[t] * total[s ^ t]) % MOD;
            dp[s] = (dp[s] - bad_cnt + MOD) % MOD;
            if (sub == 0) break;
        }
    }
    ll ans = dp[size - 1];
    // 还要乘上对联通性质不改变的边的方案数
    ans = ans * p2[back_edge_cnt - new_edge_cnt] % MOD;
    cout << ans << endl;
    return 0;
}