/**
Alice 在给 Bob 用手机打字。数字到字母的 对应 如下图所示。 

 

 为了 打出 一个字母，Alice 需要 按 对应字母 i 次，i 是该字母在这个按键上所处的位置。 

 
 比方说，为了按出字母 's' ，Alice 需要按 '7' 四次。类似的， Alice 需要按 '5' 两次得到字母 'k' 。 
 注意，数字 '0' 和 '1' 不映射到任何字母，所以 Alice 不 使用它们。 
 

 但是，由于传输的错误，Bob 没有收到 Alice 打字的字母信息，反而收到了 按键的字符串信息 。 

 
 比方说，Alice 发出的信息为 "bob" ，Bob 将收到字符串 "2266622" 。 
 

 给你一个字符串 pressedKeys ，表示 Bob 收到的字符串，请你返回 Alice 总共可能发出多少种文字信息 。 

 由于答案可能很大，将它对 10⁹ + 7 取余 后返回。 

 

 示例 1： 

 
输入：pressedKeys = "22233"
输出：8
解释：
Alice 可能发出的文字信息包括：
"aaadd", "abdd", "badd", "cdd", "aaae", "abe", "bae" 和 "ce" 。
由于总共有 8 种可能的信息，所以我们返回 8 。
 

 示例 2： 

 
输入：pressedKeys = "222222222222222222222222222222222222"
输出：82876089
解释：
总共有 2082876103 种 Alice 可能发出的文字信息。
由于我们需要将答案对 10⁹ + 7 取余，所以我们返回 2082876103 % (10⁹ + 7) = 82876089 。
 

 

 提示： 

 
 1 <= pressedKeys.length <= 10⁵ 
 pressedKeys 只包含数字 '2' 到 '9' 。 
 

 Related Topics 哈希表 数学 字符串 动态规划 👍 133 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2266{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int countTexts(string pressedKeys) {
        using ll = long long;
        const int MOD = 1e9 + 7;
        int n = pressedKeys.size();
        vector<ll> dp3(n + 1, 0);
        vector<ll> dp4(n + 1, 0);

        dp3[0] = dp4[0] = 1;
        for (int i = 1; i <= min(4, n); i++) {
            dp3[i] = dp3[i-1];
            if (i >= 2) dp3[i] = (dp3[i] + dp3[i-2]) % MOD;
            if (i >= 3) dp3[i] = (dp3[i] + dp3[i-3]) % MOD;

            dp4[i] = dp4[i-1];
            if (i >= 2) dp4[i] = (dp4[i] + dp4[i-2]) % MOD;
            if (i >= 3) dp4[i] = (dp4[i] + dp4[i-3]) % MOD;
            if (i >= 4) dp4[i] = (dp4[i] + dp4[i-4]) % MOD;
        }

        for (int i = 5; i <= n; i++) {
            dp3[i] = (dp3[i - 3] + dp3[i - 2] + dp3[i - 1]) % MOD;
            dp4[i] = (dp4[i - 4] + dp4[i - 3] + dp4[i - 2] + dp4[i - 1]) % MOD;
        }

        ll ans = 1;
        for (int i = 0; i < n; ) {
            char c = pressedKeys[i];
            int j = i;
            while (j < n && pressedKeys[j] == c) j++;
            int len = j - i;
            if (c == '7' || c == '9') {
                ans = (ans * dp4[len]) % MOD;
            } else {
                ans = (ans * dp3[len]) % MOD;
            }
            i = j;
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2266;
int main() {
    Solution solution;

    return 0;
}