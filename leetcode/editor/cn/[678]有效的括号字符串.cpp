/**
给你一个只包含三种字符的字符串，支持的字符类型分别是 '('、')' 和 '*'。请你检验这个字符串是否为有效字符串，如果是 有效 字符串返回 true 。 

 有效 字符串符合如下规则： 

 
 任何左括号 '(' 必须有相应的右括号 ')'。 
 任何右括号 ')' 必须有相应的左括号 '(' 。 
 左括号 '(' 必须在对应的右括号之前 ')'。 
 '*' 可以被视为单个右括号 ')' ，或单个左括号 '(' ，或一个空字符串 ""。 
 

 

 示例 1： 

 
输入：s = "()"
输出：true
 

 示例 2： 

 
输入：s = "(*)"
输出：true
 

 示例 3： 

 
输入：s = "(*))"
输出：true
 

 

 提示： 

 
 1 <= s.length <= 100 
 s[i] 为 '('、')' 或 '*' 
 

 Related Topics 栈 贪心 字符串 动态规划 👍 664 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution678{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool checkValidString(string s) {
        stack<int> stL;
        stack<int> stS;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                stL.push(i);
            } else if (s[i] == '*') {
                stS.push(i);
            } else {
                if (!stL.empty()) {
                    stL.pop();
                } else if (!stS.empty()) {
                    stS.pop();
                } else return false;
            }
        }
        while (!stL.empty()) {
            if (stS.empty() || stS.top() < stL.top()) return false;
            stL.pop();
            stS.pop();
        }
        return true;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution678;
int main() {
    Solution solution;

    return 0;
}