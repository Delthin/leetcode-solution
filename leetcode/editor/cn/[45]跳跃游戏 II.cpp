/**
给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。 

 每个元素 nums[i] 表示从索引 i 向后跳转的最大长度。换句话说，如果你在 nums[i] 处，你可以跳转到任意 nums[i + j] 处: 

 
 0 <= j <= nums[i] 
 i + j < n 
 

 返回到达 nums[n - 1] 的最小跳跃次数。生成的测试用例可以到达 nums[n - 1]。 

 

 示例 1: 

 
输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
 

 示例 2: 

 
输入: nums = [2,3,0,1,4]
输出: 2
 

 

 提示: 

 
 1 <= nums.length <= 10⁴ 
 0 <= nums[i] <= 1000 
 题目保证可以到达 nums[n-1] 
 

 Related Topics 贪心 数组 动态规划 👍 2719 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution45{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int jump(vector<int>& nums) {
        int pos = 0;
        int n = nums.size();
        int ans = 0;
        while (pos < n - 1) {
            int can_reach = pos + nums[pos];
            if (can_reach >= n - 1) {
                ans++;
                break;
            }
            int max_pos = pos;
            for (int i = pos + 1; i <= can_reach; i++) {
                max_pos = max(max_pos, i + nums[i]);
            }
            pos = max_pos;
            ans++;
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution45;
int main() {
    Solution solution;
    vector<int> nums = {2,3,1,1,4};
    solution.jump(nums);
    return 0;
}