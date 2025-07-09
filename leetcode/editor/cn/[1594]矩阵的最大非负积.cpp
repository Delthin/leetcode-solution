/**
给你一个大小为 m x n 的矩阵 grid 。最初，你位于左上角 (0, 0) ，每一步，你可以在矩阵中 向右 或 向下 移动。 

 在从左上角 (0, 0) 开始到右下角 (m - 1, n - 1) 结束的所有路径中，找出具有 最大非负积 的路径。路径的积是沿路径访问的单元格中所有整数的
乘积。 

 返回 最大非负积 对 10⁹ + 7 取余 的结果。如果最大积为 负数 ，则返回 -1 。 

 注意，取余是在得到最大积之后执行的。 

 

 示例 1： 
 
 
输入：grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
输出：-1
解释：从 (0, 0) 到 (2, 2) 的路径中无法得到非负积，所以返回 -1 。 

 示例 2： 
 
 
输入：grid = [[1,-2,1],[1,-2,1],[3,-4,1]]
输出：8
解释：最大非负积对应的路径如图所示 (1 * 1 * -2 * -4 * 1 = 8)
 

 示例 3： 
 
 
输入：grid = [[1,3],[0,-4]]
输出：0
解释：最大非负积对应的路径如图所示 (1 * 0 * -4 = 0)
 

 

 提示： 

 
 m == grid.length 
 n == grid[i].length 
 1 <= m, n <= 15 
 -4 <= grid[i][j] <= 4 
 

 Related Topics 数组 动态规划 矩阵 👍 78 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1594{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        using ll = long long;
        int m = grid.size();
        int n = grid[0].size();
        vector<ll> maxDp(n, 0);
        vector<ll> minDp(n, 0);
        maxDp[0] = grid[0][0];
        minDp[0] = grid[0][0];
        for (int j = 1; j < n; ++j) {
            maxDp[j] = maxDp[j - 1] * grid[0][j];
            minDp[j] = minDp[j - 1] * grid[0][j];
        }

        for (int i = 1; i < m; ++i) {
            maxDp[0] = maxDp[0] * grid[i][0];
            minDp[0] = minDp[0] * grid[i][0];
            for (int j = 1; j < n; ++j) {
                ll tmp1 = maxDp[j] * grid[i][j];
                ll tmp2 = minDp[j] * grid[i][j];
                maxDp[j] = max({tmp1, tmp2, maxDp[j - 1] * grid[i][j], minDp[j - 1] * grid[i][j]});
                minDp[j] = min({tmp1, tmp2, maxDp[j - 1] * grid[i][j], minDp[j - 1] * grid[i][j]});
            }
        }

        if (maxDp[n - 1] < 0) {
            return -1;
        }
        return maxDp[n - 1] % 1000000007;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1594;
int main() {
    Solution solution;

    return 0;
}