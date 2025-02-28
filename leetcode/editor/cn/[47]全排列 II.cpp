/**
给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。 

 

 示例 1： 

 
输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]
 

 示例 2： 

 
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 

 

 提示： 

 
 1 <= nums.length <= 8 
 -10 <= nums[i] <= 10 
 

 Related Topics 数组 回溯 排序 👍 1683 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution47{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    vector<vector<int>> ret;
    vector<int> path;
    void backTrace (vector<int>& nums, vector<bool>& used) {
        if (path.size() == nums.size()) {
            ret.emplace_back(path);
            return;
        }
        for (int i = 0; i< nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) {
                continue;
            }
            if (used[i] == false) {
                used[i] = true;
                path.emplace_back(nums[i]);
                backTrace(nums, used);
                path.pop_back();
                used[i] = false;
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // 排序
        vector<bool> used(nums.size(), false);
        backTrace(nums, used);
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution47;
int main() {
    Solution solution;

    return 0;
}