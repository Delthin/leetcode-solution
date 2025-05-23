//给定一个整数数组 nums 和一个整数 k ，返回其中元素之和可被 k 整除的非空 子数组 的数目。 
//
// 子数组 是数组中 连续 的部分。 
//
// 
//
// 示例 1： 
//
// 
//输入：nums = [4,5,0,-2,-3,1], k = 5
//输出：7
//解释：
//有 7 个子数组满足其元素之和可被 k = 5 整除：
//[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
// 
//
// 示例 2: 
//
// 
//输入: nums = [5], k = 9
//输出: 0
// 
//
// 
//
// 提示: 
//
// 
// 1 <= nums.length <= 3 * 10⁴ 
// -10⁴ <= nums[i] <= 10⁴ 
// 2 <= k <= 10⁴ 
// 
//
// Related Topics 数组 哈希表 前缀和 👍 551 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution974{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size();
        int s = 0;
        unordered_map<int, int> freq;
        freq[0] = 1;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            s = s + nums[i];
            int rest = (s % k + k) % k;
            if (freq.find(rest) != freq.end()) {
                ans += freq[rest];
            }
            freq[rest]++;
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution974;
int main() {
    Solution solution;

    return 0;
}