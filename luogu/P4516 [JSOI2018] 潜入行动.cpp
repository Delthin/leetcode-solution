
// dp[u][i][0/1][0/1]⟹ 以 u 为根节点的子树，在放了 i 个监视器,保证全部的子树上点都被监视到的情况下，带点 u 上放与不放监视器，且是否被监视到
// 考虑每个子问题的u需要v提供哪些信息
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1000000007;
const int MAXN = 100005;
const int MAXK = 105;

// ================== 修改点 1: 使用全局 C 风格数组 ==================
// dp 和 tmp 都使用全局数组，避免 vector 开销和栈溢出
int dp[MAXN][MAXK][2][2];
int tmp[MAXK][2][2];

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> siz(n + 1);
    // vector<vector<vector<vector<int>>>> dp(n + 1, vector<vector<vector<int>>>(k + 1, vector<vector<int>>(2, vector<int>(2, 0))));
    // vector<vector<vector<int>>> tmp(k + 1, vector<vector<int>>(2, vector<int>(2, 0)));
    function<void(int, int)> dfs = [&](int u, int p) {
        dp[u][0][0][0] = 1;
        dp[u][1][1][0] = 1;
        siz[u] = 1;
        for (int v: adj[u]) {
            if (v == p) continue;
            dfs(v, u);
            int side = min(siz[u], k); // u的子树中已经处理过了的节点个数
            for (int i = 0;i <= side; i++) {
                for (int a = 0; a < 2; a++) {
                    for (int b = 0; b < 2; b++) {
                        tmp[i][a][b] = dp[u][i][a][b];// 暂存之前处理过的信息,必须一个子树一个子树单独处理，考虑u侧状态和v侧状态
                        dp[u][i][a][b] = 0;
                    }
                }
            }
            for (int i = 0; i <= side; i++) {
                for (int j = 0; j <= min(siz[v], k - i); j++) {
                    // 考虑u侧原状态和加上v后的状态，u没放监视器只能从没放的状态转移过来
                    // u可以后续再补监视，v必须当场被监视，合法情况最终要u和v都被监视
                    // 1. u没有监视器且u没被监视，v必须被监视，v有监视器则u被监视
                    dp[u][i + j][0][0] += (int)((ll)tmp[i][0][0] * dp[v][j][0][1] % MOD);// v没有监视器，u也依旧不被监视
                    dp[u][i + j][0][0] %= MOD;
                    dp[u][i + j][0][1] += (int)((ll)tmp[i][0][0] * dp[v][j][1][1] % MOD);// v有监视器，u变成被监视
                    dp[u][i + j][0][1] %= MOD;
                    // 2. u没有监视器且u被监视，v放不放无所谓，但必须被监视
                    dp[u][i + j][0][1] += (int)((ll)tmp[i][0][1] * (((ll)dp[v][j][0][1] + dp[v][j][1][1]) % MOD) % MOD);
                    dp[u][i + j][0][1] %= MOD;
                    // 3. u有监视器且u没被监视，v随便被不被监视，v有监视器则u被监视
                    dp[u][i + j][1][0] += (int)((ll)tmp[i][1][0] * (((ll)dp[v][j][0][0] + dp[v][j][0][1]) % MOD) % MOD);// v没有监视器，u也依旧不被监视
                    dp[u][i + j][1][0] %= MOD;
                    dp[u][i + j][1][1] += (int)((ll)tmp[i][1][0] * (((ll)dp[v][j][1][0] + dp[v][j][1][1]) % MOD) % MOD);// v有监视器，u变成被监视
                    dp[u][i + j][1][1] %= MOD;
                    // 4. u有监视器且u被监视，只能转换到u两个都有的状态，此时v随便啦
                    dp[u][i + j][1][1] += (int)((ll)tmp[i][1][1] * (((ll)dp[v][j][0][0] + dp[v][j][1][0] + dp[v][j][0][1] + dp[v][j][1][1]) % MOD) % MOD);
                    dp[u][i + j][1][1] %= MOD;
                }
            }
            siz[u] += siz[v];
        }
    };
    dfs(1, 0);
    cout << (dp[1][k][0][1] + dp[1][k][1][1]) % MOD << endl;
    return 0;
}