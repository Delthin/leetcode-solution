/**
整数数组的一个 排列 就是将其所有成员以序列或线性顺序排列。 

 
 例如，arr = [1,2,3] ，以下这些都可以视作 arr 的排列：[1,2,3]、[1,3,2]、[3,1,2]、[2,3,1] 。 
 

 整数数组的 下一个排列 是指其整数的下一个字典序更大的排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，那么数组的 下一个排列 就是在
这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列（即，其元素按升序排列）。 

 
 例如，arr = [1,2,3] 的下一个排列是 [1,3,2] 。 
 类似地，arr = [2,3,1] 的下一个排列是 [3,1,2] 。 
 而 arr = [3,2,1] 的下一个排列是 [1,2,3] ，因为 [3,2,1] 不存在一个字典序更大的排列。 
 

 给你一个整数数组 nums ，找出 nums 的下一个排列。 

 必须 原地 修改，只允许使用额外常数空间。 

 

 示例 1： 

 
输入：nums = [1,2,3]
输出：[1,3,2]
 

 示例 2： 

 
输入：nums = [3,2,1]
输出：[1,2,3]
 

 示例 3： 

 
输入：nums = [1,1,5]
输出：[1,5,1]
 

 

 提示： 

 
 1 <= nums.length <= 100 
 0 <= nums[i] <= 100 
 

 Related Topics 数组 双指针 👍 2627 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution31{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int first_decend_ptr = nums.size() - 1;
        while (first_decend_ptr > 0) {
            if (nums[first_decend_ptr - 1] < nums[first_decend_ptr]) {
                break;
            }
            first_decend_ptr--;
        }
        if (first_decend_ptr == 0) {
            sort(nums.begin(), nums.end());
            return;
        }
        int first_larger_ptr = nums.size() - 1;
        for (; first_larger_ptr > first_decend_ptr; first_larger_ptr--) {
            if (nums[first_larger_ptr] > nums[first_decend_ptr - 1]) {
                break;
            }
        }
        swap(nums[first_larger_ptr], nums[first_decend_ptr - 1]);
        sort(nums.begin() + first_decend_ptr, nums.end());
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution31;
int main() {
    Solution solution;

    return 0;
}