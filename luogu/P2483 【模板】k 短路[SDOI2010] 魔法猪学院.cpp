#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, m, e;
    cin >> n >> m >> e;
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<vector<pair<int, int>>> adj_rev(n + 1);
    for (int i = 0; i < m; i++) {
        int s, t, e;
        cin >> s >> t >> e;
        adj[s].emplace_back(t, e);
        adj_rev[t].emplace_back(s, e);
    }
}