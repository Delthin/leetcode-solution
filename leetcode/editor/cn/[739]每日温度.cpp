/**
给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几
天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。 

 

 示例 1: 

 
输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]
 

 示例 2: 

 
输入: temperatures = [30,40,50,60]
输出: [1,1,1,0]
 

 示例 3: 

 
输入: temperatures = [30,60,90]
输出: [1,1,0] 

 

 提示： 

 
 1 <= temperatures.length <= 10⁵ 
 30 <= temperatures[i] <= 100 
 

 Related Topics 栈 数组 单调栈 👍 1888 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution739{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> stk;
        vector<int> ans(temperatures.size(), 0);
        for (int i = 0; i < temperatures.size(); i++) {
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                int day = stk.top();
                stk.pop();
                ans[day] = i - day;
            }
            stk.emplace(i);
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution739;
int main() {
    Solution solution;
    vector<int> temps = {30, 60, 90};
    solution.dailyTemperatures(temps);
    return 0;
}