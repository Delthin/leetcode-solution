/**
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。 

 算法的时间复杂度应该为 O(log (m+n)) 。 

 

 示例 1： 

 
输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2
 

 示例 2： 

 
输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
 

 

 

 提示： 

 
 nums1.length == m 
 nums2.length == n 
 0 <= m <= 1000 
 0 <= n <= 1000 
 1 <= m + n <= 2000 
 -10⁶ <= nums1[i], nums2[i] <= 10⁶ 
 

 Related Topics 数组 二分查找 分治 👍 7378 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution4{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int totalLength = nums1.size() + nums2.size();
        if (totalLength % 2 == 1) {
            return getKthElement(nums1, nums2, (totalLength + 1) / 2);
        }
        else {
            return (getKthElement(nums1, nums2, totalLength / 2) + getKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
        }
    }
    int getKthElement(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size(), n = nums2.size();
        int index1 = 0, index2 = 0;
        while (true) {
            if (index1 >= m) {
                return nums2[index2 + k - 1];
            }
            if (index2 >= n) {
                return nums1[index1 + k - 1];
            }
            if (k == 1) {
                return min(nums1[index1], nums2[index2]);
            }
            int newIndex1 = min(index1 + k / 2 - 1, m - 1);
            int newIndex2 = min(index2 + k / 2 - 1, n - 1);
            if (nums1[newIndex1] <= nums2[newIndex2]) {
                k -= newIndex1 - index1 + 1;
                index1 = newIndex1 + 1;
            } else {
                k -= newIndex2 - index2 + 1;
                index2 = newIndex2 + 1;
            }
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution4;
int main() {
    Solution solution;
    vector<int> nums1 = {1,3};
    vector<int> nums2 = {2};
    solution.findMedianSortedArrays(nums1, nums2);
    return 0;
}