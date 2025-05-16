//给你一个整数数组 nums 。数组 nums 的 唯一性数组 是一个按元素从小到大排序的数组，包含了 nums 的所有非空 子数组 中不同元素的个数。 
//
// 换句话说，这是由所有 0 <= i <= j < nums.length 的 distinct(nums[i..j]) 组成的递增数组。 
//
// 其中，distinct(nums[i..j]) 表示从下标 i 到下标 j 的子数组中不同元素的数量。 
//
// 返回 nums 唯一性数组 的 中位数 。 
//
// 注意，数组的 中位数 定义为有序数组的中间元素。如果有两个中间元素，则取值较小的那个。
// 
//
// 
//
// 示例 1： 
//
// 
// 输入：nums = [1,2,3] 
// 
//
// 输出：1 
//
// 解释： 
//
// nums 的唯一性数组为 [distinct(nums[0..0]), distinct(nums[1..1]), distinct(nums[2..2]
//), distinct(nums[0..1]), distinct(nums[1..2]), distinct(nums[0..2])]，即 [1, 1, 1,
// 2, 2, 3] 。唯一性数组的中位数为 1 ，因此答案是 1 。 
//
// 示例 2： 
//
// 
// 输入：nums = [3,4,3,4,5] 
// 
//
// 输出：2 
//
// 解释： 
//
// nums 的唯一性数组为 [1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3] 。唯一性数组的中位数为 2 ，因此答
//案是 2 。 
//
// 示例 3： 
//
// 
// 输入：nums = [4,3,5,4] 
// 
//
// 输出：2 
//
// 解释： 
//
// nums 的唯一性数组为 [1, 1, 1, 1, 2, 2, 2, 3, 3, 3] 。唯一性数组的中位数为 2 ，因此答案是 2 。 
//
// 
//
// 提示： 
//
// 
// 1 <= nums.length <= 10⁵ 
// 1 <= nums[i] <= 10⁵ 
// 
//
// Related Topics 数组 哈希表 二分查找 滑动窗口 👍 47 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution3134{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        long long k = (n * (n + 1LL) / 2 + 1) / 2;
        auto check = [&] (int x) ->bool {
            // 对x + 1滑窗，能满足x+1的剩下元素都在x+1及以上
            unordered_map<int, int> freq;
            int l = 0;
            long long num = 0;
            for (int r = 0; r < n; r++) {
                freq[nums[r]]++;
                while (freq.size() >= x) {
                    // 退到滑窗只有x为止，剩余元素的组合数量就是x+1及以上的数量
                    if (--freq[nums[l]] == 0) {
                        freq.erase(nums[l]);
                    }
                    l++;
                }
                num += r - l + 1;
                if (num >= k) return true;
            }
            return num >= k;
        };
        int l = 1, r = n + 1;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            (check(mid) ? r : l) = mid;
        }
        return r - 1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3134;
int main() {
    Solution solution;
    vector<int> nums = {3,4,3,4,5};
    solution.medianOfUniquenessArray(nums);
    return 0;
}