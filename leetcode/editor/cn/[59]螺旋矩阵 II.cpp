/**
给你一个正整数 n ，生成一个包含 1 到 n² 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。 

 

 示例 1： 
 
 
输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]
 

 示例 2： 

 
输入：n = 1
输出：[[1]]
 

 

 提示： 

 
 1 <= n <= 20 
 

 Related Topics 数组 矩阵 模拟 👍 1410 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution59{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ans(n, vector<int>(n));
        constexpr int direction[4][2] = {{0, 1},{1,0},{0, -1}, {-1, 0}};
        int x = 0, y = 0;
        int direct = 0;
        for (int i = 1; i <= n * n; i++) {
            ans[x][y] = i;
            int newX = x + direction[direct][0];
            int newY = y + direction[direct][1];
            if (newX < 0 || newX >= n || newY < 0 || newY >= n || ans[newX][newY] != 0) {
                direct = (direct + 1) % 4;
                newX = x + direction[direct][0];
                newY = y + direction[direct][1];
            }
            x = newX;
            y = newY;
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution59;
int main() {
    Solution solution;
    solution.generateMatrix(3);
    return 0;
}