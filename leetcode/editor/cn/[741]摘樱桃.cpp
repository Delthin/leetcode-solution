/**
给你一个 n x n 的网格 grid ，代表一块樱桃地，每个格子由以下三种数字的一种来表示： 

 
 0 表示这个格子是空的，所以你可以穿过它。 
 1 表示这个格子里装着一个樱桃，你可以摘到樱桃然后穿过它。 
 -1 表示这个格子里有荆棘，挡着你的路。 
 

 请你统计并返回：在遵守下列规则的情况下，能摘到的最多樱桃数： 

 
 从位置 (0, 0) 出发，最后到达 (n - 1, n - 1) ，只能向下或向右走，并且只能穿越有效的格子（即只可以穿过值为 0 或者 1 的格子）； 
 当到达 (n - 1, n - 1) 后，你要继续走，直到返回到 (0, 0) ，只能向上或向左走，并且只能穿越有效的格子； 
 当你经过一个格子且这个格子包含一个樱桃时，你将摘到樱桃并且这个格子会变成空的（值变为 0 ）； 
 如果在 (0, 0) 和 (n - 1, n - 1) 之间不存在一条可经过的路径，则无法摘到任何一个樱桃。 
 

 

 示例 1： 
 
 
输入：grid = [[0,1,-1],[1,0,-1],[1,1,1]]
输出：5
解释：玩家从 (0, 0) 出发：向下、向下、向右、向右移动至 (2, 2) 。
在这一次行程中捡到 4 个樱桃，矩阵变成 [[0,1,-1],[0,0,-1],[0,0,0]] 。
然后，玩家向左、向上、向上、向左返回起点，再捡到 1 个樱桃。
总共捡到 5 个樱桃，这是最大可能值。
 

 示例 2： 

 
输入：grid = [[1,1,-1],[1,-1,1],[-1,1,1]]
输出：0
 

 

 提示： 

 
 n == grid.length 
 n == grid[i].length 
 1 <= n <= 50 
 grid[i][j] 为 -1、0 或 1 
 grid[0][0] != -1 
 grid[n - 1][n - 1] != -1 
 

 Related Topics 数组 动态规划 矩阵 👍 499 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution741{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        // vector<vector<vector<int>>> memo(n * 2 - 1, vector<vector<int>>(n, vector<int>(n, -1)));
        // function<int(int, int, int)> dfs = [&](int t, int x1, int x2) -> int {
        //     if (x1 < 0 || x2 < 0 || t < x1 || t < x2 || grid[x1][t - x1] < 0 || grid[x2][t - x2] < 0) {
        //         return INT_MIN;
        //     }
        //     if (t == 0) {
        //         return grid[0][0];
        //     }
        //     int &res = memo[t][x1][x2];
        //     if (res != -1) {
        //         return res;
        //     }
        //     res = max({
        //         dfs(t - 1, x1 - 1, x2 - 1),
        //         dfs(t - 1, x1 - 1, x2),
        //         dfs(t - 1, x1, x2 - 1),
        //         dfs(t - 1, x1, x2)
        //     });
        //     res += grid[x1][t - x1];
        //     if (x1 != x2) {
        //         res += grid[x2][t - x2];
        //     }
        //     return res;
        // };
        // return max(dfs(n * 2 - 2, n - 1, n - 1), 0);
        vector<vector<vector<int>>> dp(2 * n - 1, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
        dp[0][0][0] = grid[0][0];
        for (int t = 1; t < 2 * n - 1; ++t) {
            for (int x1 = max(t - n + 1, 0); x1 < min(n, t + 1); ++x1) {
                for (int x2 = max(t - n + 1, 0); x2 < min(n, t + 1); ++x2) {
                    if (grid[x1][t - x1] < 0 || grid[x2][t - x2] < 0) {
                        continue;
                    }
                    int cherry = grid[x1][t - x1];
                    if (x1 != x2) {
                        cherry += grid[x2][t - x2];
                    }
                    for (int dx1 = -1; dx1 <= 0; ++dx1) {
                        for (int dx2 = -1; dx2 <= 0; ++dx2) {
                            if (x1 + dx1 >= 0 && x2 + dx2 >= 0 && dp[t - 1][x1 + dx1][x2 + dx2] != INT_MIN) {
                                dp[t][x1][x2] = max(dp[t][x1][x2], dp[t - 1][x1 + dx1][x2 + dx2] + cherry);
                            }
                        }
                    }
                }
            }
        }
        return max(dp[2 * n - 2][n - 1][n - 1], 0);
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution741;
int main() {
    Solution solution;
    vector<vector<int>> grid = {
        {0, 1, -1},
        {1, 0, -1},
        {1, 1, 1}
    };
    cout << solution.cherryPickup(grid) << endl;
    return 0;
}