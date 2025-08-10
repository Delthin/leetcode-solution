#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int LOGN = 20;
const ll INF = 1e18;
int n;
vector<vector<pair<int, int>>> adj;
vector<vector<int>> parent;
vector<int> depth;

vector<ll> dist;  // 到一号的距离
vector<int> tsize; // 子树的大小

void dijkstra(int start)
{
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    pq.emplace(0, start);
    dist[start] = 0;

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        for (const auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
}

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
    dijkstra(1);
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

bool is_ancestor(int u, int v)
{
    return depth[u] <= depth[v] && lca(u, v) == u;
}

ll get_dist(int u, int v)
{
    return dist[u] + dist[v] - 2 * dist[lca(u, v)];
}

ll get_dist(int u, int v, int l)
{
    return dist[u] + dist[v] - 2 * dist[l];
}

vector<int> get_path(int u, int v, int l)
{
    vector<int> path1;
    vector<int> path2;

    int cur = u;
    while (cur != l) {
        path1.push_back(cur);
        cur = parent[cur][0];
    }
    path1.push_back(l);

    cur = v;
    while (cur != l) {
        path2.push_back(cur);
        cur = parent[cur][0];
    }

    reverse(path2.begin(), path2.end());
    path1.insert(path1.end(), path2.begin(), path2.end());

    return path1;
}

vector<ll> get_counts(const vector<int>& path, int x, int y, int l) {
    int k = path.size();

    vector<ll> counts(k);

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
    return counts;
}

void solve() {
    int x, y, z;
    cin >> x >> y >> z;
    if (x == y) { cout << 0 << endl; return; }

    int l = lca(x, y);
    vector<int> path = get_path(x, y, l);
    int k = path.size();
    vector<ll> counts = get_counts(path, x, y, l);

    vector<ll> path_dists(k, 0);
    for (int i = 1; i < k; ++i) {
        path_dists[i] = path_dists[i-1] + abs(dist[path[i]] - dist[path[i-1]]);
    }

    // pu为u到路径上最近的点，每个点是否更新只和其pu有关
    // d(pu,pv) > d(pu,x) + d(pv,y) + z 才需要更新
    // 两边同时加d(pu,pv)得
    // 2 * d(pu,pv) > d(x,y) + z
    ll threshold = get_dist(x, y, l) + z;
    ll ans = 0;

    ll sum_counts = 0;
    int p_i = 0;
    for (int j = 1; j < k; ++j) {
        while (p_i < j && 2 * path_dists[p_i] < 2 * path_dists[j] - threshold) {
            sum_counts += counts[p_i];
            p_i++;
        }
        ans += counts[j] * sum_counts;
    }
    cout << ans << endl;
}

int main()
{
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