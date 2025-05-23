//给你一个 m x n 的二进制矩形 grid 和一个整数 health 表示你的健康值。 
//
// 你开始于矩形的左上角 (0, 0) ，你的目标是矩形的右下角 (m - 1, n - 1) 。 
//
// 你可以在矩形中往上下左右相邻格子移动，但前提是你的健康值始终是 正数 。 
//
// 对于格子 (i, j) ，如果 grid[i][j] = 1 ，那么这个格子视为 不安全 的，会使你的健康值减少 1 。 
//
// 如果你可以到达最终的格子，请你返回 true ，否则返回 false 。 
//
// 注意 ，当你在最终格子的时候，你的健康值也必须为 正数 。 
//
// 
//
// 示例 1： 
//
// 
// 输入：grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1 
// 
//
// 输出：true 
//
// 解释： 
//
// 沿着下图中灰色格子走，可以安全到达最终的格子。 
//
//
// 示例 2： 
//
// 
// 输入：grid = [[0,1,1,0,0,0],[1,0,1,0,0,0],[0,1,1,1,0,1],[0,0,1,0,1,0]], health =
// 3 
// 
//
// 输出：false 
//
// 解释： 
//
// 健康值最少为 4 才能安全到达最后的格子。 
//
//
// 示例 3： 
//
// 
// 输入：grid = [[1,1,1],[1,0,1],[1,1,1]], health = 5 
// 
//
// 输出：true 
//
// 解释： 
//
// 沿着下图中灰色格子走，可以安全到达最终的格子。 
//
// 
//
// 任何不经过格子 (1, 1) 的路径都是不安全的，因为你的健康值到达最终格子时，都会小于等于 0 。 
//
// 
//
// 提示： 
//
// 
// m == grid.length 
// n == grid[i].length 
// 1 <= m, n <= 50 
// 2 <= m * n 
// 1 <= health <= m + n 
// grid[i][j] 要么是 0 ，要么是 1 。 
// 
//
// Related Topics 广度优先搜索 图 数组 矩阵 最短路 堆（优先队列） 👍 11 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution3286{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    const int DIR[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    bool inArea(vector<vector<int>>& g, int x, int y) {
        return x >= 0 && x < g.size() && y >= 0 && y < g[0].size();
    }
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();
        deque<pair<int, int>> q;
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        q.emplace_back(0, 0);
        dist[0][0] = grid[0][0] == 1;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop_front();
            if (x == m - 1 && y == n - 1) break;
            for (int k = 0; k < 4; k++) {
                int nx = x + DIR[k][0], ny = y + DIR[k][1];
                if (inArea(grid, nx, ny)) {
                    int nd = dist[x][y] + (grid[nx][ny] == 1);
                    if (nd < health && nd < dist[nx][ny]) {
                        dist[nx][ny] = nd;
                        if (grid[nx][ny] == 0) q.emplace_front(nx, ny);
                        else q.emplace_back(nx, ny);
                    }
                }
            }
        }
        return dist[m - 1][n - 1] < health;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3286;
int main() {
    Solution solution;

    return 0;
}