/**
给你一个整数数组 nums 和两个正整数 m 和 k 。 

 请你返回 nums 中长度为 k 的 几乎唯一 子数组的 最大和 ，如果不存在几乎唯一子数组，请你返回 0 。 

 如果 nums 的一个子数组有至少 m 个互不相同的元素，我们称它是 几乎唯一 子数组。 

 子数组指的是一个数组中一段连续 非空 的元素序列。 

 

 示例 1： 

 
输入：nums = [2,6,7,3,1,7], m = 3, k = 4
输出：18
解释：总共有 3 个长度为 k = 4 的几乎唯一子数组。分别为 [2, 6, 7, 3] ，[6, 7, 3, 1] 和 [7, 3, 1, 7] 。这些子数
组中，和最大的是 [2, 6, 7, 3] ，和为 18 。
 

 示例 2： 

 
输入：nums = [5,9,9,2,4,5,4], m = 1, k = 3
输出：23
解释：总共有 5 个长度为 k = 3 的几乎唯一子数组。分别为 [5, 9, 9] ，[9, 9, 2] ，[9, 2, 4] ，[2, 4, 5] 和 [4
, 5, 4] 。这些子数组中，和最大的是 [5, 9, 9] ，和为 23 。
 

 示例 3： 

 
输入：nums = [1,2,1,2,1,2,1], m = 3, k = 3
输出：0
解释：输入数组中不存在长度为 k = 3 的子数组含有至少  m = 3 个互不相同元素的子数组。所以不存在几乎唯一子数组，最大和为 0 。
 

 

 提示： 

 
 1 <= nums.length <= 2 * 10⁴ 
 1 <= m <= k <= nums.length 
 1 <= nums[i] <= 10⁹ 
 

 Related Topics 数组 哈希表 滑动窗口 👍 55 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2841{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    long long maxSum(vector<int>& nums, int m, int k) {
        unordered_map<int, int> freq;
        long long sum = 0;
        long long ans = 0;
        long long onlyNum = 0;
        for (long long i = 0; i < nums.size(); i++) {
            sum += nums[i];
            freq[nums[i]]++;
            if (freq[nums[i]] == 1) {
                onlyNum++;
            }
            if (i < k - 1) continue;
            if (onlyNum >= m) {
                ans = max(ans, sum);
            }
            sum -= nums[i - k + 1];
            freq[nums[i - k + 1]]--;
            if (freq[nums[i - k + 1]] == 0) {
                onlyNum--;
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2841;
int main() {
    Solution solution;

    return 0;
}