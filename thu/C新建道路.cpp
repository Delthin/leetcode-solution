#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int LOGN = 20;
const ll INF = 1e18;
int n;
vector<vector<pair<int, int>>> adj;
vector<ll> dist;  // 到一号的距离
vector<int> tsize; // 子树的大小
vector<int> path; // 基环树的路径
vector<ll> path_dists;// 基环树上点的前缀距离
vector<int> counts; // 环上每个点的子树大小

vector<vector<int>> parent;
vector<int> depth;
void dfs_lca(int u, int p, int d)
{
    depth[u] = d;
    parent[u][0] = p;
    for (auto [v, w] : adj[u]) {
        if (v != p) {
            dfs_lca(v, u, d + 1);
            tsize[u] += tsize[v];
        }
    }
}

int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    for (int j = LOGN - 1; j >= 0; --j) {
        if (depth[u] - (1 << j) >= depth[v]) {
            u = parent[u][j];
        }
    }

    if (u == v)
        return u;

    for (int j = LOGN - 1; j >= 0; --j) {
        if (parent[u][j] != 0 && parent[u][j] != parent[v][j]) {
            u = parent[u][j];
            v = parent[v][j];
        }
    }
    return parent[u][0];
}

void dfs_dist(int u, int p, ll d)
{
    dist[u] = d;
    for (auto [v, w] : adj[u]) {
        if (v != p) {
            dfs_dist(v, u, d + w);
        }
    }
}

void preprocess()
{
    depth.resize(n + 1, 0);
    dist.resize(n + 1, INF);
    tsize.resize(n + 1, 1);
    parent.resize(n + 1, vector<int>(LOGN, 0));
    dfs_lca(1, 0, 0);
    for (int j = 1; j < LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            if (parent[i][j - 1] != 0) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
            }
        }
    }
    dfs_dist(1, 0, 0);
}

void get_path(int u, int v, int l, vector<int>& path)
{
    // 计算从u到v基环树的路径
    int cur = u;
    while (cur != l) {
        path.push_back(cur);
        cur = parent[cur][0];
    }
    path.push_back(l);
    int len_l = path.size();
    cur = v;
    while (cur != l) {
        path.push_back(cur);
        cur = parent[cur][0];
    }
    reverse(path.begin() + len_l, path.end());
}

void get_counts(const vector<int>& path, int x, int y, int l, vector<int>& counts) {
    // 计算环上每个点的子树大小，每个子树距离是否改变只和环上的点有关
    int k = path.size();
    bool found_l = false;
    if (x == l) {
        // 此子树全在路径上，自己加上此子树以外的点
        int child = path[1];
        counts[0] = n - tsize[child];
        found_l = true;
    } else {
        // 子树不在路径上，自己加上所有子树点
        counts[0] = tsize[x];
    }
    if (y == l) {
        int child = path[k - 2];
        counts[k - 1] = n - tsize[child];
    } else {
        counts[k - 1] = tsize[y];
    }

    for (int i = 1; i < k - 1; ++i) {
        int w = path[i];
        int prev_w = path[i - 1];
        int next_w = path[i + 1];
        if (w == l) {
            found_l = true;
            counts[i] = n - tsize[prev_w] - tsize[next_w];
        } else {
            if (!found_l) {
                // w在l的左子树
                counts[i] = tsize[w] - tsize[prev_w];
            } else {
                // w在l的右子树
                counts[i] = tsize[w] - tsize[next_w];
            }
        }
    }
}


void solve() {
    int x, y, z;
    cin >> x >> y >> z;
    if (x == y) { cout << 0 << endl; return; }
    int l = lca(x, y);
    // k为环上点的数量
    get_path(x, y, l, path);
    int k = path.size();
    counts.resize(k);
    get_counts(path, x, y, l, counts);
    path_dists.resize(k, 0);// 从x到y原始路径前缀距离
    for (int i = 1; i < k; ++i) {
        path_dists[i] = path_dists[i-1] + abs(dist[path[i]] - dist[path[i-1]]);
    }

    // d(pu,pv) > d(pu,x) + d(pv,y) + z 才需要更新
    // 两边同时加d(pu,pv)得
    // 2 * d(pu,pv) > d(x,y) + z
    ll threshold = path_dists[k - 1] + z;
    ll ans = 0;
    ll sum_counts = 0;
    // 从枚举环上点(i, j)优化成双指针移动，O(k)
    int p_i = 0;
    for (int j = 1; j < k; ++j) {
        while (p_i < j && 2 * path_dists[p_i] < 2 * path_dists[j] - threshold) {
            sum_counts += counts[p_i];
            p_i++;
        }
        ans += counts[j] * sum_counts;
    }
    cout << ans << '\n';
    path.clear();
    path_dists.clear();
    counts.clear();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int m;
    cin >> n >> m;
    adj.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    preprocess();

    while (m--) {
        solve();
    }
}