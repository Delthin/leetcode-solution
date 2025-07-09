/**
给你一个 m x n 的整数网格图 grid ，你可以从一个格子移动到 4 个方向相邻的任意一个格子。 

 请你返回在网格图中从 任意 格子出发，达到 任意 格子，且路径中的数字是 严格递增 的路径数目。由于答案可能会很大，请将结果对 10⁹ + 7 取余 后返回。
 

 如果两条路径中访问过的格子不是完全相同的，那么它们视为两条不同的路径。 

 

 示例 1： 

 

 输入：grid = [[1,1],[3,4]]
输出：8
解释：严格递增路径包括：
- 长度为 1 的路径：[1]，[1]，[3]，[4] 。
- 长度为 2 的路径：[1 -> 3]，[1 -> 4]，[3 -> 4] 。
- 长度为 3 的路径：[1 -> 3 -> 4] 。
路径数目为 4 + 3 + 1 = 8 。
 

 示例 2： 

 输入：grid = [[1],[2]]
输出：3
解释：严格递增路径包括：
- 长度为 1 的路径：[1]，[2] 。
- 长度为 2 的路径：[1 -> 2] 。
路径数目为 2 + 1 = 3 。
 

 

 提示： 

 
 m == grid.length 
 n == grid[i].length 
 1 <= m, n <= 1000 
 1 <= m * n <= 10⁵ 
 1 <= grid[i][j] <= 10⁵ 
 

 Related Topics 深度优先搜索 广度优先搜索 图 拓扑排序 记忆化搜索 数组 动态规划 矩阵 👍 66 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2328{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int countPaths(vector<vector<int>>& grid) {
        using ll = long long;
        int m = grid.size();
        int n = grid[0].size();
        const int MOD = 1e9 + 7;
        // dp[i][j] 表示从 (i, j) 出发的严格递增路径数目
        vector<vector<ll>> dp(m, vector<ll>(n, 1));
        // 记录每个格子的坐标
        vector<pair<int, int>> cells;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cells.emplace_back(i, j);
            }
        }
        // 按照 grid[i][j] 的值进行排序
        sort(cells.begin(), cells.end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
            return grid[a.first][a.second] < grid[b.first][b.second];
        });
        // 四个方向的偏移量
        vector<int> dx = {0, 0, -1, 1};
        vector<int> dy = {-1, 1, 0, 0};
        ll totalPaths = 0;
        for (const auto& cell : cells) {
            int x = cell.first;
            int y = cell.second;
            // 遍历四个方向
            for (int d = 0; d < 4; ++d) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                // 检查边界和严格递增条件
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] > grid[x][y]) {
                    dp[nx][ny] = (dp[nx][ny] + dp[x][y]) % MOD;
                }
            }
            totalPaths = (totalPaths + dp[x][y]) % MOD;
        }
        return totalPaths;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2328;
int main() {
    Solution solution;

    return 0;
}