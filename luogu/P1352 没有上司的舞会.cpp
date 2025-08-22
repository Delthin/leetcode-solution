
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;

int main() {
    cin >> n;
    vector<int> happy(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> happy[i];
    }
    vector<vector<int>> adj(n + 1);
    vector<bool> has_father(n + 1, false);
    for (int i = 0; i < n - 1; i++) {
        int l, k;
        cin >> l >> k;
        adj[k].push_back(l);
        has_father[l] = true;
    }
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    function<void(int)> dfs = [&](int u) {
        dp[u][1] = happy[u];// 选u
        for (int v :adj[u]) {
            dfs(v);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    };
    int root = 1;
    while (has_father[root]) {
        root++;
    }
    dfs(root);
    cout << max(dp[root][0], dp[root][1]) << endl;
    return 0;
}