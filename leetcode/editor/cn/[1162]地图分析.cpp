//你现在手里有一份大小为
// n x n 的 网格 grid，上面的每个 单元格 都用 0 和 1 标记好了。其中 0 代表海洋，1 代表陆地。 
//
// 请你找出一个海洋单元格，这个海洋单元格到离它最近的陆地单元格的距离是最大的，并返回该距离。如果网格上只有陆地或者海洋，请返回 -1。 
//
// 我们这里说的距离是「曼哈顿距离」（ Manhattan Distance）：(x0, y0) 和 (x1, y1) 这两个单元格之间的距离是 |x0 - 
//x1| + |y0 - y1| 。 
//
// 
//
// 示例 1： 
//
// 
//
// 
//输入：grid = [[1,0,1],[0,0,0],[1,0,1]]
//输出：2
//解释： 
//海洋单元格 (1, 1) 和所有陆地单元格之间的距离都达到最大，最大距离为 2。
// 
//
// 示例 2： 
//
// 
//
// 
//输入：grid = [[1,0,0],[0,0,0],[0,0,0]]
//输出：4
//解释： 
//海洋单元格 (2, 2) 和所有陆地单元格之间的距离都达到最大，最大距离为 4。
// 
//
// 
//
// 提示： 
//
// 
// 
//
// 
// n == grid.length 
// n == grid[i].length 
// 1 <= n <= 100 
// grid[i][j] 不是 0 就是 1 
// 
//
// Related Topics 广度优先搜索 数组 动态规划 矩阵 👍 411 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution1162{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    const int DIR[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    bool inArea(vector<vector<int>>& g, int x, int y) {
        return x >= 0 && x < g.size() && y >= 0 && y < g[0].size();
    }
public:
    int maxDistance(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        vector<vector<bool>> vis(m, (vector<bool>(n, false)));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    q.emplace(i, j);
                }
            }
        }

        int step = -1;
        while (!q.empty()) {
            step++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                for (auto& [dx, dy]: DIR) {
                    int nx = x + dx, ny = y + dy;
                    if (inArea(grid, nx, ny) && grid[nx][ny] == 0 && vis[nx][ny] == false) {
                        q.emplace(nx, ny);
                        vis[nx][ny] = true;
                    }
                }
            }
        }

        return step <= 0 ? -1 : step;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1162;
int main() {
    Solution solution;

    return 0;
}