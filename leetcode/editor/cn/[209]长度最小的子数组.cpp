/**
给定一个含有 n 个正整数的数组和一个正整数 target 。 

 找出该数组中满足其总和大于等于 target 的长度最小的 子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度
。如果不存在符合条件的子数组，返回 0 。 

 

 示例 1： 

 
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
 

 示例 2： 

 
输入：target = 4, nums = [1,4,4]
输出：1
 

 示例 3： 

 
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0
 

 

 提示： 

 
 1 <= target <= 10⁹ 
 1 <= nums.length <= 10⁵ 
 1 <= nums[i] <= 10⁴ 
 

 

 进阶： 

 
 如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n)) 时间复杂度的解法。 
 

 Related Topics 数组 二分查找 前缀和 滑动窗口 👍 2364 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution209{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix(n + 1);
        prefix[0] = 0;
        for(int i = 1; i <= n; i++) {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }
        if (prefix[n] - prefix[0] < target) {
            return 0;
        }
        int l = 0, r = 1;
        int ans = 100005;
        while(r <= n) {
            if(prefix[r] - prefix[l] < target) {
                r++;
            } else {
                ans = min(ans, r - l);
                l++;
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution209;
int main() {
    Solution solution;
    vector<int> nums = {1,2,3,4,5};
    solution.minSubArrayLen(11,nums);
    return 0;
}