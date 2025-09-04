#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
vector<ll> ori_a;
vector<ll> ori_b;

int cartesian_tree(const vector<ll>& a, vector<int>& lc, vector<int>& rc) {
    // 大根堆笛卡尔树
    vector<int> st;
    for (int i = 1; i <= n; i++) {
        int last_pop = 0;
        // 如果是小根堆，这里改成大于号
        while (!st.empty() && a[st.back()] < a[i]) {
            last_pop = st.back();
            st.pop_back();
        }
        if (last_pop > 0) {
            lc[i] = last_pop;
        }
        if (!st.empty()) {
            rc[st.back()] = i;
        }
        st.push_back(i);
    }
    return st.empty() ? 0 : st[0];
}

void solve() {
    int k;
    cin >> k;
    vector<ll> a = ori_a;
    vector<ll> b = ori_b;
    while (k--) {
        int i, a_i, b_i;
        cin >> i >> a_i >> b_i;
        a[i] = a_i;
        b[i] = b_i;
    }
    vector<ll> sum(n + 1);// 前缀和，方便计算区间子树的和
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + b[i];
    }
    vector<int> lc(n + 1);
    vector<int> rc(n + 1);
    int root = cartesian_tree(a, lc, rc);
    vector<ll> f(n + 1);// 从i出发所需的最小攻击力
    function<void(int, int, int, ll)> dfs = [&](int u, int l, int r, ll cur) {
        // cur表示需要满足父节点及以上的最小攻击力
        if (u == 0 || l > r) {
            return;
        }
        f[u] = max(a[u], cur);
        if (l == r) return;// 叶子节点
        dfs(lc[u], l, u - 1, max(cur, a[u] - (sum[u - 1] - sum[l - 1])));
        dfs(rc[u], u + 1, r, max(cur, a[u] - (sum[r] - sum[u])));
    };
    dfs(root, 1, n, 0);
    ll ans = 0;
    for (int i = 1; i <= n - 1; i++) {
        ll cur = min(f[i], f[i + 1]);
        ans = ans ^ cur;
    }
    cout << ans << endl;
}

void solve1() {
    int k;
    cin >> k;
    vector<ll> a = ori_a;
    vector<ll> b = ori_b;
    while (k--) {
        int i, a_i, b_i;
        cin >> i >> a_i >> b_i;
        a[i] = a_i;
        b[i] = b_i;
    }
    ll ans = 0;
    for (int i = 1; i <= n - 1; i++) {
        int l = i;
        int r = i + 1;
        ll p = 0;// 需要的开局攻击力
        ll cur = 0;// 目前的攻击力
        while (l >= 1 && r <= n) {
            // 贪心选两边小的那个
            int j = l;
            ll need = a[j];
            if (a[r] < a[j]) {
                j = r;
                need = a[j];
            }
            if (cur < need) {
                p += need - cur;
                cur = need;
            }
            cur += b[j];
            if (j == l) {
                l--;
            } else {
                r++;
            }
        }
        while (l >= 1) {
            ll need = a[l];
            if (cur < need) {
                p += need - cur;
                cur = need;
            }
            cur += b[l];
            l--;
        }
        while (r <= n) {
            ll need = a[r];
            if (cur < need) {
                p += need - cur;
                cur = need;
            }
            cur += b[r];
            r++;
        }
        ans = ans ^ p;
    }
    cout << ans << endl;
}

int main() {
    cin >> n;
    ori_a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ori_a[i];
    }
    ori_b.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ori_b[i];
    }
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}



