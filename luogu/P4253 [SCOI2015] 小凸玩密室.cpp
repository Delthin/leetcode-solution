#include <bits/stdc++.h>
using namespace std;
using ll = long long;
inline int lc(int u) {return u << 1;}
inline int rc(int u) {return u << 1 | 1;}
inline int pa(int u) {return u >> 1;}
inline int an(int u, int j) {
    if (u < (1 << (j - 1))) return -1;
    return u >> j;
}
inline int br(int u) {return u ^ 1;}
int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int LOGN = log2(n) + 2;
    // 到第i个祖先节点的距离
    vector<vector<ll>> dist(n + 1, vector<ll>(LOGN, 0));
    for (int i = 2; i <= n; i++) {
        cin >> dist[i][1];
        for (int j = 2; an(i, j) >= 0; j++) {
            dist[i][j] = dist[i][j - 1] + dist[an(i, j - 1)][1];
        }
    }

    vector<vector<ll>> dp_fa(n + 1, vector<ll>(LOGN, LONG_LONG_MAX / 3));// 处理完i的子树后,下一个转移到i的j级祖先的最小代价
    vector<vector<ll>> dp_br(n + 1, vector<ll>(LOGN, LONG_LONG_MAX / 3));// 处理完i的子树后,下一个转移到i的j - 1级祖先的兄弟节点的最小代价
    for (int i = n; i >= 1; i--) {
        for (int j = 1; an(i, j) >= 0; j++) {
            int p = an(i, j);// 当前子问题根的父节点
            int root = an(i, j - 1);// 当前子问题的根
            int bro = br(root);
            int l = lc(i);
            int r = rc(i);
            // i是叶子节点，从p走到i，点亮i，走回p或b
            if (l > n) {
                dp_fa[i][j] = dist[i][j] * a[p];
                if (bro <= n) {
                    dp_br[i][j] = (dist[i][j] + dist[bro][1]) * a[bro];
                }
            }
            // i只有左儿子
            else if (r > n) {
                // 左儿子的dp加上i到左儿子的花费
                dp_fa[i][j] = dp_fa[l][j + 1] + dist[l][1] * a[l];
                dp_br[i][j] = dp_br[l][j + 1] + dist[l][1] * a[l];
            }
            // 左右都有
            else {
                // 回到p
                ll u2l2r2p = dist[l][1] * a[l] + dp_br[l][1] + dp_fa[r][j + 1];
                ll u2r2l2p = dist[r][1] * a[r] + dp_br[r][1] + dp_fa[l][j + 1];
                dp_fa[i][j] = min({dp_fa[i][j], u2l2r2p, u2r2l2p});
                // 回到bro
                ll u2l2r2b = dist[l][1] * a[l] + dp_br[l][1] + dp_br[r][j + 1];
                ll u2r2l2b = dist[r][1] * a[r] + dp_br[r][1] + dp_br[l][j + 1];
                dp_br[i][j] = min({dp_br[i][j], u2l2r2b, u2r2l2b});
            }
        }
    }
    ll ans = LONG_LONG_MAX;
    for (int i = 1; i <= n; i++) {
        // 从i开始，一层层往上叠加，兄弟直接加，爸爸要算
        ll cost = dp_fa[i][1];// 从i走到i的父节点
        int last = i;
        for (int p = pa(i); p >= 1; p = pa(p)) {
            int bro_of_last = br(last);
            if (bro_of_last <= n) { // last有兄弟
                // 从p走到bro_of_last，再从bro_of_last走到爷爷
                cost += dist[bro_of_last][1] * a[bro_of_last] + dp_fa[bro_of_last][2];
            } else {
                // 从p到他爷爷
                cost += dist[p][1] * a[pa(p)];
            }
            last = p;
        }
        ans = min(ans, cost);
    }
    cout << ans << endl;
    return 0;
}