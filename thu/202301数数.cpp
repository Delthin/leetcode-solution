// dp取模
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<ll> dp(3, 0);
        dp[0] = 3;
        dp[1] = 9;
        bool overflow = false;
        const ll MOD = (ll)1e16;
        for (int i = 2; i < n; i++) {
            dp[i % 3] = 2 * dp[(i + 2) % 3] + 2 * dp[(i + 1) % 3];
            if (dp[i % 3] >= MOD) {
                overflow = true;
            }
            dp[i % 3] %= (ll)MOD;
        }
        ll ans = dp[(n - 1) % 3];
        if (overflow) {
            ans = ans % (ll)1e10;
            cout << "......" << setfill('0') << setw(10) << ans << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}