/**
你有一套活字字模 tiles，其中每个字模上都刻有一个字母 tiles[i]。返回你可以印出的非空字母序列的数目。 

 注意：本题中，每个活字字模只能使用一次。 

 

 示例 1： 

 
输入："AAB"
输出：8
解释：可能的序列为 "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA"。
 

 示例 2： 

 
输入："AAABBC"
输出：188
 

 示例 3： 

 
输入："V"
输出：1 

 

 提示： 

 
 1 <= tiles.length <= 7 
 tiles 由大写英文字母组成 
 

 Related Topics 哈希表 字符串 回溯 计数 👍 290 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1079{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int numTilePossibilities(string tiles) {
        vector<long long> freq(27, 0);
        for (char c : tiles) {
            freq[c - 'A' + 1]++;
        }
        unordered_set<int> res;
        function<void(long long)> dfs = [&](long long cur) {
            if (cur > 0) {
                res.insert(cur);
            }
            for (int i = 1; i <= 26; i++) {
                if (freq[i] > 0) {
                    freq[i]--;
                    long long target = cur * 26 + i;
                    if (res.find(target) == res.end()) {
                        dfs(target);
                    }
                    freq[i]++;
                }
            }
        };
        dfs(0);
        return res.size();
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1079;
int main() {
    Solution solution;
    string tiles = "AAB";
    cout << solution.numTilePossibilities(tiles) << endl;
    return 0;
}