/**
给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的 子集（幂集）。 

 解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。 

 
 
 
 
 

 示例 1： 

 
输入：nums = [1,2,2]
输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
 

 示例 2： 

 
输入：nums = [0]
输出：[[],[0]]
 

 

 提示： 

 
 1 <= nums.length <= 10 
 -10 <= nums[i] <= 10 
 

 Related Topics 位运算 数组 回溯 👍 1270 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution90{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    vector<pair<int, int>> freq;
    vector<vector<int>> ans;
    vector<int> path;
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int num: nums) {
            if (freq.empty() || freq.back().first != num) {
                freq.emplace_back(num, 1);
            } else {
                freq.back().second++;
            }
        }
        combine(0);
        return ans;
    }
    void combine(int index) {
        if (index == freq.size()) {
            ans.push_back(path);
            return;
        }
        combine(index + 1);
        for (int i = 0; i < freq[index].second; i++) {
            path.push_back(freq[index].first);
            combine(index + 1);
        }
        for (int i = 0; i < freq[index].second; i++) {
            path.pop_back();
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution90;
int main() {
    Solution solution;

    return 0;
}