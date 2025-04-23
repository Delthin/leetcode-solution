//给定一个正整数数组 nums和一个整数 k，返回 nums 中 「好子数组」 的数目。 
//
// 如果 nums 的某个子数组中不同整数的个数恰好为 k，则称 nums 的这个连续、不一定不同的子数组为 「好子数组 」。 
//
// 
// 例如，[1,2,3,1,2] 中有 3 个不同的整数：1，2，以及 3。 
// 
//
// 子数组 是数组的 连续 部分。 
//
// 
//
// 示例 1： 
//
// 
//输入：nums = [1,2,1,2,3], k = 2
//输出：7
//解释：恰好由 2 个不同整数组成的子数组：[1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
// 
//
// 示例 2： 
//
// 
//输入：nums = [1,2,1,3,4], k = 3
//输出：3
//解释：恰好由 3 个不同整数组成的子数组：[1,2,1,3], [2,1,3], [1,3,4].
// 
//
// 
//
// 提示： 
//
// 
// 1 <= nums.length <= 2 * 10⁴ 
// 1 <= nums[i], k <= nums.length 
// 
//
// Related Topics 数组 哈希表 计数 滑动窗口 👍 515 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution992{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        unordered_map<int, int> freq1, freq2;
        int l1 = 0, l2 = 0, r = 0;
        int ans = 0;
        for (; r < nums.size(); r++) {
            freq1[nums[r]]++;
            freq2[nums[r]]++;
            while (l1 <= r && freq1.size() >= k) {
                freq1[nums[l1]]--;
                if (freq1[nums[l1]] == 0) {
                    freq1.erase(nums[l1]);
                }
                l1++;
            }
            while (l2 <= r && freq2.size() > k) {
                freq2[nums[l2]]--;
                if (freq2[nums[l2]] == 0) {
                    freq2.erase(nums[l2]);
                }
                l2++;
            }
            ans += l1 - l2;
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution992;
int main() {
    Solution solution;

    return 0;
}