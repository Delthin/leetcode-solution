/**
给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。 

 

 示例 1： 
 
 
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
 

 示例 2： 
 
 
输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]
 

 

 提示： 

 
 m == matrix.length 
 n == matrix[i].length 
 1 <= m, n <= 10 
 -100 <= matrix[i][j] <= 100 
 

 Related Topics 数组 矩阵 模拟 👍 1835 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution54{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        const int step[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        const int visited = 101;
        int x = 0, y = 0;
        int direction = 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> ans(m * n);
        for (int i = 0; i < m * n; i++) {
            ans[i] = matrix[x][y];
            matrix[x][y] = visited;
            int next_x = x + step[direction][0];
            int next_y = y + step[direction][1];
            if (next_x < 0 || next_x >= m || next_y < 0 || next_y >= n ||
                matrix[next_x][next_y] == visited) {
                direction = (direction + 1) % 4;
                next_x = x + step[direction][0];
                next_y = y + step[direction][1];
            }
            x = next_x;
            y = next_y;
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution54;
int main() {
    Solution solution;

    return 0;
}