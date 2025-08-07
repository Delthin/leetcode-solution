#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll contain_k(int i, int k) {
    ll res = 0;
    while (i > 0) {
        if (k == (i % 10)) res++;
        i /= 10;
    }
    return res;
}

int main() {
    int n, k;
    cin >> n >> k;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += contain_k(i, k);
    }
    cout << ans << endl;
    return 0;
}