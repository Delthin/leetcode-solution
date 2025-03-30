/**
给你一个正整数数组 nums ，请你从中删除一个含有 若干不同元素 的子数组。删除子数组的 得分 就是子数组各元素之 和 。 

 返回 只删除一个 子数组可获得的 最大得分 。 

 如果数组 b 是数组 a 的一个连续子序列，即如果它等于 a[l],a[l+1],...,a[r] ，那么它就是 a 的一个子数组。 

 

 示例 1： 

 
输入：nums = [4,2,4,5,6]
输出：17
解释：最优子数组是 [2,4,5,6]
 

 示例 2： 

 
输入：nums = [5,2,1,2,5,2,1,2,5]
输出：8
解释：最优子数组是 [5,2,1] 或 [1,2,5]
 

 

 提示： 

 
 1 <= nums.length <= 10⁵ 
 1 <= nums[i] <= 10⁴ 
 

 Related Topics 数组 哈希表 滑动窗口 👍 108 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1695{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        unordered_set<int> us;
        int l = 0, r = 0;
        int ans = 0;
        int sum = 0;
        for (; r < nums.size(); r++) {
            while (us.count(nums[r]) != 0) {
                us.erase(nums[l]);
                sum -= nums[l];
                l++;
            }
            sum += nums[r];
            us.insert(nums[r]);
            ans = max(ans, sum);
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1695;
int main() {
    Solution solution;

    return 0;
}