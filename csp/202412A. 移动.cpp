#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    const int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    unordered_map<char, int> mp = {{'f', 0}, {'b', 1}, {'l', 2}, {'r', 3}};
    while (k--) {
        int x, y;
        cin >> x >> y;
        string s;
        cin >> s;
        for (int i = 0; i < s.size(); i++) {
            int d = mp[s[i]];
            int nx = x + dir[d][0];
            int ny = y + dir[d][1];
            if (nx < 1 || nx > n || ny < 1 || ny > n) {
                continue;
            }
            x = nx;
            y = ny;
        }
        cout << x << " " << y << endl;
    }
    return 0;
}