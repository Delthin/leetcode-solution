//
// Created by lisiyi on 25-8-4.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        int ans = 0;
        vector<string> a(n);
        int need_row = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            bool need = false;
            for (int j = 0; j < m; j++) {
                if (a[i][j] == '1') {
                    need = need ^ true;
                }
            }
            need_row += need;
        }
        int need_col = 0;
        for (int j = 0; j < m; j++) {
            bool need = false;
            for (int i = 0; i < n; i++) {
                if (a[i][j] == '1') {
                    need = need ^ true;
                }
            }
            need_col += need;
        }
        ans = max(need_col, need_row);
        cout << ans << endl;
    }
    return 0;
}