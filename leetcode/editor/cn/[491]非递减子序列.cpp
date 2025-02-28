/**
给你一个整数数组 nums ，找出并返回所有该数组中不同的递增子序列，递增子序列中 至少有两个元素 。你可以按 任意顺序 返回答案。 

 数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。 

 

 示例 1： 

 
输入：nums = [4,6,7,7]
输出：[[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
 

 示例 2： 

 
输入：nums = [4,4,3,2,1]
输出：[[4,4]]
 

 

 提示： 

 
 1 <= nums.length <= 15 
 -100 <= nums[i] <= 100 
 

 Related Topics 位运算 数组 哈希表 回溯 👍 843 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution491{
//leetcode submit region begin(Prohibit modification and deletion)
    class Solution {
    public:
        vector<int> temp;
        vector<vector<int>> ans;

        void dfs(int cur, int last, vector<int>& nums) {
            if (cur == nums.size()) {
                if (temp.size() >= 2) {
                    ans.push_back(temp);
                }
                return;
            }
            if (nums[cur] >= last) {
                temp.push_back(nums[cur]);
                dfs(cur + 1, nums[cur], nums);
                temp.pop_back();
            }
            if (nums[cur] != last) {
                dfs(cur + 1, last, nums);
            }
        }

        vector<vector<int>> findSubsequences(vector<int>& nums) {
            dfs(0, INT_MIN, nums);
            return ans;
        }
    };

//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution491;
int main() {
    Solution solution;

    return 0;
}