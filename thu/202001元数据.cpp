#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> ans(n + 1, 0);
    while (m--) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'A') {
            ans[x] = min((ll)1e9, (ll)ans[x] + y);
        } else {
            ans[x] = max(0, ans[x] - y);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << '\n';
    }
}
