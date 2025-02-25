/**
给你一个字符串 s ，请你反转字符串中 单词 的顺序。 

 单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。 

 返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。 

 注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。 

 

 示例 1： 

 
输入：s = "the sky is blue"
输出："blue is sky the"
 

 示例 2： 

 
输入：s = "  hello world  "
输出："world hello"
解释：反转后的字符串中不能存在前导空格和尾随空格。
 

 示例 3： 

 
输入：s = "a good   example"
输出："example good a"
解释：如果两个单词间有多余的空格，反转后的字符串需要将单词间的空格减少到仅有一个。
 

 

 提示： 

 
 1 <= s.length <= 10⁴ 
 s 包含英文大小写字母、数字和空格 ' ' 
 s 中 至少存在一个 单词 
 

 
 

 

 进阶：如果字符串在你使用的编程语言中是一种可变数据类型，请尝试使用 O(1) 额外空间复杂度的 原地 解法。 

 Related Topics 双指针 字符串 👍 1268 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution151{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    void removeExtraSpaces(string& s) {//去除所有空格并在相邻单词之间添加空格, 快慢指针。
        int slow = 0;   //整体思想参考https://programmercarl.com/0027.移除元素.html
        for (int i = 0; i < s.size(); ++i) { //
            if (s[i] != ' ') { //遇到非空格就处理，即删除所有空格。
                if (slow != 0) s[slow++] = ' '; //手动控制空格，给单词之间添加空格。slow != 0说明不是第一个单词，需要在单词前添加空格。
                while (i < s.size() && s[i] != ' ') { //补上该单词，遇到空格说明单词结束。
                    s[slow++] = s[i++];
                }
            }
        }
        s.resize(slow); //slow的大小即为去除多余空格后的大小。
    }
public:
    string reverseWords(string s) {
        removeExtraSpaces(s);
        reverse(s.begin(), s.end());
        for (int i = 0; i < s.size();) {
            int r = i + 1;
            while (r < s.size() && s[r] != ' ') {
                r++;
            }
            reverse(s.begin() + i, s.begin() + r);
            i = r + 1;
        }
        return s;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution151;
int main() {
    Solution solution;
    solution.reverseWords("the sky is blue");
    return 0;
}