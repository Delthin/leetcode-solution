/**
给定一个整数数组 nums，处理以下类型的多个查询: 

 
 计算索引 left 和 right （包含 left 和 right）之间的 nums 元素的 和 ，其中 left <= right 
 

 实现 NumArray 类： 

 
 NumArray(int[] nums) 使用数组 nums 初始化对象 
 int sumRange(int i, int j) 返回数组 nums 中索引 left 和 right 之间的元素的 总和 ，包含 left 和 
right 两点（也就是 nums[left] + nums[left + 1] + ... + nums[right] ) 
 

 

 示例 1： 

 
输入：
["NumArray", "sumRange", "sumRange", "sumRange"]
[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
输出：
[null, 1, -1, -3]

解释：
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return 1 ((-2) + 0 + 3)
numArray.sumRange(2, 5); // return -1 (3 + (-5) + 2 + (-1)) 
numArray.sumRange(0, 5); // return -3 ((-2) + 0 + 3 + (-5) + 2 + (-1))
 

 

 提示： 

 
 1 <= nums.length <= 10⁴ 
 -10⁵ <= nums[i] <= 10⁵ 
 0 <= i <= j < nums.length 
 最多调用 10⁴ 次 sumRange 方法 
 

 Related Topics 设计 数组 前缀和 👍 687 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution303{
//leetcode submit region begin(Prohibit modification and deletion)
class NumArray {
    vector<int> prefix;
public:
    NumArray(vector<int>& nums) {
        prefix.resize(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }
    
    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution303;
int main() {
    Solution solution;

    return 0;
}