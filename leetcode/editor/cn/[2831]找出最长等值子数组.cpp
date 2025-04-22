//给你一个下标从 0 开始的整数数组 nums 和一个整数 k 。 
//
// 如果子数组中所有元素都相等，则认为子数组是一个 等值子数组 。注意，空数组是 等值子数组 。 
//
// 从 nums 中删除最多 k 个元素后，返回可能的最长等值子数组的长度。 
//
// 子数组 是数组中一个连续且可能为空的元素序列。 
//
// 
//
// 示例 1： 
//
// 
//输入：nums = [1,3,2,3,1,3], k = 3
//输出：3
//解释：最优的方案是删除下标 2 和下标 4 的元素。
//删除后，nums 等于 [1, 3, 3, 3] 。
//最长等值子数组从 i = 1 开始到 j = 3 结束，长度等于 3 。
//可以证明无法创建更长的等值子数组。
// 
//
// 示例 2： 
//
// 
//输入：nums = [1,1,2,2,1,1], k = 2
//输出：4
//解释：最优的方案是删除下标 2 和下标 3 的元素。 
//删除后，nums 等于 [1, 1, 1, 1] 。 
//数组自身就是等值子数组，长度等于 4 。 
//可以证明无法创建更长的等值子数组。
// 
//
// 
//
// 提示： 
//
// 
// 1 <= nums.length <= 10⁵ 
// 1 <= nums[i] <= nums.length 
// 0 <= k <= nums.length 
// 
//
// Related Topics 数组 哈希表 二分查找 滑动窗口 👍 137 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution2831{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        unordered_map<int, vector<int>> posList;
        for (int i = 0; i < nums.size(); i++) {
            posList[nums[i]].emplace_back(i);
        }
        int ans = 0;
        for (auto& [_, pos]: posList) {
            int l = 0;
            for (int r = 0; r < pos.size(); r++) {
                while (pos[r] - pos[l] - (r - l) > k) {
                    l++;
                }
                ans = max(ans, r - l + 1);
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2831;
int main() {
    Solution solution;

    return 0;
}