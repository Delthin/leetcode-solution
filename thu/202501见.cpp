//
// Created by lisiyi on 25-8-3.
//
#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& line) {
    int n = line.size();
    int max_h = 0;
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (line[i] > max_h) {
            res++;
            max_h = line[i];
        }
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    // 转化为求每行每列的最长上升子序列长度，在n为100时复杂度为4*n*nlogn
    vector<vector<int>> grid(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        vector<int> line = grid[i];
        int l_i = solve(line);
        reverse(line.begin(), line.end());
        int r_i = solve(line);
        vector<int> col;
        for (int j = 0; j < n; j++) {
            col.push_back(grid[j][i]);
        }
        int u_i = solve(col);
        reverse(col.begin(), col.end());
        int d_i = solve(col);
        cout << l_i << " " << r_i << " " << u_i << " " << d_i << endl;
    }
    return 0;
}
