/**
给你一个满足下述两条属性的 m x n 整数矩阵： 

 
 每行中的整数从左到右按非严格递增顺序排列。 
 每行的第一个整数大于前一行的最后一个整数。 
 

 给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。 

 

 示例 1： 
 
 
输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
输出：true
 

 示例 2： 
 
 
输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
输出：false
 

 

 提示： 

 
 m == matrix.length 
 n == matrix[i].length 
 1 <= m, n <= 100 
 -10⁴ <= matrix[i][j], target <= 10⁴ 
 

 Related Topics 数组 二分查找 矩阵 👍 1009 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution74{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row_l = 0, row_r = matrix.size();
        int row = -1;
        while (row_l < row_r) {
            int mid = row_l + (row_r - row_l) / 2;
            if (matrix[mid][0] <= target) {
                row_l = mid + 1;
                row = mid;
            } else {
                row_r = mid;
            }
        }
        if (row == -1) {
            return false;
        }
        int l = 0, r = matrix[0].size();
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (matrix[row][mid] == target) {
                return true;
            }
            if (matrix[row][mid] < target) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution74;
int main() {
    Solution solution;

    return 0;
}