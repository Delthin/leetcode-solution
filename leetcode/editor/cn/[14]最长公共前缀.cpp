//编写一个函数来查找字符串数组中的最长公共前缀。 
//
// 如果不存在公共前缀，返回空字符串 ""。 
//
// 
//
// 示例 1： 
//
// 
//输入：strs = ["flower","flow","flight"]
//输出："fl"
// 
//
// 示例 2： 
//
// 
//输入：strs = ["dog","racecar","car"]
//输出：""
//解释：输入不存在公共前缀。 
//
// 
//
// 提示： 
//
// 
// 1 <= strs.length <= 200 
// 0 <= strs[i].length <= 200 
// strs[i] 如果非空，则仅由小写英文字母组成 
// 
//
// Related Topics 字典树 字符串 👍 3270 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution14{
//leetcode submit region begin(Prohibit modification and deletion)
class Node {
private:
    vector<pair<Node*, int>>children;
public:
    Node() {
        children.resize(26, {nullptr, 0});
    }
    void insert(const string& str) {
        int index = 0;
        while (index < str.size()) {
            int alphabet = str[index] - 'a';
            Node* node = children[alphabet].first;
            if (node == nullptr) {
                node = new Node();
                children[alphabet].first = node;
            }
            children[alphabet].second++;
            index++;
        }
    }
};

    class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution14;
int main() {
    Solution solution;

    return 0;
}