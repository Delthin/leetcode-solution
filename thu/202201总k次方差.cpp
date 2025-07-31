#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    long long ans = 0;
    const int MOD = 998244353;
    for (int i = n - 1, j = n - 1; i >= 0; --i, j-=2) {
        ans = (ans + a[i] * j % MOD) % MOD;
    }
    ans = (ans+ MOD) * 2 % MOD;
    cout << ans << endl;
    return 0;
}
