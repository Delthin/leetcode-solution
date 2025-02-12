/**
整数数组 nums 按升序排列，数组中的值 互不相同 。 

 在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+
1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4
,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。 

 给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。 

 你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。 

 

 示例 1： 

 
输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4
 

 示例 2： 

 
输入：nums = [4,5,6,7,0,1,2], target = 3
输出：-1 

 示例 3： 

 
输入：nums = [1], target = 0
输出：-1
 

 

 提示： 

 
 1 <= nums.length <= 5000 
 -10⁴ <= nums[i] <= 10⁴ 
 nums 中的每个值都 独一无二 
 题目数据保证 nums 在预先未知的某个下标上进行了旋转 
 -10⁴ <= target <= 10⁴ 
 

 Related Topics 数组 二分查找 👍 3096 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution33{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    static bool check_target(int i, vector<int>& nums, int target) {
        return nums[i] <= target;
    }
    static bool check_rotate(int i, vector<int>& nums, int target) {
        return i < nums.size() - 1 && (nums[i] > nums[i + 1] || nums[i] > nums.back());
    }
public:
    int search(vector<int>& nums, int target) {
        int rotate_i = binary_search(0, nums.size() - 1, nums, -1, check_rotate);
        int ans = -1;
        if (rotate_i == -1) {
            ans = binary_search(0, nums.size(), nums, target, check_target);
        }else if (target >= nums[0]) {
            ans = binary_search(0, rotate_i + 1, nums, target, check_target);
        }
        else {
            ans = binary_search(rotate_i + 1, nums.size(), nums, target, check_target);
        }
        return ans == -1 ? -1 : target == nums[ans] ? ans : -1;
    }
    int binary_search(int l, int r, vector<int>& nums, int target, bool (*check)(int, vector<int>&, int)) {
        int ans = -1;
        while(l < r) {
            int mid = l + (r - l) / 2;
            if (check(mid, nums, target)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution33;
int main() {
    Solution solution;
    vector<int> test = {3,4,5,6,1,2};
    solution.search(test, 2);
    return 0;
}