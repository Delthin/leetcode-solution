//给你一个下标从 0 开始的整数数组 nums 。对于每个下标 i（1 <= i <= nums.length - 2），nums[i] 的 美丽值 等于： 
//
//
// 
// 2，对于所有 0 <= j < i 且 i < k <= nums.length - 1 ，满足 nums[j] < nums[i] < nums[k] 
//
// 1，如果满足 nums[i - 1] < nums[i] < nums[i + 1] ，且不满足前面的条件 
// 0，如果上述条件全部不满足 
// 
//
// 返回符合 1 <= i <= nums.length - 2 的所有 nums[i] 的 美丽值的总和 。 
//
// 
//
// 示例 1： 
//
// 输入：nums = [1,2,3]
//输出：2
//解释：对于每个符合范围 1 <= i <= 1 的下标 i :
//- nums[1] 的美丽值等于 2
// 
//
// 示例 2： 
//
// 输入：nums = [2,4,6,4]
//输出：1
//解释：对于每个符合范围 1 <= i <= 2 的下标 i :
//- nums[1] 的美丽值等于 1
//- nums[2] 的美丽值等于 0
// 
//
// 示例 3： 
//
// 输入：nums = [3,2,1]
//输出：0
//解释：对于每个符合范围 1 <= i <= 1 的下标 i :
//- nums[1] 的美丽值等于 0
// 
//
// 
//
// 提示： 
//
// 
// 3 <= nums.length <= 10⁵ 
// 1 <= nums[i] <= 10⁵ 
// 
//
// Related Topics 数组 👍 28 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution2012{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int sumOfBeauties(vector<int>& nums) {
        int maxBefore = nums[0];
        int minAfter = nums[nums.size() - 1];
        vector<int> vec(nums.size(), 0);
        for (int i = 1; i < nums.size() - 1; i++) {
            if (nums[i] > maxBefore) {
                vec[i]++;
                maxBefore = nums[i];
            }
        }
        int ans = 0;
        for (int i = nums.size() - 2; i >= 1; i--) {
            if (nums[i] < minAfter) {
                vec[i]++;
                minAfter = nums[i];
            }
            if (vec[i] == 2) {
                ans += 2;
            } else {
                ans += nums[i - 1] < nums[i] && nums[i] < nums[i + 1];
            }
        }
        return ans;

    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2012;
int main() {
    Solution solution;

    return 0;
}