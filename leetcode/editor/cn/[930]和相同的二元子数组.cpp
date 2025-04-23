//给你一个二元数组 nums ，和一个整数 goal ，请你统计并返回有多少个和为 goal 的 非空 子数组。 
//
// 子数组 是数组的一段连续部分。 
//
// 
//
// 示例 1： 
//
// 
//输入：nums = [1,0,1,0,1], goal = 2
//输出：4
//解释：
//有 4 个满足题目要求的子数组：[1,0,1]、[1,0,1,0]、[0,1,0,1]、[1,0,1]
// 
//
// 示例 2： 
//
// 
//输入：nums = [0,0,0,0,0], goal = 0
//输出：15
// 
//
// 
//
// 提示： 
//
// 
// 1 <= nums.length <= 3 * 10⁴ 
// nums[i] 不是 0 就是 1 
// 0 <= goal <= nums.length 
// 
//
// Related Topics 数组 哈希表 前缀和 滑动窗口 👍 351 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution930{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        long long sum = 0, sum1 = 0;
        int ans = 0;
        int l = 0, l1 = 0, r = 0;
        for (; r < nums.size(); r++) {
            sum += nums[r];
            sum1 += nums[r];
            while (l <= r && sum >= goal) {
                sum -= nums[l];
                l++;
            }
            while (l1 <= r && sum1 >= goal + 1) {
                sum1 -= nums[l1];
                l1++;
            }
            ans += l - l1;
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution930;
int main() {
    Solution solution;

    return 0;
}