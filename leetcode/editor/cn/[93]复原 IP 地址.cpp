/**
有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。 

 
 例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 
"192.168@1.1" 是 无效 IP 地址。 
 

 给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能的有效 IP 地址，这些地址可以通过在 s 中插入 '.' 来形成。你 不能 重新排序
或删除 s 中的任何数字。你可以按 任何 顺序返回答案。 

 

 示例 1： 

 
输入：s = "25525511135"
输出：["255.255.11.135","255.255.111.35"]
 

 示例 2： 

 
输入：s = "0000"
输出：["0.0.0.0"]
 

 示例 3： 

 
输入：s = "101023"
输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
 

 

 提示： 

 
 1 <= s.length <= 20 
 s 仅由数字组成 
 

 Related Topics 字符串 回溯 👍 1487 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution93{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    vector<string> ret;
    vector<int> dotPath;
    bool isValid(const string& str) {
        if ((str[0] == '0' && str.size() > 1) || str.size() > 3) {return false;}
        int num = stoi(str);
        return num >=0 && num <= 255;
    }
    string dot2String(const string& s) {
        string result = s;
        // 略过最后一个
        for (int i = dotPath.size() - 1; i >= 0; i--) {
            result.insert(dotPath[i], ".");
        }
        return result;
    }
    void backTrace(const string& s, int index) {
        if (dotPath.size() == 3 && index < s.size() && isValid(s.substr(index))) {
            ret.emplace_back(dot2String(s));
            return;
        }
        if (dotPath.size() >= 3) return;
        for (int i = index + 1; i <= min(index + 3, static_cast<int>(s.size())); i++) {
            if (isValid(s.substr(index, i - index))) {
                dotPath.emplace_back(i);
                backTrace(s, i);
                dotPath.pop_back();
            }
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        backTrace(s, 0);
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution93;
int main() {
    Solution solution;

    return 0;
}