// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;
// const ll INF = 1e18;
//
// int main() {
//     int n, m;
//     cin >> n >> m;
//     string type;
//     cin >> type;
//     vector<int> p(n + 1);
//     for (int i = 1; i <= n; i++) {
//         cin >> p[i];
//     }
//     vector<vector<int>> adj(n + 1);
//     for (int i = 0; i < n - 1; i++) {
//         int u, v;
//         cin >> u >> v;
//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }
//     auto solve1 = [&]() {
//         while (m --) {
//             int a, x, b, y;
//             cin >> a >> x >> b >> y;
//             vector<vector<ll>> dp(n + 1, vector<ll>(2, LONG_LONG_MAX));
//             // 以u为根的子树合法的最小代价
//             function<void(int, int)> dfs = [&](int u, int fa) {
//                 // 道路两端至少有一个点被驻扎
//                 dp[u][0] = 0;
//                 dp[u][1] = p[u];
//                 for (int v : adj[u]) {
//                     if (v == fa) continue;
//                     dfs(v, u);
//                     dp[u][1] += min(dp[v][0], dp[v][1]);
//                     dp[u][0] += dp[v][1];
//                 }
//                 if (u == a) {
//                     dp[u][!x] = INF;
//                 }
//                 if (u == b) {
//                     dp[u][!y] = INF;
//                 }
//             };
//             dfs(1, 0);
//             ll ans = min(dp[1][0], dp[1][1]);
//             cout << ((ans >= INF) ? -1 : ans) << endl;
//         }
//     };
//     auto solveA1 = [&]() {
//         // 此时点1必选，直接从点2开始dp即可，计算每个点前缀最小代价和后缀最小代价
//         vector<vector<ll>> dp_pre(n + 2, vector<ll>(2, 0));
//         dp_pre[1][0] = INF;
//         dp_pre[1][1] = p[1];
//         for (int i = 2; i <= n; i++) {
//             dp_pre[i][0] += dp_pre[i - 1][1];
//             dp_pre[i][1] += min(dp_pre[i - 1][0], dp_pre[i - 1][1]) + p[i];
//         }
//         // 后缀最小代价
//         vector<vector<ll>> dp_suf(n + 2, vector<ll>(2, 0));
//         dp_suf[n][0] = 0;
//         dp_suf[n][1] = p[n];
//         for (int i = n - 1; i >= 1; i--) {
//             dp_suf[i][0] += dp_suf[i + 1][1];
//             dp_suf[i][1] += min(dp_suf[i + 1][0], dp_suf[i + 1][1]) + p[i];
//         }
//         while (m --) {
//             int a, x, b, y;
//             cin >> a >> x >> b >> y;
//             ll ans = 0;
//             if (y) {
//                 // 如果选b，那么b-1和b+1都任选
//                 ans += p[b];
//                 ans += min(dp_pre[b - 1][0], dp_pre[b - 1][1]);
//                 ans += min(dp_suf[b + 1][0], dp_suf[b + 1][1]);
//             } else {
//                 // b-1和b+1都必须选
//                 ans += dp_pre[b - 1][1];
//                 ans += dp_suf[b + 1][1];
//             }
//             cout << ans << endl;
//         }
//     };
//     auto solveA2 = [&]() {
//         // 此时ab相连，计算每个点前缀最小代价和后缀最小代价
//         vector<vector<ll>> dp_pre(n + 2, vector<ll>(2, 0));
//         dp_pre[1][0] = 0;
//         dp_pre[1][1] = p[1];
//         for (int i = 2; i <= n; i++) {
//             dp_pre[i][0] += dp_pre[i - 1][1];
//             dp_pre[i][1] += min(dp_pre[i - 1][0], dp_pre[i - 1][1]) + p[i];
//         }
//         // 后缀最小代价
//         vector<vector<ll>> dp_suf(n + 2, vector<ll>(2, 0));
//         dp_suf[n][0] = 0;
//         dp_suf[n][1] = p[n];
//         for (int i = n - 1; i >= 1; i--) {
//             dp_suf[i][0] += dp_suf[i + 1][1];
//             dp_suf[i][1] += min(dp_suf[i + 1][0], dp_suf[i + 1][1]) + p[i];
//         }
//         while (m--) {
//             int a, x, b, y;
//             cin >> a >> x >> b >> y;
//             if (a > b) {
//                 swap(a, b);
//                 swap(x, y);
//             }
//             ll ans = 0;
//             if (!x && !y) {
//                 cout << -1 << endl;
//                 continue;
//             }
//             if (x) {
//                 // 如果选a, 那么a-1任选
//                 ans += p[a];
//                 ans += min(dp_pre[a - 1][0], dp_pre[a - 1][1]);
//             } else {
//                 // a-1必须选
//                 ans += dp_pre[a - 1][1];
//             }
//             if (y) {
//                 // 如果选b，那么b+1任选
//                 ans += p[b];
//                 ans += min(dp_suf[b + 1][0], dp_suf[b + 1][1]);
//             } else {
//                 // b+1都必须选
//                 ans += dp_suf[b + 1][1];
//             }
//             cout << ans << endl;
//         }
//     };
//     if (type == "A1") {
//         solveA1();
//     } else if (type == "A2") {
//         solveA2();
//     } else {
//         solve1();
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18; // 使用一个足够大的数表示无穷大
const int MAXN = 100005;
const int LOGN = 18; // log2(100005) 约等于 17

int n, m;
vector<int> p;
vector<vector<int>> adj;
set<pair<int, int>> edges; // 用于快速判断两点是否相邻
// f[u][0/1]: 以u为根的子树中，u不选/选的最小开销 (自底向上DFS计算)
vector<vector<ll>> f;
// g[u][0/1]: 除u的子树外，图中剩余部分在u的父节点状态导致u不选/选时的最小开销 (自顶向下DFS计算)
vector<vector<ll>> g;
// 倍增数组
vector<int> depth;
vector<vector<int>> parent;
// fh[u][j][su][sv]: u状态为su，u的2^j祖先v状态为sv时，v子树去掉u子树这部分的最小开销
ll fh[MAXN][LOGN][2][2];
// DFS1: 计算 f, depth, parent[u][0]
void dfs1(int u, int fa, int d) {
    depth[u] = d;
    parent[u][0] = fa;
    f[u][1] = p[u];
    f[u][0] = 0;
    for (int v : adj[u]) {
        if (v == fa) continue;
        dfs1(v, u, d + 1);
        f[u][1] += min(f[v][0], f[v][1]);
        f[u][0] += f[v][1];
    }
}
// DFS2: 计算 g 数组
void dfs2(int u, int fa) {
    for (int v : adj[u]) {
        if (v == fa) continue;
        // 计算 g[v][0] (v不选，则父节点u必须选)
        // 开销 = (u子树外的开销 | u选) + (u子树内除了v分支的开销 | u选)
        g[v][0] = g[u][1] + (f[u][1] - min(f[v][0], f[v][1]));
        // 计算 g[v][1] (v选，则父节点u可选可不选)
        ll cost_u_chosen = g[v][0]; // u选时，和上面情况一样
        ll cost_u_not_chosen = g[u][0] + (f[u][0] - f[v][1]);
        g[v][1] = min(cost_u_chosen, cost_u_not_chosen);
        dfs2(v, u);
    }
}

void precompute() {
    f.assign(n + 1, vector<ll>(2, 0));
    g.assign(n + 1, vector<ll>(2, 0));
    depth.assign(n + 1, 0);
    parent.assign(n + 1, vector<int>(LOGN, 0));
    // 1. 基础树形DP 和 LCA准备
    dfs1(1, 0, 1);
    // 2. 计算子树外开销
    g[1][0] = 0; g[1][1] = 0; // 根节点没有子树外
    dfs2(1, 0);
    // 3. 预处理倍增数组 parent 和 fh
    for (int j = 1; j < LOGN; ++j) {
        for (int i = 1; i <= n; ++i) {
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
        }
    }
    // 3.1 fh 的 base case (j=0, 即u和它的直接父亲)
    for (int i = 1; i <= n; ++i) {
        int fa = parent[i][0];
        if (fa == 0) continue;
        // i不选，父不选: 不合法
        fh[i][0][0][0] = INF;
        // i不选，父选: f[fa][1] - min(f[i][0], f[i][1])
        fh[i][0][0][1] = f[fa][1] - min(f[i][0], f[i][1]);
        // i选，父不选: f[fa][0] - f[i][1]
        fh[i][0][1][0] = f[fa][0] - f[i][1];
        // i选，父选: 和 i不选,父选 一样
        fh[i][0][1][1] = f[fa][1] - min(f[i][0], f[i][1]);
    }
    // 3.2 fh 的递推
    for (int j = 1; j < LOGN; ++j) {
        for (int i = 1; i <= n; ++i) {
            int mid = parent[i][j - 1];
            if (mid == 0 || parent[mid][j-1] == 0) continue;
            for (int u_state = 0; u_state < 2; ++u_state) {
                for (int v_state = 0; v_state < 2; ++v_state) {
                    fh[i][j][u_state][v_state] = INF;
                    // 枚举中间点 mid 的状态 (0 或 1)
                    for (int mid_state = 0; mid_state < 2; ++mid_state) {
                        ll part1 = fh[i][j - 1][u_state][mid_state];
                        ll part2 = fh[mid][j - 1][mid_state][v_state];
                        if (part1 < INF && part2 < INF) {
                           fh[i][j][u_state][v_state] = min(fh[i][j][u_state][v_state], part1 + part2);
                        }
                    }
                }
            }
        }
    }
}

ll solve(int a, int x, int b, int y) {
    if (depth[a] < depth[b]) {
        swap(a, b);
        swap(x, y);
    }
    // tmp_a[s] 表示a跳到当前位置，当前位置状态为s时，a原来子树+路径的最小开销
    ll tmp_a[2] = {INF, INF};
    ll tmp_b[2] = {INF, INF};
    tmp_a[x] = f[a][x];
    tmp_b[y] = f[b][y];
    // 1. 将 a 跳到和 b 同一深度
    for (int i = LOGN - 1; i >= 0; --i) {
        if (depth[a] - (1 << i) >= depth[b]) {
            ll next_tmp_a[2] = {INF, INF};
            for (int cur_state = 0; cur_state < 2; ++cur_state) {
                if (tmp_a[cur_state] >= INF) continue;
                for (int next_state = 0; next_state < 2; ++next_state) {
                    ll path_cost = fh[a][i][cur_state][next_state];
                    if (path_cost < INF) {
                        next_tmp_a[next_state] = min(next_tmp_a[next_state], tmp_a[cur_state] + path_cost);
                    }
                }
            }
            tmp_a[0] = next_tmp_a[0];
            tmp_a[1] = next_tmp_a[1];
            a = parent[a][i];
        }
    }
    // 2. 如果 a,b 是祖先关系
    if (a == b) {
        if (tmp_a[y] >= INF) return -1; // y状态和从下面传上来的状态冲突
        return tmp_a[y] + g[b][y];
    }
    // 3. a,b 一起向上跳到LCA的子节点
    for (int i = LOGN - 1; i >= 0; --i) {
        if (parent[a][i] != parent[b][i]) {
            ll next_tmp_a[2] = {INF, INF};
            ll next_tmp_b[2] = {INF, INF};
            for (int cur_state = 0; cur_state < 2; ++cur_state) {
                for (int next_state = 0; next_state < 2; ++next_state) {
                    if (tmp_a[cur_state] < INF) {
                        ll path_cost_a = fh[a][i][cur_state][next_state];
                        if (path_cost_a < INF) {
                           next_tmp_a[next_state] = min(next_tmp_a[next_state], tmp_a[cur_state] + path_cost_a);
                        }
                    }
                    if (tmp_b[cur_state] < INF) {
                         ll path_cost_b = fh[b][i][cur_state][next_state];
                        if (path_cost_b < INF) {
                            next_tmp_b[next_state] = min(next_tmp_b[next_state], tmp_b[cur_state] + path_cost_b);
                        }
                    }
                }
            }
            tmp_a[0] = next_tmp_a[0]; tmp_a[1] = next_tmp_a[1];
            tmp_b[0] = next_tmp_b[0]; tmp_b[1] = next_tmp_b[1];
            a = parent[a][i];
            b = parent[b][i];
        }
    }
    int lca = parent[a][0];
    // 4. 在 LCA 处合并答案
    ll ans = INF;
    // Case 1: LCA 不选
    ll cost_lca_0 = g[lca][0] + (f[lca][0] - f[a][1] - f[b][1]) + tmp_a[1] + tmp_b[1];
    ans = min(ans, cost_lca_0);
    // Case 2: LCA 选
    ll cost_lca_1 = g[lca][1] + (f[lca][1] - min(f[a][0], f[a][1]) - min(f[b][0], f[b][1]))
                   + min(tmp_a[0], tmp_a[1]) + min(tmp_b[0], tmp_b[1]);
    ans = min(ans, cost_lca_1);
    return ans >= INF ? -1 : ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string type;
    cin >> n >> m >> type;
    p.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    adj.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.insert({u, v});
        edges.insert({v, u});
    }
    precompute();
    for (int i = 0; i < m; ++i) {
        int a, x, b, y;
        cin >> a >> x >> b >> y;
        if (x == 0 && y == 0 && edges.count({a, b})) {
            cout << -1 << "\n";
            continue;
        }
        ll result = solve(a, x, b, y);
        cout << result << "\n";
    }
    return 0;
}
