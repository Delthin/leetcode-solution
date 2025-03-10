/**
给定一个字符串 s 和一个字符串字典
 wordDict ，在字符串
 s 中增加空格来构建一个句子，使得句子中所有的单词都在词典中。以任意顺序 返回所有这些可能的句子。 

 注意：词典中的同一个单词可能在分段中被重复使用多次。 

 

 示例 1： 

 
输入:s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
输出:["cats and dog","cat sand dog"]
 

 示例 2： 

 
输入:s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine",
"pineapple"]
输出:["pine apple pen apple","pineapple pen apple","pine applepen apple"]
解释: 注意你可以重复使用字典中的单词。
 

 示例 3： 

 
输入:s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
输出:[]
 

 

 提示： 

 
 

 
 1 <= s.length <= 20 
 1 <= wordDict.length <= 1000 
 1 <= wordDict[i].length <= 10 
 s 和 wordDict[i] 仅有小写英文字母组成 
 wordDict 中所有字符串都 不同 
 

 Related Topics 字典树 记忆化搜索 数组 哈希表 字符串 动态规划 回溯 👍 777 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution140{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    unordered_map<int, vector<string>> ans;
    unordered_set<string> wordSet;
    void backtrack(const string& s, int index) {
        if (!ans.count(index)) {
            if (index == s.size()) {
                ans[index] = {""};
                return;
            }
            for (int i = index + 1; i <= s.size(); i++) {
                string word = s.substr(index, i - index);
                if (wordSet.find(word) != wordSet.end()) {
                    backtrack(s, i);
                    for (const string& succ: ans[i]) {
                        ans[index].emplace_back(succ.empty() ? word: word + " " + succ);
                    }
                }
            }
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        wordSet = unordered_set<string>(wordDict.begin(), wordDict.end());
        backtrack(s, 0);
        return ans[0];
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution140;
int main() {
    Solution solution;

    return 0;
}