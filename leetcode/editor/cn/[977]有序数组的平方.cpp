/**
给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。 

 
 

 

 示例 1： 

 
输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后，数组变为 [16,1,0,9,100]
排序后，数组变为 [0,1,9,16,100] 

 示例 2： 

 
输入：nums = [-7,-3,2,3,11]
输出：[4,9,9,49,121]
 

 

 提示： 

 
 1 <= nums.length <= 10⁴ 
 -10⁴ <= nums[i] <= 10⁴ 
 nums 已按 非递减顺序 排序 
 

 

 进阶： 

 
 请你设计时间复杂度为 O(n) 的算法解决本问题 
 

 Related Topics 数组 双指针 排序 👍 1081 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution977{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> ans;
        int l = 0, r = nums.size()-1;
        while(l <= r) {
            if (abs(nums[l]) > abs(nums[r])) {
                ans.push_back(static_cast<int>(pow(nums[l], 2)));
                l++;
            } else {
                ans.push_back(static_cast<int>(pow(nums[r], 2)));
                r--;
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution977;
int main() {
    Solution solution;

    return 0;
}