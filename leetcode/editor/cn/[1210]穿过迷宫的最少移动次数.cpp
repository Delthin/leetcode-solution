//你还记得那条风靡全球的贪吃蛇吗？ 
//
// 我们在一个 n*n 的网格上构建了新的迷宫地图，蛇的长度为 2，也就是说它会占去两个单元格。蛇会从左上角（(0, 0) 和 (0, 1)）开始移动。我们用
// 0 表示空单元格，用 1 表示障碍物。蛇需要移动到迷宫的右下角（(n-1, n-2) 和 (n-1, n-1)）。 
//
// 每次移动，蛇可以这样走： 
//
// 
// 如果没有障碍，则向右移动一个单元格。并仍然保持身体的水平／竖直状态。 
// 如果没有障碍，则向下移动一个单元格。并仍然保持身体的水平／竖直状态。 
// 如果它处于水平状态并且其下面的两个单元都是空的，就顺时针旋转 90 度。蛇从（(r, c)、(r, c+1)）移动到 （(r, c)、(r+1, c)）。
// 
// 如果它处于竖直状态并且其右面的两个单元都是空的，就逆时针旋转 90 度。蛇从（(r, c)、(r+1, c)）移动到（(r, c)、(r, c+1)）。 
//
// 
//
// 返回蛇抵达目的地所需的最少移动次数。 
//
// 如果无法到达目的地，请返回 -1。 
//
// 
//
// 示例 1： 
//
// 
//
// 输入：grid = [[0,0,0,0,0,1],
//               [1,1,0,0,1,0],
//               [0,0,0,0,1,1],
//               [0,0,1,0,1,0],
//               [0,1,1,0,0,0],
//               [0,1,1,0,0,0]]
//输出：11
//解释：
//一种可能的解决方案是 [右, 右, 顺时针旋转, 右, 下, 下, 下, 下, 逆时针旋转, 右, 下]。
// 
//
// 示例 2： 
//
// 输入：grid = [[0,0,1,1,1,1],
//               [0,0,0,0,1,1],
//               [1,1,0,0,0,1],
//               [1,1,1,0,0,1],
//               [1,1,1,0,0,1],
//               [1,1,1,0,0,0]]
//输出：9
// 
//
// 
//
// 提示： 
//
// 
// 2 <= n <= 100 
// 0 <= grid[i][j] <= 1 
// 蛇保证从空单元格开始出发。 
// 
//
// Related Topics 广度优先搜索 数组 矩阵 👍 157 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution1210{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    const int DIR[2][2] = { {0, 1}, {1, 0}};

    bool inArea(vector<vector<int>>& g, int x, int y) {
        return x >= 0 && x < g.size() && y >= 0 && y < g[0].size();
    }
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int n = grid.size();
        queue<tuple<int, int, int>> q; // 0表示横着
        vector<vector<vector<bool>>> vis(n, (vector<vector<bool>>(n,vector<bool>(2, false))));

        q.emplace(0, 0, 0);
        vis[0][0][0] = true;

        for (int step = 0; !q.empty(); step++) {
            int size = q.size();
            for (int _ = 0; _ < size; _++) {
                auto [x, y, s] = q.front();
                q.pop();
                if (x == n - 1 && y == n - 2 && s == 0) return step;

                // 不改s
                for (auto& [dx, dy]: DIR) {
                    int nx = x + dx, ny = y + dy;
                    int fx = nx, fy = ny;
                    if (dx == s) {
                        // 移动和朝向同向
                        fx += dx;
                        fy += dy;
                    } else if (dy == s) {
                        // 移动和朝向不同
                        // s = 0, dy = 0, dx = 1
                        fx += dy;
                        fy += dx;
                    }
                    if (inArea(grid, nx, ny) && inArea(grid, fx, fy) && grid[nx][ny] == 0 && grid[fx][fy] == 0 && !vis[nx][ny][s]) {
                        q.emplace(nx, ny, s);
                        vis[nx][ny][s] = true;
                    }
                }
                // 改s
                int fx = x, fy = y;
                int ffx = x + 1, ffy = y + 1;
                if (s == 0) {
                    fx += 1;
                } else {
                    fy += 1;
                }

                // 检查两个单元格！！！
                if (inArea(grid, fx, fy) && grid[fx][fy] == 0 && !vis[x][y][!s]
                     && inArea(grid, ffx, ffy) && grid[ffx][ffy] == 0) {
                    q.emplace(x, y, !s);
                    vis[x][y][!s] = true;
                }
            }
        }
        return -1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1210;
int main() {
    Solution solution;

    return 0;
}