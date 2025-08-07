#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> A(n + 1, vector<int>(m + 1, 0)); // [0][j]和[i][0]正好存有几个数
    // 能全填的就一种情况，存在两行全填
    vector<tuple<int, int, int>> ans;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> A[i][j];
            if (A[i][j] > 0) {
                A[i][0]++;
                A[0][j]++;
            }
        }
    }
    // 先扫一次行和列
    auto fill_row = [&](int i) {
        if (A[i][0] < 2)
            return 0;

        int res = 0;
        int prev_j = 0, prev_val = 0;
        int diff = 0, start = 0;
        for (int j = 1; j <= m; j++) {
            if (A[i][j] > 0) {
                if (prev_j == 0) {
                    prev_j = j;
                    prev_val = A[i][j];
                } else {
                    diff = (A[i][j] - prev_val) / (j - prev_j);
                    start = (A[i][j] - diff * (j - 1));
                    break;
                }
            }
        }
        for (int j = 1; j <= m; j++) {
            if (A[i][j] == 0) {
                A[i][j] = start + diff * (j - 1);
                A[i][0]++;
                A[0][j]++;
                ans.push_back({i, j, A[i][j]});
                res++;
            }
        }
        return res;
    };

    auto fill_col = [&](int j) {
        if (A[0][j] < 2)
            return 0;
        int res = 0;
        int prev_i = 0, prev_val = 0;
        int diff = 0, start = 0;
        for (int i = 1; i <= n; i++) {
            if (A[i][j] > 0) {
                if (prev_i == 0) {
                    prev_i = i;
                    prev_val = A[i][j];
                } else {
                    diff = (A[i][j] - prev_val) / (i - prev_i);
                    start = (A[i][j] - diff * (i - 1));
                    break;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            if (A[i][j] == 0) {
                A[i][j] = start + diff * (i - 1);
                A[0][j]++;
                A[i][0]++;
                ans.push_back({i, j, A[i][j]});
                res++;
            }
        }
        return res;
    };
    // while (true) {
    //     int cnt = 0;
    //     for (int i = 1; i <= n; i++) {
    //         cnt += fill_row(i);
    //     }
    //     for (int j = 1; j <= m; j++) {
    //         cnt += fill_col(j);
    //     }
    //     if (cnt == 0) break;
    // } 其实只要扫两遍就行，不用while
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += fill_row(i);
    }
    for (int j = 1; j <= m; j++) {
        cnt += fill_col(j);
    }
    for (int i = 1; i <= n; i++) {
        cnt += fill_row(i);
    }
    for (int j = 1; j <= m; j++) {
        cnt += fill_col(j);
    }
    sort(ans.begin(), ans.end());
    for (const auto &[i, j, val] : ans) {
        cout << i << " " << j << " " << val << endl;
    }
    return 0;
}