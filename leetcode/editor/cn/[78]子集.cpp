/**
给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。 

 解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。 

 

 示例 1： 

 
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 

 示例 2： 

 
输入：nums = [0]
输出：[[],[0]]
 

 

 提示： 

 
 1 <= nums.length <= 10 
 -10 <= nums[i] <= 10 
 nums 中的所有元素 互不相同 
 

 Related Topics 位运算 数组 回溯 👍 2441 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution78{
//leetcode submit region begin(Prohibit modification and deletion)
    class Solution {
    private:
        vector<vector<int>> result;
        vector<int> path;
        void backtracking(vector<int>& nums, int startIndex) {
            result.push_back(path); // 收集子集，要放在终止添加的上面，否则会漏掉自己
            if (startIndex >= nums.size()) { // 终止条件可以不加
                return;
            }
            for (int i = startIndex; i < nums.size(); i++) {
                path.push_back(nums[i]);
                backtracking(nums, i + 1);
                path.pop_back();
            }
        }
    public:
        vector<vector<int>> subsets(vector<int>& nums) {
            result.clear();
            path.clear();
            backtracking(nums, 0);
            return result;
        }
    };
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution78;
int main() {
    Solution solution;

    return 0;
}