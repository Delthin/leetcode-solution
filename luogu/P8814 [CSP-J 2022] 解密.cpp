#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll k;
    cin >> k;
    while (k --) {
        ll n, e, d;
        cin >> n >> e >> d;
        if (e == 1 && d == 1) {
            cout << 1 << " " << n << endl;
            continue;
        }
        ll sum = n - e * d + 2;
        if (sum <= 1) {
            cout << "NO" << endl;
            continue;
        }
        ll product = n;
        // 解方程 a^2 - a*sum + n = 0,
        ll delta = sum * sum - 4 * product;
        if (delta < 0) {
            cout << "NO" << endl;
            continue;
        }
        ll a = (sum - sqrt(delta)) / 2;
        if (a == 1 && (e!=1 || d != 1)) {
            cout << "NO" << endl;
            continue;
        }
        ll b = n / a;
        if (a <= 0 || a * b != n || a + b != sum) {
            cout << "NO" << endl;
            continue;
        }
        cout << a << " " << b << endl;
    }
    return 0;
}