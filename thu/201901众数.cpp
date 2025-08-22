//
// Created by lisiyi on 25-8-13.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> cnt(m, vector<int>(10, 0));
    while (n--) {
        int x;
        cin >> x;
        for (int i = 0; i < m; i++) {
            if (x == 0) break;
            cnt[i][x % 10]++;
            x /= 10;
        }
    }
    for (int i = 0; i < m; i++) {
        int max_cnt = cnt[i][0];
        int max_num = 0;
        for (int j = 1; j < 10; j++) {
            if (cnt[i][j] > max_cnt) {
                max_cnt = cnt[i][j];
                max_num = j;
            }
        }
        cout << max_num << endl;
    }
    return 0;
}