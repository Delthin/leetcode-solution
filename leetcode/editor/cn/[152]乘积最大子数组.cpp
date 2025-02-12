/**
给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续 子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。 

 测试用例的答案是一个 32-位 整数。 

 

 示例 1: 

 
输入: nums = [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。
 

 示例 2: 

 
输入: nums = [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。 

 

 提示: 

 
 1 <= nums.length <= 2 * 10⁴ 
 -10 <= nums[i] <= 10 
 nums 的任何子数组的乘积都 保证 是一个 32-位 整数 
 

 Related Topics 数组 动态规划 👍 2368 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution152{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }
        int ans = nums[0];
        pair<int, int> dp = {nums[0], nums[0]};
        for(int i = 1; i < n; i++) {
            int num = nums[i];
            const auto last = dp;
            dp = {max(last.first * num, max(num, last.second * num)), min(last.second * num, min(num, last.first * num))};
            ans = max(ans, dp.first);
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution152;
int main() {
    Solution solution;
    vector<int> nums = {2, 3, -2, 4};
    solution.maxProduct(nums);
    return 0;
}