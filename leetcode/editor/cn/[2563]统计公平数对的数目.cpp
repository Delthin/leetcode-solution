//给你一个下标从 0 开始、长度为 n 的整数数组 nums ，和两个整数 lower 和 upper ，返回 公平数对的数目 。 
//
// 如果 (i, j) 数对满足以下情况，则认为它是一个 公平数对 ： 
//
// 
// 0 <= i < j < n，且 
// lower <= nums[i] + nums[j] <= upper 
// 
//
// 
//
// 示例 1： 
//
// 
//输入：nums = [0,1,7,4,4,5], lower = 3, upper = 6
//输出：6
//解释：共计 6 个公平数对：(0,3)、(0,4)、(0,5)、(1,3)、(1,4) 和 (1,5) 。
// 
//
// 示例 2： 
//
// 
//输入：nums = [1,7,9,2,5], lower = 11, upper = 11
//输出：1
//解释：只有单个公平数对：(2,3) 。
// 
//
// 
//
// 提示： 
//
// 
// 1 <= nums.length <= 10⁵ 
// nums.length == n 
// -10⁹ <= nums[i] <= 10⁹ 
// -10⁹ <= lower <= upper <= 10⁹ 
// 
//
// Related Topics 数组 双指针 二分查找 排序 👍 139 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution2563{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        long long ans = 0;
        sort(nums.begin(), nums.end());
        for (auto it = nums.begin(); it != nums.end(); ++it) {
            int nums_i = *it;
            auto lower_it = lower_bound(it + 1, nums.end(), lower - nums_i);
            auto upper_it = upper_bound(it + 1, nums.end(), upper - nums_i);
            ans += upper_it - lower_it;
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2563;
int main() {
    Solution solution;

    return 0;
}