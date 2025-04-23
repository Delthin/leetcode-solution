/**
给你一个下标从 0 开始的数组 nums 和一个整数 target 。 

 下标从 0 开始的数组 infinite_nums 是通过无限地将 nums 的元素追加到自己之后生成的。 

 请你从 infinite_nums 中找出满足 元素和 等于 target 的 最短 子数组，并返回该子数组的长度。如果不存在满足条件的子数组，返回 -1 。
 

 

 示例 1： 

 
输入：nums = [1,2,3], target = 5
输出：2
解释：在这个例子中 infinite_nums = [1,2,3,1,2,3,1,2,...] 。
区间 [1,2] 内的子数组的元素和等于 target = 5 ，且长度 length = 2 。
可以证明，当元素和等于目标值 target = 5 时，2 是子数组的最短长度。 

 示例 2： 

 
输入：nums = [1,1,1,2,3], target = 4
输出：2
解释：在这个例子中 infinite_nums = [1,1,1,2,3,1,1,1,2,3,1,1,...].
区间 [4,5] 内的子数组的元素和等于 target = 4 ，且长度 length = 2 。
可以证明，当元素和等于目标值 target = 4 时，2 是子数组的最短长度。
 

 示例 3： 

 
输入：nums = [2,4,6,8], target = 3
输出：-1
解释：在这个例子中 infinite_nums = [2,4,6,8,2,4,6,8,...] 。
可以证明，不存在元素和等于目标值 target = 3 的子数组。
 

 

 提示： 

 
 1 <= nums.length <= 10⁵ 
 1 <= nums[i] <= 10⁵ 
 1 <= target <= 10⁹ 
 

 Related Topics 数组 哈希表 前缀和 滑动窗口 👍 43 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2875{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int minSizeSubarray(vector<int>& nums, int target) {
        int n = nums.size();
        int ans = INT_MAX;
        long long numSum = accumulate(nums.begin(), nums.end(), 0LL);
        int circles = target / numSum;
        target %= numSum;
        int l = 0, r = 0;
        long long sum = 0;
        for (; r < 2 * n && l < n; r++) {
            sum += nums[r % n];
            while (sum > target) {
                sum -= nums[l++ % n];
            }
            if (sum == target) {
                ans = min(ans, r - l + 1);
            }
        }
        if (ans == INT_MAX) return -1;
        return ans + circles * n;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2875;
int main() {
    Solution solution;

    return 0;
}