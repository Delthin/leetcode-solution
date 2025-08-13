// 卡常数80，不管了
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<int>> adj;
vector<int> a;
vector<int> ans;
vector<int> cnt;
int now = 0;

void dfs(int u, int p) {
    if (cnt[a[u]] == 0) {
        now++;
    }
    cnt[a[u]]++;
    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        dfs(v, u);
    }
    ans[u] = now;
    cnt[a[u]]--;
    if (cnt[a[u]] == 0) {
        now--;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    scanf("%d", &n);
    adj.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    a.resize(n + 1);
    vector<int> vals;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        vals.push_back(a[i]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int total = vals.size();
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
    }
    cnt.resize(total, 0);
    ans.resize(n + 1, 0);
    dfs(n, 0);
    for (int i = 1; i <= n; i++) {
        printf("%d%c", ans[i], " \n"[i == n]);
    }
    return 0;
}
