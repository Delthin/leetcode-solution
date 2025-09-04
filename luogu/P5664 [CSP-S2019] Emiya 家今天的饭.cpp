#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 998244353;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    vector<ll> s(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            s[i] += a[i][j];
        }
        s[i] %= MOD;
    }
    // 正难则反，总方案数 - 不合法方案数 = 合法方案数
    // 不合法方案只要遍历每种食材出现 k / 2 + 1 次以上即可
    // 关键：等价于对于每种食材，出现次数比其他食材出现次数和还多的方案数
    vector<vector<ll>> g(n + 1, vector<ll>(n + 1, 0));// 前i种选了j个的方案数
    g[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            g[i][j] = g[i - 1][j];
            if (j > 0) {
                g[i][j] += g[i - 1][j - 1] * s[i - 1] % MOD;
            }
            g[i][j] %= MOD;
        }
    }
    ll total = 0;
    for (int i = 1; i <= n; i++) {
        total += g[n][i];
        total %= MOD;
    }
    for (int col = 0; col < m; col++) {
        // // f[i][j][k]表示对于col这一列，前i行选了col列的j个，其他列选了k个的方案数
        // vector<vector<vector<ll> > > f(n + 1, vector<vector<ll> >(n + 1, vector<ll>(n + 1)));
        // f[0][0][0] = 1;
        // for (int i = 1; i <= n; i++) {
        //     for (int j = 0; j <= i; j++) {
        //         for (int k = 0; k <= i - j; k++) {
        //             f[i][j][k] = f[i - 1][j][k];
        //             if (j > 0) {
        //                 f[i][j][k] += f[i - 1][j - 1][k] * a[i - 1][col] % MOD;// 选这一列新的
        //             }
        //             if (k > 0) {
        //                 f[i][j][k] += f[i - 1][j][k - 1] * (s[i - 1] - a[i - 1][col]) % MOD;// 选这一列以外新的
        //             }
        //             f[i][j][k] %= MOD;
        //         }
        //     }
        // }
        // // 不合法的方案数是j > k 且 j + k > 0的所有情况
        // for (int j = 1; j <= n; j++) {
        //     for (int k = 0; k < j; k++) {
        //         total += MOD - f[n][j][k];
        //         total %= MOD;
        //     }
        // }

        // 考虑合并状态维度j和k, j - k = d - n(考虑下标非负)
        // f[i][d]表示对于col这一列，前i行选了col列的j个，其他列选了k个，其中j - k = d - n的方案数，我们只关心j-k>0的不合法情况
        vector<vector<ll>> f(n + 1, vector<ll>(2 * n + 3, 0));
        f[0][n] = 1;
        for (int i = 1; i <= n; i++) {
            for (int d = n - i; d <= n + i; d++) {
                // 这一行不选
                f[i][d] = f[i - 1][d];
                // 选这列新的，d相当于加了1
                if (d > 0) f[i][d] += f[i - 1][d - 1] * a[i - 1][col] % MOD;
                // 不选这列新的，d相当于减了1
                f[i][d] += f[i - 1][d + 1] * ((s[i - 1] + MOD - a[i - 1][col]) % MOD) % MOD;
                f[i][d] %= MOD;
            }
        }
        // 不合法的方案数是d > 0的所有情况
        for (int d = 1; d <= n; d++) {
            total += MOD - f[n][d + n];
            total %= MOD;
        }
    }
    cout << total << endl;
    return 0;
}