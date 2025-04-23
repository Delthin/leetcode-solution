//给你一个下标从 0 开始的整数数组 nums 。nums 的一个子数组如果满足以下条件，那么它是 不间断 的： 
//
// 
// i，i + 1 ，...，j 表示子数组中的下标。对于所有满足 i <= i1, i2 <= j 的下标对，都有 0 <= |nums[i1] - 
//nums[i2]| <= 2 。 
// 
//
// 请你返回 不间断 子数组的总数目。 
//
// 子数组是一个数组中一段连续 非空 的元素序列。 
//
// 
//
// 示例 1： 
//
// 
//输入：nums = [5,4,2,4]
//输出：8
//解释：
//大小为 1 的不间断子数组：[5], [4], [2], [4] 。
//大小为 2 的不间断子数组：[5,4], [4,2], [2,4] 。
//大小为 3 的不间断子数组：[4,2,4] 。
//没有大小为 4 的不间断子数组。
//不间断子数组的总数目为 4 + 3 + 1 = 8 。
//除了这些以外，没有别的不间断子数组。
// 
//
// 示例 2： 
//
// 
//输入：nums = [1,2,3]
//输出：6
//解释：
//大小为 1 的不间断子数组：[1], [2], [3] 。
//大小为 2 的不间断子数组：[1,2], [2,3] 。
//大小为 3 的不间断子数组：[1,2,3] 。
//不间断子数组的总数目为 3 + 2 + 1 = 6 。
// 
//
// 
//
// 提示： 
//
// 
// 1 <= nums.length <= 10⁵ 
// 1 <= nums[i] <= 10⁹ 
// 
//
// Related Topics 队列 数组 有序集合 滑动窗口 单调队列 堆（优先队列） 👍 61 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution2762{
//leetcode submit region begin(Prohibit modification and deletion)
    class Solution {
    public:
        long long continuousSubarrays(vector<int>& nums) {
            deque<int> min_q, max_q;
            long long ans = 0;
            int left = 0;
            for (int right = 0; right < nums.size(); right++) {
                int x = nums[right];
                while (!min_q.empty() && x <= nums[min_q.back()]) {
                    min_q.pop_back();
                }
                min_q.push_back(right);

                while (!max_q.empty() && x >= nums[max_q.back()]) {
                    max_q.pop_back();
                }
                max_q.push_back(right);

                while (nums[max_q.front()] - nums[min_q.front()] > 2) {
                    left++;
                    if (min_q.front() < left) {
                        min_q.pop_front();
                    }
                    if (max_q.front() < left) {
                        max_q.pop_front();
                    }
                }
                ans += right - left + 1;
            }
            return ans;
        }
    };
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2762;
int main() {
    Solution solution;

    return 0;
}