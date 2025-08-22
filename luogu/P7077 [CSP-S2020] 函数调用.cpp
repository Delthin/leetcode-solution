// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;
// const int MOD = 998244353;
//
// int n, m;
// vector<ll> a;
// vector<vector<int>> adj;
//
// struct Func {
//     map<int, ll> add;
//     ll mul = 1;
//     vector<int> g;
// };
//
// vector<Func> funcs;
// vector<int> in_degree;
// void topo_sort() {
//
//     queue<int> q;
//     for (int i = 1; i <= m; i++) {
//         if (in_degree[i] == 0) {
//             q.push(i);
//         }
//     }
//     while (!q.empty()) {
//         int u = q.front();
//         q.pop();
//         auto& func = funcs[u];
//         if (!func.g.empty()) {
//             // type3，需要一个个顺序计算
//             for (int g: func.g) {
//                 const auto& func_g = funcs[g];
//                 for (auto&[p, v]: func.add) {
//                     v = v * func_g.mul % MOD;
//                 }
//                 func.mul = func.mul * func_g.mul % MOD;
//                 for (const auto[p, v]: func_g.add) {
//                     func.add[p] = (func.add[p] + v) % MOD;
//                 }
//             }
//         }
//         for (int v : adj[u]) {
//             in_degree[v]--;
//             if (in_degree[v] == 0) {
//                 q.push(v);
//             }
//         }
//     }
// }
//
// int main() {
//     cin >> n;
//     a.resize(n + 1);
//     for (int i = 1; i <= n; i++) {
//         cin >> a[i];
//     }
//     cin >> m;
//     m++;// 加入一个type3的函数，调用最后的函数序列
//     funcs.resize(m + 1);
//     adj.resize(m + 1);
//     in_degree.resize(m + 1);
//     for (int i = 1; i <= m; i++) {
//         int T;
//         if (i == m) {
//             T = 3;
//         } else {
//             cin >> T;
//         }
//         if (T == 1) {
//             int p, v;
//             cin >> p >> v;
//             funcs[i].add[p] = v;
//         } else if (T == 2) {
//             cin >> funcs[i].mul;
//         } else {
//             int c;
//             cin >> c;
//             for (int j = 0; j < c; j++) {
//                 int g;
//                 cin >> g;
//                 funcs[i].g.push_back(g);
//                 adj[g].push_back(i);
//                 in_degree[i]++;
//             }
//         }
//     }
//     topo_sort();
//     map<int, ll> add = funcs[m].add;
//     ll mul = funcs[m].mul;
//     for (int i = 1; i <= n; i++) {
//         cout << (a[i] * mul % MOD + add[i] + MOD) % MOD << " \n"[i == n];
//     }
//     return 0;
// }
// 不计算每个函数的独立贡献，而是计算每个加法操作的最终贡献，其依赖于其后的所有乘法
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 998244353;

int n, m;
vector<ll> a;
vector<vector<int>> adj;

struct Func {
    int type;
    int p = 0, v = 0; // type1，原始加法操作的参数
    ll mul = 1; // type2 & 3，当前函数的乘法因子
    vector<int> g;// type3，依赖的函数
    ll add_factor = 0; // type1，当前函数的加法因子
};

vector<Func> funcs;
vector<int> in_degree;
vector<int> topo_sort() {

    queue<int> q;
    for (int i = 1; i <= m; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        order.push_back(u);
        q.pop();
        auto& func = funcs[u];
        if (!func.g.empty()) {
            for (int g: func.g) {
                func.mul = func.mul * funcs[g].mul % MOD;
            }
        }
        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    return order;
}

int main() {
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> m;
    funcs.resize(m + 1);
    adj.resize(m + 1);
    in_degree.resize(m + 1);
    for (int i = 1; i <= m; i++) {
        int T;
        cin >> T;
        funcs[i].type = T;
        if (T == 1) {
            cin >> funcs[i].p >> funcs[i].v;
        } else if (T == 2) {
            cin >> funcs[i].mul;
        } else {
            int c;
            cin >> c;
            for (int j = 0; j < c; j++) {
                int g;
                cin >> g;
                funcs[i].g.push_back(g);
                adj[g].push_back(i);
                in_degree[i]++;
            }
        }
    }
    int q;
    cin >> q;
    vector<int> qs(q);
    for (int i = 0; i < q; i++) {
        cin >> qs[i];
    }
    auto order = topo_sort();
    // 最终序列权重初始化
    ll suffix_mul = 1;
    for (int i = q - 1; i >= 0; i--) {
        funcs[qs[i]].add_factor += suffix_mul;
        suffix_mul = suffix_mul * funcs[qs[i]].mul % MOD;
    }

    // 反向拓扑排序，用后续的乘法计算前面加法操作贡献
    for (int i = order.size() - 1; i >= 0; i--) {
        int u = order[i];
        Func& func = funcs[u];
        // 每个u反向传播乘数
        if (func.type == 3 && func.add_factor != 0) {
            ll suffix_mul_u = func.add_factor;
            for (int j = func.g.size() -1; j >= 0; j--) {
                int g = func.g[j];
                funcs[g].add_factor = (funcs[g].add_factor + suffix_mul_u % MOD) % MOD;
                suffix_mul_u = suffix_mul_u * funcs[g].mul % MOD;
            }
        }
    }

    // 先把所有乘法操作的结果算出来
    for (int i = 1; i <= n; i++) {
        a[i] = a[i] * suffix_mul % MOD;
    }

    // 计算每个加法操作的最终贡献
    for (int i = 1; i <= m; i++) {
        if (funcs[i].type == 1) {
            a[funcs[i].p] = (a[funcs[i].p] + funcs[i].v * funcs[i].add_factor % MOD) % MOD;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
    }
    return 0;
}

