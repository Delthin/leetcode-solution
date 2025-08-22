#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dp(n + 1, 1);// dp记录以u为根的子树的最大链长
    int ans = 0;// ans记录经过u的最大毛毛虫长度
    function<void(int, int)> dfs = [&] (int u, int p) {
        dp[u] = adj[u].size();
        int max1 = 0;
        int max2 = 0;
        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }
            dfs(v, u);
            if (dp[v] > max1) {
                max2 = max1;
                max1 = dp[v];
            } else if (dp[v] > max2) {
                max2 = dp[v];
            }
        }
        dp[u] += max(1, max1) - 1;
        int cur_ans = max1 + max2 + adj[u].size() + 1;
        // 这里只计算u和u的子树，因为如果经过根节点，必然会在顶层递归到
        if (max1 != 0) {
            cur_ans--;
        }
        if (max2 != 0) {
            cur_ans--;
        }
        ans = max(ans, cur_ans);
    };
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}
