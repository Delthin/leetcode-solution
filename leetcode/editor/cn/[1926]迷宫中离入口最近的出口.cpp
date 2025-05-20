//给你一个 m x n 的迷宫矩阵 maze （下标从 0 开始），矩阵中有空格子（用 '.' 表示）和墙（用 '+' 表示）。同时给你迷宫的入口 
//entrance ，用 entrance = [entrancerow, entrancecol] 表示你一开始所在格子的行和列。 
//
// 每一步操作，你可以往 上，下，左 或者 右 移动一个格子。你不能进入墙所在的格子，你也不能离开迷宫。你的目标是找到离 entrance 最近 的出口。出口
// 的含义是 maze 边界 上的 空格子。entrance 格子 不算 出口。 
//
// 请你返回从 entrance 到最近出口的最短路径的 步数 ，如果不存在这样的路径，请你返回 -1 。 
//
// 
//
// 示例 1： 
// 输入：maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance =
// [1,2]
//输出：1
//解释：总共有 3 个出口，分别位于 (1,0)，(0,2) 和 (2,3) 。
//一开始，你在入口格子 (1,2) 处。
//- 你可以往左移动 2 步到达 (1,0) 。
//- 你可以往上移动 1 步到达 (0,2) 。
//从入口处没法到达 (2,3) 。
//所以，最近的出口是 (0,2) ，距离为 1 步。
// 
//
// 示例 2： 
// 输入：maze = [["+","+","+"],[".",".","."],["+","+","+"]], entrance = [1,0]
//输出：2
//解释：迷宫中只有 1 个出口，在 (1,2) 处。
//(1,0) 不算出口，因为它是入口格子。
//初始时，你在入口与格子 (1,0) 处。
//- 你可以往右移动 2 步到达 (1,2) 处。
//所以，最近的出口为 (1,2) ，距离为 2 步。
// 
//
// 示例 3： 
// 输入：maze = [[".","+"]], entrance = [0,0]
//输出：-1
//解释：这个迷宫中没有出口。
// 
//
// 
//
// 提示： 
//
// 
// maze.length == m 
// maze[i].length == n 
// 1 <= m, n <= 100 
// maze[i][j] 要么是 '.' ，要么是 '+' 。 
// entrance.length == 2 
// 0 <= entrancerow < m 
// 0 <= entrancecol < n 
// entrance 一定是空格子。 
// 
//
// Related Topics 广度优先搜索 数组 矩阵 👍 125 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution1926{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    const int DIR[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    bool exit(vector<vector<char>>& g, int x, int y, int sx, int sy) {
        return (x==0 || x == g.size() - 1 || y == 0 || y == g[0].size() - 1) && !(sx == x && sy == y);
    }

    bool inArea(vector<vector<char>>& g, int x, int y) {
        return x >= 0 && x < g.size() && y >= 0 && y < g[0].size();
    }

    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size();
        int n = maze[0].size();
        queue<pair<int, int>> q;
        vector<vector<bool>> vis(m, (vector<bool>(n, false)));
        q.emplace(entrance[0], entrance[1]);
        vis[entrance[0]][entrance[1]] = true;
        int step = 0;
        bool f = false;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                if (exit(maze, x, y, entrance[0], entrance[1])) {
                    f = true;
                    break;
                };
                for (auto& [dx, dy]: DIR) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (inArea(maze, nx, ny) && maze[nx][ny] == '.' && vis[nx][ny] == false) {
                        q.emplace(nx, ny);
                        vis[nx][ny] = true;
                    }
                }
            }

            if (f) break;
            step++;
        }
        if (!f) return -1;
        return step;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1926;
int main() {
    Solution solution;
    vector<vector<char>> maze = {{'.','.'}};
    vector<int> entrance = {0, 1};
    solution.nearestExit(maze, entrance);
    return 0;
}