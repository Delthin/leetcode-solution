/**
给定一个平衡括号字符串 S，按下述规则计算该字符串的分数： 

 
 () 得 1 分。 
 AB 得 A + B 分，其中 A 和 B 是平衡括号字符串。 
 (A) 得 2 * A 分，其中 A 是平衡括号字符串。 
 

 

 示例 1： 

 输入： "()"
输出： 1
 

 示例 2： 

 输入： "(())"
输出： 2
 

 示例 3： 

 输入： "()()"
输出： 2
 

 示例 4： 

 输入： "(()(()))"
输出： 6
 

 

 提示： 

 
 S 是平衡括号字符串，且只含有 ( 和 ) 。 
 2 <= S.length <= 50 
 

 Related Topics 栈 字符串 👍 539 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution856{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int scoreOfParentheses(string s) {
        // (->0
        stack<int> st;
        for (char c: s) {
            if (c == '(') st.push(0);
            if (c == ')') {
                int tmp = 0;
                if (st.top() == 0) {
                    // () 直接消
                    st.pop();
                    tmp = 1;
                } else {
                    // (A)
                    tmp = st.top() * 2;
                    st.pop();
                    st.pop();
                }
                // 消AB
                while (!st.empty() && st.top() > 0) {
                    tmp += st.top();
                    st.pop();
                }
                st.push(tmp);
            }
        }
        return st.top();
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution856;
int main() {
    Solution solution;

    return 0;
}