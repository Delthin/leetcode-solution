#include <bits/stdc++.h>
using namespace std;
using ll = long long;
bool is_prime(ll n) {
    if (n < 2) return false;
    // 优化：i <= x / i 等价于 i*i <= x，避免了乘法溢出和sqrt函数调用
    for (ll i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ll x;
    cin >> x;
    for (int i = 0; ;i++) {
        x *= 10;
        ll start = pow(10, i);
        ll end = pow(10, i + 1);
        for (ll j = start; j < end; j++) {
            if (is_prime(x + j)) {
                cout << x + j << endl;
                return 0;
            }
        }
    }
    return 0;
}