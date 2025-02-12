/**
给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。 

 在「杨辉三角」中，每个数是它左上方和右上方的数的和。 

 

 

 示例 1: 

 
输入: numRows = 5
输出: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
 

 示例 2: 

 
输入: numRows = 1
输出: [[1]]
 

 

 提示: 

 
 1 <= numRows <= 30 
 

 Related Topics 数组 动态规划 👍 1216 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution118{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        ans.push_back({1});
        for(int i = 1; i < numRows; i++) {
            vector<int> row;
            row.push_back(1);
            for (int j = 0; j < i - 1; j++) {
                row.push_back(ans[i - 1][j] + ans[i - 1][j + 1]);
            }
            row.push_back(1);
            ans.push_back(row);
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution118;
int main() {
    Solution solution;
    solution.generate(5);
    return 0;
}