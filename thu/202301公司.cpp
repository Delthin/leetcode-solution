//
// Created by lisiyi on 25-8-2.
// 18:09->18:19
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    unordered_map<int, pair<int, double>> mp;
    while (m--) {
        int x, y;
        cin >> x >> y;
        if (mp.count(x)) {
            mp[x].first++;
            mp[x].second = (a[y] + mp[x].second * (mp[x].first - 1)) / mp[x].first;
        } else {
            mp[x].first = 1;
            mp[x].second = a[y];
        }
    }
    int ans = 0;
    for (const auto&[x, p]: mp) {
        if (p.second > a[x]) ans++;
    }
    cout << ans << endl;
    return 0;
}