//给你一个整数数组 nums。该数组包含 n 个元素，其中 恰好 有 n - 2 个元素是 特殊数字 。剩下的 两个 元素中，一个是所有 特殊数字 的 和 ，
//另一个是 异常值 。 
//
// 异常值 的定义是：既不是原始特殊数字之一，也不是所有特殊数字的和。 
//
// 注意，特殊数字、和 以及 异常值 的下标必须 不同 ，但可以共享 相同 的值。 
//
// 返回 nums 中可能的 最大异常值。 
//
// 
//
// 示例 1： 
//
// 
// 输入： nums = [2,3,5,10] 
// 
//
// 输出： 10 
//
// 解释： 
//
// 特殊数字可以是 2 和 3，因此和为 5，异常值为 10。 
//
// 示例 2： 
//
// 
// 输入： nums = [-2,-1,-3,-6,4] 
// 
//
// 输出： 4 
//
// 解释： 
//
// 特殊数字可以是 -2、-1 和 -3，因此和为 -6，异常值为 4。 
//
// 示例 3： 
//
// 
// 输入： nums = [1,1,1,1,1,5,5] 
// 
//
// 输出： 5 
//
// 解释： 
//
// 特殊数字可以是 1、1、1、1 和 1，因此和为 5，另一个 5 为异常值。 
//
// 
//
// 提示： 
//
// 
// 3 <= nums.length <= 10⁵ 
// -1000 <= nums[i] <= 1000 
// 输入保证 nums 中至少存在 一个 可能的异常值。 
// 
//
// Related Topics 数组 哈希表 计数 枚举 👍 19 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution3371{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int getLargestOutlier(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int sum = accumulate(nums.begin(), nums.end(), 0);
        // sum - 和 - 异常值 = 和
        // 异常值 = sum - 2和
        unordered_set<int> us(nums.begin(), nums.end());
        int ans = -1001;
        for (int i = 0; i < n; i++) {
            auto it = us.find(sum - 2 * nums[i]);
            if (it != us.end()) {
                // 第一个重复出现的直接跳过
                if (*it == nums[i]) {
                    if (nums.begin() + i == find(nums.begin(), nums.end(), nums[i])) {
                        continue;
                    }
                }
                ans = max(ans, *it);
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3371;
int main() {
    Solution solution;

    return 0;
}