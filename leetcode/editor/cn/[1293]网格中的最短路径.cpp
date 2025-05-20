//给你一个 m * n 的网格，其中每个单元格不是 0（空）就是 1（障碍物）。每一步，您都可以在空白单元格中上、下、左、右移动。 
//
// 如果您 最多 可以消除 k 个障碍物，请找出从左上角 (0, 0) 到右下角 (m-1, n-1) 的最短路径，并返回通过该路径所需的步数。如果找不到这样
//的路径，则返回 -1 。 
//
// 
//
// 示例 1： 
//
// 
//
// 
//输入： grid = [[0,0,0],[1,1,0],[0,0,0],[0,1,1],[0,0,0]], k = 1
//输出：6
//解释：
//不消除任何障碍的最短路径是 10。
//消除位置 (3,2) 处的障碍后，最短路径是 6 。该路径是 (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3
//,2) -> (4,2).
// 
//
// 示例 2： 
//
// 
//
// 
//输入：grid = [[0,1,1],[1,1,1],[1,0,0]], k = 1
//输出：-1
//解释：我们至少需要消除两个障碍才能找到这样的路径。
// 
//
// 
//
// 提示： 
//
// 
// grid.length == m 
// grid[0].length == n 
// 1 <= m, n <= 40 
// 1 <= k <= m*n 
// grid[i][j] 是 0 或 1 
// grid[0][0] == grid[m-1][n-1] == 0 
// 
//
// Related Topics 广度优先搜索 数组 矩阵 👍 293 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution1293{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    const int DIR[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    bool inArea(vector<vector<int>>& g, int x, int y) {
        return x >= 0 && x < g.size() && y >= 0 && y < g[0].size();
    }
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q1;
        queue<pair<int, int>> q2;
        vector<vector<bool>> vis(m, (vector<bool>(n, false)));
        vector<vector<int>> dis(m, (vector<int>(n, INT_MAX)));

        // 第一轮，从起点往障碍边界遍历
        q1.emplace(0, 0);
        vis[0][0] = true;
        dis[0][0] = 0;
        while (!q1.empty()) {
            auto [x, y] = q1.front();
            q1.pop();
            if (grid[x][y] == 1) {
                q2.emplace(x, y);
                continue;
            }
            for (auto& [dx, dy]: DIR) {
                int nx = x + dx, ny = y + dy;
                if (inArea(grid, nx, ny) && vis[nx][ny] == false) {
                    q1.emplace(nx, ny);
                    vis[nx][ny] = true;
                    dis[nx][ny] = dis[x][y] + 1;
                }
            }
        }

        return
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1293;
int main() {
    Solution solution;

    return 0;
}