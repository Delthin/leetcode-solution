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
    struct state {
        int x;
        int y;
        int k;
        state(int _x, int _y, int _k) : x(_x), y(_y), k(_k){
        }
    };
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        queue<state> q;
        vector<vector<vector<bool>>> vis(m, (vector<vector<bool>>(n,vector<bool>(k + 1, false))));

        q.emplace(0, 0, 0);
        vis[0][0][0] = true;
        for (int step = 0; !q.empty(); step++) {
            int size = q.size();
            for (int _ = 0; _ < size; _++) {
                auto [x, y, rest] = q.front();
                q.pop();
                if (x == m - 1 && y == n - 1) return step;

                for (auto& [dx, dy]: DIR) {
                    int nx = x + dx, ny = y + dy;
                    if (inArea(grid, nx, ny)) {
                        if (grid[nx][ny] == 0 && !vis[nx][ny][rest]) {
                            q.emplace(nx, ny, rest);
                            vis[nx][ny][rest] = true;
                        } else if (grid[nx][ny] == 1 && rest < k && !vis[nx][ny][rest + 1]){
                            q.emplace(nx, ny, rest + 1);
                            vis[nx][ny][rest + 1] = true;
                        }
                    }
                }
            }
        }
        return -1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1293;
int main() {
    Solution solution;

    return 0;
}