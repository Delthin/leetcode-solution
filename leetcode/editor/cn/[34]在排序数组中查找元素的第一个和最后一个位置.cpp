/**
给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。 

 如果数组中不存在目标值 target，返回 [-1, -1]。 

 你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。 

 

 示例 1： 

 
输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4] 

 示例 2： 

 
输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1] 

 示例 3： 

 
输入：nums = [], target = 0
输出：[-1,-1] 

 

 提示： 

 
 0 <= nums.length <= 10⁵ 
 -10⁹ <= nums[i] <= 10⁹ 
 nums 是一个非递减数组 
 -10⁹ <= target <= 10⁹ 
 

 Related Topics 数组 二分查找 👍 2888 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution34{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = 0, r = nums.size();
        int first = -1;
        while(l < r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] < target) {
                l = mid + 1;
                first = mid;
            } else {
                r = mid;
            }
        }
        first++;
        l = first;
        r = nums.size();
        int last = -1;
        while(l < r) {
            // 找第一个大的
            int mid = l + (r - l) / 2;
            if (nums[mid] <= target) {
                l = mid + 1;
                last = mid;
            } else {
                r = mid;
            }
        }
        if (last == -1) {
            return {-1, -1};
        }
        return {first, last};
    }

};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution34;
int main() {
    Solution solution;

    return 0;
}