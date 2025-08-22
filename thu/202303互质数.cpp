// 求互质->求不互质->容斥原理
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

const int N = 500005;
bool is_composite[N];       // is_composite[x] 标记x是否为合数
int factor[N + 10][7];// 存每个数的质因子
int fcnt[N + 10];// 每个数的质因子数量
void get_primes() {
    for (int i = 2; i <= N; i++) {
        if (is_composite[i]) {
            continue;
        }
        factor[i][fcnt[i]] = i;
        fcnt[i]++;
        for (int j = i + i; j <= N; j += i) {
            is_composite[j] = true;
            factor[j][fcnt[j]] = i;
            fcnt[j]++;
        }
    }
}

int divided_cnt[N];// 集合内有多少数整除i，其中i的质因子各不相同

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<bool> in(n + 1, false);
    get_primes();
    ll total = 0;
    auto query = [&] (int x) {
        // x不在集合内的情况下，有多少数和x互质
        int lim = 1 << fcnt[x];
        int ret = 0;
        for (int s = 0; s < lim; s++) {
            int cur = 1, popcount = 0;
            for (int j = 0; j < fcnt[x]; j++) {
                if (s >> j & 1) {
                    cur *= factor[x][j];
                    popcount++;
                }
            }
            // 对于6，1的倍数-2的倍数-3的倍数+6的倍数，奇数个因数减，偶数个因数加
            ret += (popcount & 1 ? -1 : 1) * divided_cnt[cur];
        }
        return ret;
    };
    auto change = [&] (int i, bool add) {
        int x = a[i];
        ll ans = 0;
        if (add) {
            ans = query(x);
        }
        int lim = 1 << fcnt[x];
        for (int s = 0; s < lim; s++) {
            int cur = 1;
            for (int j = 0; j < fcnt[x]; j++) {
                if (s >> j & 1) {
                    cur *= factor[x][j];
                }
            }
            divided_cnt[cur] += (add ? 1 : -1);
        }
        in[i] = add;
        if (!add) {
            ans = -query(x);
        }
        return ans;
    };
    while (q--) {
        int i;
        cin >> i;
        total += change(i, !in[i]);
        cout << total << '\n';
    }
}