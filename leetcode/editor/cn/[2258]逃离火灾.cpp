/**
给你一个下标从 0 开始大小为 m x n 的二维整数数组 grid ，它表示一个网格图。每个格子为下面 3 个值之一： 

 
 0 表示草地。 
 1 表示着火的格子。 
 2 表示一座墙，你跟火都不能通过这个格子。 
 

 一开始你在最左上角的格子 (0, 0) ，你想要到达最右下角的安全屋格子 (m - 1, n - 1) 。每一分钟，你可以移动到 相邻 的草地格子。每次你移动
 之后 ，着火的格子会扩散到所有不是墙的 相邻 格子。 

 请你返回你在初始位置可以停留的 最多 分钟数，且停留完这段时间后你还能安全到达安全屋。如果无法实现，请你返回 -1 。如果不管你在初始位置停留多久，你 总是 
能到达安全屋，请你返回 10⁹ 。 

 注意，如果你到达安全屋后，火马上到了安全屋，这视为你能够安全到达安全屋。 

 如果两个格子有共同边，那么它们为 相邻 格子。 

 

 示例 1： 

 

 输入：grid = [[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0
,0,0,0,0,0]]
输出：3
解释：上图展示了你在初始位置停留 3 分钟后的情形。
你仍然可以安全到达安全屋。
停留超过 3 分钟会让你无法安全到达安全屋。 

 示例 2： 

 

 输入：grid = [[0,0,0,0],[0,1,2,0],[0,2,0,0]]
输出：-1
解释：上图展示了你马上开始朝安全屋移动的情形。
火会蔓延到你可以移动的所有格子，所以无法安全到达安全屋。
所以返回 -1 。
 

 示例 3： 

 

 输入：grid = [[0,0,0],[2,2,0],[1,2,0]]
输出：1000000000
解释：上图展示了初始网格图。
注意，由于火被墙围了起来，所以无论如何你都能安全到达安全屋。
所以返回 10⁹ 。
 

 

 提示： 

 
 m == grid.length 
 n == grid[i].length 
 2 <= m, n <= 300 
 4 <= m * n <= 2 * 10⁴ 
 grid[i][j] 是 0 ，1 或者 2 。 
 grid[0][0] == grid[m - 1][n - 1] == 0 
 

 Related Topics 广度优先搜索 数组 二分查找 矩阵 👍 153 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2258{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    const int dx[4] = {0, 0, -1, 1};
    const int dy[4] = {-1, 1, 0, 0};
    int maximumMinutes(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> que;
        que.emplace(0, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    que.emplace(i, j);
                }
            }
        }

        auto check = [&] (int time) {
            vector<vector<int>> g = grid;
            // 分开表示人和火的位置
            vector<vector<bool>> person(m, vector<bool>(n, false));
            person[0][0] = true;  // 初始位置

            // 先模拟火蔓延 time 分钟
            queue<pair<int, int>> fire_q;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (g[i][j] == 1) {
                        fire_q.emplace(i, j);
                    }
                }
            }

            for (int t = 0; t < time && !fire_q.empty(); t++) {
                int size = fire_q.size();
                for (int i = 0; i < size; i++) {
                    auto [x, y] = fire_q.front();
                    fire_q.pop();

                    for (int j = 0; j < 4; j++) {
                        int nx = x + dx[j];
                        int ny = y + dy[j];
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && g[nx][ny] == 0) {
                            g[nx][ny] = 1;  // 火蔓延
                            fire_q.emplace(nx, ny);
                        }
                    }
                }
            }

            // 如果初始位置已经着火，无法等待
            if (g[0][0] == 1) return false;

            // 人开始逃离
            queue<pair<int, int>> person_q;
            person_q.emplace(0, 0);

            while (!person_q.empty()) {
                // 人先移动
                int person_size = person_q.size();

                for (int i = 0; i < person_size; i++) {
                    auto [x, y] = person_q.front();
                    person_q.pop();

                    // 如果当前位置着火，跳过
                    if (g[x][y] == 1) continue;

                    // 如果到达安全屋，成功
                    if (x == m - 1 && y == n - 1) return true;

                    for (int j = 0; j < 4; j++) {
                        int nx = x + dx[j];
                        int ny = y + dy[j];
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && g[nx][ny] == 0 && !person[nx][ny]) {
                            person[nx][ny] = true;
                            person_q.emplace(nx, ny);
                        }
                    }
                }

                // 火蔓延
                int fire_size = fire_q.size();
                for (int i = 0; i < fire_size; i++) {
                    auto [x, y] = fire_q.front();
                    fire_q.pop();

                    for (int j = 0; j < 4; j++) {
                        int nx = x + dx[j];
                        int ny = y + dy[j];
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && g[nx][ny] == 0) {
                            g[nx][ny] = 1;
                            fire_q.emplace(nx, ny);
                        }
                    }
                }
            }

            // 检查是否到达安全屋
            return person[m-1][n-1] == true;
        };
        int l = -1, r = m * n + 1;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) l = mid;
            else r = mid;
        }
        return l >= m * n ? 1'000'000'000 : l;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2258;
int main() {
    Solution solution;

    return 0;
}