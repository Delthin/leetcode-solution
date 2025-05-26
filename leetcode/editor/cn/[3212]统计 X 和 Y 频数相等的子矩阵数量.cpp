/**
给你一个二维字符矩阵 grid，其中 grid[i][j] 可能是 'X'、'Y' 或 '.'，返回满足以下条件的子矩阵数量： 

 
 包含 grid[0][0] 
 'X' 和 'Y' 的频数相等。 
 至少包含一个 'X'。 
 

 

 示例 1： 

 
 输入： grid = [["X","Y","."],["Y",".","."]] 
 

 输出： 3 

 解释： 

 

 示例 2： 

 
 输入： grid = [["X","X"],["X","Y"]] 
 

 输出： 0 

 解释： 

 不存在满足 'X' 和 'Y' 频数相等的子矩阵。 

 示例 3： 

 
 输入： grid = [[".","."],[".","."]] 
 

 输出： 0 

 解释： 

 不存在满足至少包含一个 'X' 的子矩阵。 

 

 提示： 

 
 1 <= grid.length, grid[i].length <= 1000 
 grid[i][j] 可能是 'X'、'Y' 或 '.'. 
 

 Related Topics 数组 矩阵 前缀和 👍 3 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution3212{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> sumX(m + 1, vector<int>(n + 1, 0));
        vector<vector<int>> sumY(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n;j++) {
                sumX[i + 1][j + 1] = sumX[i + 1][j] + sumX[i][j + 1] - sumX[i][j] + (grid[i][j] == 'X');
                sumY[i + 1][j + 1] = sumY[i + 1][j] + sumY[i][j + 1] - sumY[i][j] + (grid[i][j] == 'Y');
            }
        }
        int ans = 0;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (sumX[i][j] > 0 && sumX[i][j] == sumY[i][j]) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3212;
int main() {
    Solution solution;
    vector<vector<char>> grid = {{'X','Y','.'},{'Y','.','.'}};
    solution.numberOfSubmatrices(grid);
    return 0;
}