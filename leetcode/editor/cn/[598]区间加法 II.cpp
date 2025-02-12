/**
给你一个 m x n 的矩阵 M 和一个操作数组 op 。矩阵初始化时所有的单元格都为 0 。ops[i] = [ai, bi] 意味着当所有的 0 <= x 
< ai 和 0 <= y < bi 时， M[x][y] 应该加 1。 

 在 执行完所有操作后 ，计算并返回 矩阵中最大整数的个数 。 

 

 示例 1: 

 

 
输入: m = 3, n = 3，ops = [[2,2],[3,3]]
输出: 4
解释: M 中最大的整数是 2, 而且 M 中有4个值为2的元素。因此返回 4。
 

 示例 2:

 
输入: m = 3, n = 3, ops = [[2,2],[3,3],[3,3],[3,3],[2,2],[3,3],[3,3],[3,3],[2,2],[
3,3],[3,3],[3,3]]
输出: 4
 

 示例 3: 

 
输入: m = 3, n = 3, ops = []
输出: 9
 

 

 提示: 

 
 

 
 1 <= m, n <= 4 * 10⁴ 
 0 <= ops.length <= 10⁴ 
 ops[i].length == 2 
 1 <= ai <= m 
 1 <= bi <= n 
 

 Related Topics 数组 数学 👍 222 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution598{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
     int min_x = m;
     int min_y = n;
     for (auto op: ops) {
      int x = op[0], y = op[1];
      min_x = min(x, min_x);
      min_y = min(y, min_y);
     }
     return min_x * min_y;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution598;
int main() {
    Solution solution;

    return 0;
}