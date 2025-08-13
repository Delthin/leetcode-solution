// 三元环+枚举计数，换一个角度从边思考！
// 解题思路演进分为三个阶段。首先，通过 **$O(N^3)$ 暴力枚举** 所有三人组合来直接模拟，以此理解问题。然后，优化为 **$O(\sum d_u^2)$ 的分类算术法**：对每个学生 `u`，将其余人分为朋友和陌生人，只用循环计算最关键的 `p6`（三角形数），其他概率值 (`p1-p5`) 全部由 `p6` 和度数等信息通过数学公式推导得出，大幅减少了循环。最终，为解决极端情况下的超时，采用 **$O(M\sqrt{M})$ 的全局预处理方案**，通过“三元环计数”算法一次性计算出所有学生的 `p6` 值，使得对每个学生的最终求解过程达到 $O(1)$ 复杂度。
// 寻找不变量与约束、多视角分析、分解与关联、正难则反
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, m;
// vector<vector<pair<int, int>>> adj;
vector<set<int> > adj;
vector<int> degree;
vector<ll> sum_of_friends_degrees;
vector<int> num_p6;

void init() {
    degree.resize(n + 1);
    sum_of_friends_degrees.resize(n + 1, 0);
    num_p6.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        degree[i] = adj[i].size();
    }
    for (int i = 1; i <= n; i++) {
        for (int j: adj[i]) {
            sum_of_friends_degrees[i] += degree[j];
        }
    }
    vector<vector<int>> adj_new(n + 1);
    // 将原图的无向边转换为有向边，从“小”的节点连向“大”的节点。这个“小”的定义是：优先比较度数，度数小的更小；如果度数相同，则比较编号，编号小的更小。
    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            if (make_pair(degree[u], u) < make_pair(degree[v], v)) {
                adj_new[u].push_back(v);
            }
        }
    }
    vector<int> visited(n + 1, 0); // 用作标记数组

    for (int u = 1; u <= n; ++u) {
        // 标记 u 的所有出邻居
        for (int v : adj_new[u]) {
            visited[v] = u; // 用 u 作为标记，避免每次清空
        }

        // 遍历 u 的出邻居 v，再遍历 v 的出邻居 w
        for (int v : adj_new[u]) {
            for (int w : adj_new[v]) {
                // 如果 w 也是 u 的出邻居，则发现一个三元环
                if (visited[w] == u) {
                    num_p6[u]++;
                    num_p6[v]++;
                    num_p6[w]++;
                }
            }
        }
    }
}

ll com(ll a, ll b) {
    if (b == 1) return a;
    if (b == 2) return a * (a - 1) / 2;
    if (b == 3) return a * (a - 1) * (a - 2) / 6;
    return 1;
}

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void frac(ll a, ll b) {
    // 输出最简分数 a/b
    if (a == 0) {
        cout << "0/1";
        return;
    }
    if (a == b) {
        cout << "1/1";
        return;
    }
    ll g = gcd(a, b);
    a /= g;
    b /= g;
    cout << a << "/" << b;
}

void coutall(ll total, ll p1, ll p2, ll p3, ll p4, ll p5, ll p6) {
    frac(p1, total);
    cout << " ";
    frac(p2, total);
    cout << " ";
    frac(p3, total);
    cout << " ";
    frac(p4, total);
    cout << " ";
    frac(p5, total);
    cout << " ";
    frac(p6, total);
    cout << endl;
}

// void solvem1() {
//     for (int i = 1; i <= n; i++) {
//         if (adj[i].empty()) {
//             coutall(com(n - 1, 2), com(n - 1, 2) - 1, 1, 0, 0, 0, 0);
//         } else {
//             coutall(1, 0, 0, 1, 0, 0, 0);
//         }
//     }
// }
// void solve1() {
//     for (int i = 1; i <= n; i++) {
//         // 此时m = 1，m = 3都被排除
//         int friends = adj[i].size();
//         if (friends == 1) {
//             coutall(1, 0, 0, 0, 0, 1, 0);
//         } else {
//             coutall(1, 0, 0, 0, 1, 0, 0);
//         }
//     }
// }
//
// void solve2() {
//     ll all = com(n - 1, 2);
//     for (int u = 1; u <= n; u++) {
//         ll p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0, p6 = 0;
//         // 考虑u的朋友外的任意两点，v，w，其中v必然在w的前面
//         for (int v = 1; v <= n; v++) {
//             if (v == u) continue;
//             if (!adj[u].count(v)) {
//                 // v的朋友以外选不是u或u的朋友的点就是p1
//                 for (int w = v + 1; w <= n; w++) {
//                     if (w == u) continue;
//                     if (adj[u].count(w)) {
//                         // 后面一个是u的朋友
//                         if (adj[v].count(w)) p5++;
//                         else p3++;
//                     } else {
//                         // 后面一个不是u的朋友
//                         if (adj[v].count(w)) p2++;
//                         else p1++;
//                     }
//                 }
//             } else {
//                 // v是u的朋友
//                 // p3 的w非u和v的朋友
//                 for (int w = v + 1; w <= n; w++) {
//                     if (w == u) continue;
//                     if (adj[u].count(w)) {
//                         // w是u的朋友
//                         if (adj[v].count(w)) p6++; // w也是v的朋友
//                         else p4++; // w只是u的朋友
//                     } else {
//                         // w不是u的朋友
//                         if (adj[v].count(w)) p5++;
//                         else p3++;
//                     }
//                 }
//             }
//         }
//         coutall(all, p1, p2, p3, p4, p5, p6);
//     }
// }

void solve() {
    ll all = com(n - 1, 2);
    for (int u = 1; u <= n; u++) {
        // 关键是p2，p5，p6都是特定边的数量
        ll p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0, p6 = 0;
        // A: v 和 w 都是 u 的朋友。
        ll A_all = com(adj[u].size(), 2);
        p6 = num_p6[u];
        p4 = A_all - p6;
        // B: v 是 u 的朋友，w不是
        ll B_all = adj[u].size() * (n - adj[u].size() - 1);

        // 神来之笔1！！！
        // 从v出发，连向u共1条，连向u的其他朋友v-w是朋友朋友边，连向u的陌生人，v-s是朋友陌生人边
        // num_p5 = (sum_{v \in adj[u]} d_v) - d_u - 2 * num_p6 （朋友朋友边被算了两次）
        p5 = sum_of_friends_degrees[u] - adj[u].size() - p6 * 2;
        p3 = B_all - p5;
        // C: v 和 w 都不是 u 的朋友。
        ll C_all = all - A_all - B_all;

        // 神来之笔2！！！
        // num_p2 = m - du - num_p6 - num_p5 p6两个端点都是u的朋友，p5一个端点是u的朋友
        p2 = m - adj[u].size() - p6 - p5;
        p1 = C_all - p2;
        coutall(all, p1, p2, p3, p4, p5, p6);
    }
}

int main() {
    cin >> n >> m;
    if (m == 0) {
        for (int i = 1; i <= n; i ++) {
            coutall(1, 0, 0, 0, 0, 0, 0);
        }
        return 0;
    }
    if (m == n * (n - 1) / 2) {
        for (int i = 1; i <= n; i ++) {
            coutall(1, 0, 0, 0, 0, 0, 1);
        }
        return 0;
    }
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        // adj[a].push_back({b, 1});
        // adj[b].push_back({a, 1});
        adj[a].insert(b);
        adj[b].insert(a);
    }
    init();
    // if (m == 1) {
    //     solvem1();
    //     return 0;
    // }
    // if (n <= 3) {
    //     solve1();
    //     return 0;
    // }
    solve();
}
