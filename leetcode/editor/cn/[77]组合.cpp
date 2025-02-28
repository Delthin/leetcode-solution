/**
给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。 

 你可以按 任何顺序 返回答案。 

 

 示例 1： 

 
输入：n = 4, k = 2
输出：
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
] 

 示例 2： 

 
输入：n = 1, k = 1
输出：[[1]] 

 

 提示： 

 
 1 <= n <= 20 
 1 <= k <= n 
 

 Related Topics 回溯 👍 1730 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution77{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    vector<int> path;
    vector<vector<int>> ret;
    void backTrace(int n, int k, int index) {
        if (path.size() == k) {
            ret.emplace_back(path);
            return;
        }
        for (int i = index; i <= n - (k - path.size()) + 1; i++) {
            path.emplace_back(i);
            backTrace(n, k, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        backTrace(n, k, 1);
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution77;
int main() {
    Solution solution;

    return 0;
}