//给你一个 m x n 的二进制矩阵 grid ，每个格子要么为 0 （空）要么为 1 （被占据）。 
//
// 给你邮票的尺寸为 stampHeight x stampWidth 。我们想将邮票贴进二进制矩阵中，且满足以下 限制 和 要求 ： 
//
// 
// 覆盖所有 空 格子。 
// 不覆盖任何 被占据 的格子。 
// 我们可以放入任意数目的邮票。 
// 邮票可以相互有 重叠 部分。 
// 邮票不允许 旋转 。 
// 邮票必须完全在矩阵 内 。 
// 
//
// 如果在满足上述要求的前提下，可以放入邮票，请返回 true ，否则返回 false 。 
//
// 
//
// 示例 1： 
//
// 
//
// 输入：grid = [[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0]], stampHeight = 
//4, stampWidth = 3
//输出：true
//解释：我们放入两个有重叠部分的邮票（图中标号为 1 和 2），它们能覆盖所有与空格子。
// 
//
// 示例 2： 
//
// 
//
// 输入：grid = [[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]], stampHeight = 2, 
//stampWidth = 2 
//输出：false 
//解释：没办法放入邮票覆盖所有的空格子，且邮票不超出网格图以外。
// 
//
// 
//
// 提示： 
//
// 
// m == grid.length 
// n == grid[r].length 
// 1 <= m, n <= 10⁵ 
// 1 <= m * n <= 2 * 10⁵ 
// grid[r][c] 要么是 0 ，要么是 1 。 
// 1 <= stampHeight, stampWidth <= 10⁵ 
// 
//
// Related Topics 贪心 数组 矩阵 前缀和 👍 160 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution2132{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    int sArea(vector<vector<int>>& s, int r1, int c1, int r2, int c2) {
        return s[r2 + 1][c2 + 1] - s[r2 + 1][c1] - s[r1][c2 + 1] + s[r1][c1];
    }
public:
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        int m = grid.size(), n =  grid[0].size();
        vector<vector<int>> d(m+2, vector<int>(n+2, 0));
        vector<vector<int>> s(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                s[i+1][j+1] = s[i+1][j] + s[i][j+1] - s[i][j] + grid[i][j];
            }
        }
        for (int r1 = 0; r1 <= m - stampHeight; r1++) {
            for (int c1 = 0; c1 <= n - stampWidth; c1++) {
                if (grid[r1][c1] == 1) continue;
                int r2 = r1 + stampHeight - 1, c2 = c1 + stampWidth - 1;
                if (sArea(s, r1, c1, r2, c2) != 0) continue;
                d[r1+1][c1+1]++;
                d[r1+1][c2+2]--;
                d[r2+2][c1+1]--;
                d[r2+2][c2+2]++;
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                d[i+1][j+1] += d[i+1][j] + d[i][j+1] - d[i][j];
                if (grid[i][j] == 0 && d[i + 1][j + 1] == 0) return false;
            }
        }
        return true;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2132;
int main() {
    Solution solution;

    return 0;
}