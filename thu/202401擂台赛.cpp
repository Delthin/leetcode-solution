//
// Created by lisiyi on 25-8-2.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// 17:06 ->
int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n, vector<int>(n, 0));
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            cin >> adj[i][j];
        }
    }
    auto get_winner = [&](int i, int j) {
        if (adj[i][j] == 1) return i;
        else return j;
    };
    vector<int> permutation(n, 0);
    iota(permutation.begin(), permutation.end(), 0);
    int ans = 0;
    function<int(int l, int r)> dfs = [&] (int l, int r) {
        if (l == r - 1) return get_winner(permutation[l], permutation[r]);
        int mid = l + (r - l) / 2;
        return get_winner(dfs(l, mid), dfs(mid + 1, r));
    };
    do {
        ans += dfs(0, n - 1) == 0;
    }
    while (next_permutation(permutation.begin(), permutation.end()));
    cout << ans / (pow(2, n / 2)) << endl;
    return 0;
}