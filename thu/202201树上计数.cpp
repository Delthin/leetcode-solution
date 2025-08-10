#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, L, R;
    cin >> n >> L >> R;
    vector<vector<int>> adj(n + 1);
    for (int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        adj[fa].emplace_back(i);
    }
    int ans = 0;
    function<int(int)> dfs = [&] (int i) {
        if (adj[i].empty()) return 1;
        int res = 1;
        for (auto v: adj[i]) {
            res += dfs(v);
        }
        if (res >= L && res <= R) {
            ans++;
        }
        return res;
    };
    dfs(1);
    cout << ans << endl;
    return 0;
}