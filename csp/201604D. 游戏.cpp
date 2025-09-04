#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, m, t;
    cin >> n >> m >> t;
    const int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    queue<pair<int, int>> q;
    q.emplace(1, 1);
    map<pair<int, int>, pair<int, int>> mp;
    for (int i = 0; i < t; i++) {
        int r, c, a, b;
        cin >> r >> c >> a >> b;
        mp[{r, c}] = {a, b};
    }
    int ans = 0;
    while (!q.empty() && ans <= 400) {
        int s = q.size();
        vector<vector<bool>> vis(n + 1, vector<bool>(m + 1, false));
        for (int i = 0; i < s; i++) {
            auto [x, y] = q.front();
            q.pop();
            if (x == n && y == m) {
                cout << ans << endl;
                return 0;
            }
            for (auto d : dir) {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx < 1 || nx > n || ny < 1 || ny > m) {
                    continue;
                }
                if (vis[nx][ny]) {// 同一时间点防止重复访问
                    continue;
                }
                if (mp.count({nx, ny})) {
                    if (mp[{nx, ny}].first <= ans+1 && mp[{nx, ny}].second >= ans+1) {
                        continue;
                    }
                }
                vis[nx][ny] = true;
                q.emplace(nx, ny);
            }
        }
        ans++;
    }
    return 0;
}