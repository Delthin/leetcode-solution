// 暴力
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1, 0);
    for (int i =1; i<=n; i++) {
        cin >> a[i];
    }
    vector<bool> in(n + 1, false);
    ll now = 0;
    auto change = [&] (int x, bool add) {
        ll ans = 0;
        if (add) {
            // 新加入，判断和每个已有的数是否互质
            for (int i = 1; i <= n; i++) {
                if (in[i] && gcd(a[i], a[x]) == 1) {
                    ans++;
                }
            }
        } else {
            // 删除
            for (int i = 1; i <= n; i++) {
                if (in[i] && gcd(a[i], a[x]) == 1 && i != x) {
                    ans--;
                }
            }
        }
        now += ans;
    };
    while (q--) {
        int x;
        cin >> x;
        if (in[x]) {
            // 删除
            change(x, false);
        } else {
            change(x, true);
        }
        in[x] = !in[x];
        cout << now << '\n';
    }
}