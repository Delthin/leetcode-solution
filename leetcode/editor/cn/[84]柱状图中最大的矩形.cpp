//给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。 
//
// 求在该柱状图中，能够勾勒出来的矩形的最大面积。 
//
// 
//
// 示例 1: 
//
// 
//
// 
//输入：heights = [2,1,5,6,2,3]
//输出：10
//解释：最大的矩形为图中红色区域，面积为 10
// 
//
// 示例 2： 
//
// 
//
// 
//输入： heights = [2,4]
//输出： 4 
//
// 
//
// 提示： 
//
// 
// 1 <= heights.length <=10⁵ 
// 0 <= heights[i] <= 10⁴ 
// 
//
// Related Topics 栈 数组 单调栈 👍 2886 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution84{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // nums[i]大于top，比较当前最大面积和前面最大面积，如果当前大，就弹，否则不弹
        // nums[i]小于top，弹所有大的
        // 等于同大于，更新
        // 每次压栈存{i};
        int ans = 0;
        stack<int> st;
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        for (int i = 0; i < heights.size(); i++) {
            while (!st.empty() && heights[i] < heights[st.top()]) {
                // 算弹出的左右
                int h = heights[st.top()];
                st.pop();
                ans = max(ans, h * (i - st.top() - 1));
            }
            st.emplace(i);
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution84;
int main() {
    Solution solution;
    vector<int> heights = {2, 1, 2};
    cout << solution.largestRectangleArea(heights);
    return 0;
}