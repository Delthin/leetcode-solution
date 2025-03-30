/**
给你一个整数数组 nums 和一个整数 x 。每一次操作时，你应当移除数组 nums 最左边或最右边的元素，然后从 x 中减去该元素的值。请注意，需要 修改 数
组以供接下来的操作使用。 

 如果可以将 x 恰好 减到 0 ，返回 最小操作数 ；否则，返回 -1 。 

 

 示例 1： 

 
输入：nums = [1,1,4,2,3], x = 5
输出：2
解释：最佳解决方案是移除后两个元素，将 x 减到 0 。
 

 示例 2： 

 
输入：nums = [5,6,7,8,9], x = 4
输出：-1
 

 示例 3： 

 
输入：nums = [3,2,20,1,1,3], x = 10
输出：5
解释：最佳解决方案是移除后三个元素和前两个元素（总共 5 次操作），将 x 减到 0 。
 

 

 提示： 

 
 1 <= nums.length <= 10⁵ 
 1 <= nums[i] <= 10⁴ 
 1 <= x <= 10⁹ 
 

 Related Topics 数组 哈希表 二分查找 前缀和 滑动窗口 👍 412 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1658{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        const int maxSum = accumulate(nums.begin(), nums.end(), 0) - x;
        if (maxSum < 0) return - 1;
        int l = 0, r = 0;
        int sum = 0;
        int ans = INT_MAX;
        for (; r < nums.size(); r++) {
            sum += nums[r];
            while (sum > maxSum) {
                sum -= nums[l++];
            }
            if (sum == maxSum) {
                ans = min(ans, static_cast<int>(nums.size()) - r + l - 1);
            }
        }
        if (ans == INT_MAX) {
            return -1;
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1658;
int main() {
    Solution solution;

    return 0;
}