#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first < b.first;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                pq.emplace(grid[i][j], i);
            }
        }
        long long ret = 0 ;
        for (int i = 0; i < k; i++) {
            auto [num, row] = pq.top();
            if (limits[row] == 0) {
                pq.pop();
                i--;
            } else {
                limits[row]--;
                ret += num;
                pq.pop();
            }
        }
        return ret;
    }
};
