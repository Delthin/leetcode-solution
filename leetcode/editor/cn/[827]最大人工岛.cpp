//给你一个大小为 n x n 二进制矩阵 grid 。最多 只能将一格 0 变成 1 。 
//
// 返回执行此操作后，grid 中最大的岛屿面积是多少？ 
//
// 岛屿 由一组上、下、左、右四个方向相连的 1 形成。 
//
// 
//
// 示例 1: 
//
// 
//输入: grid = [[1, 0], [0, 1]]
//输出: 3
//解释: 将一格0变成1，最终连通两个小岛得到面积为 3 的岛屿。
// 
//
// 示例 2: 
//
// 
//输入: grid = [[1, 1], [1, 0]]
//输出: 4
//解释: 将一格0变成1，岛屿的面积扩大为 4。 
//
// 示例 3: 
//
// 
//输入: grid = [[1, 1], [1, 1]]
//输出: 4
//解释: 没有0可以让我们变成1，面积依然为 4。 
//
// 
//
// 提示： 
//
// 
// n == grid.length 
// n == grid[i].length 
// 1 <= n <= 500 
// grid[i][j] 为 0 或 1 
// 
//
// Related Topics 深度优先搜索 广度优先搜索 并查集 数组 矩阵 👍 455 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution827{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    const int DIR[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    bool inArea(vector<vector<int>>& g, int x, int y) {
        return x >= 0 && x < g.size() && y >= 0 && y < g[0].size();
    }

    int dfs(vector<vector<int>>& grid,vector<vector<int>>& vis,int idx, int x, int y) {

        int ret = grid[x][y];
        vis[x][y] = idx;

        for (auto &[dx, dy] : DIR) {
            int nx = x + dx, ny = y + dy;
            if (inArea(grid, nx, ny) && grid[nx][ny] != 0 && !vis[nx][ny]) {
                ret += dfs(grid,vis, idx, nx, ny);
            }
        }
        return ret;
    }
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int ans = 0;
        // vis充当并查集
        vector<vector<int>> vis(n, vector<int>(n, 0));
        // 记录每个idx岛的大小
        vector<int> island = {0};
        int idx = 1;
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && vis[i][j] == 0) {
                    int s = dfs(grid, vis, idx++, i, j);
                    island.emplace_back(s);
                    ans = max(ans, s);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    int sum = 1;
                    unordered_set<int> idxs;
                    for (auto &[dx, dy] : DIR) {
                        int nx = i + dx, ny = j + dy;
                        if (inArea(grid, nx, ny) && grid[nx][ny] != 0 && !idxs.count(vis[nx][ny])) {
                            int id = vis[nx][ny];
                            sum += island[id];
                            idxs.insert(id);
                        }
                    }
                    ans = max(ans, sum);
                }
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution827;
int main() {
    Solution solution;
    vector<vector<int>> grid = {{1, 1}, {1, 0}};
    solution.largestIsland(grid);
    return 0;
}