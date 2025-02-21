/**
给你一个 正 整数 n 。 

 用 even 表示在 n 的二进制形式（下标从 0 开始）中值为 1 的偶数下标的个数。 

 用 odd 表示在 n 的二进制形式（下标从 0 开始）中值为 1 的奇数下标的个数。 

 请注意，在数字的二进制表示中，位下标的顺序 从右到左。 

 返回整数数组 answer ，其中 answer = [even, odd] 。 

 

 示例 1： 

 
 输入：n = 50 
 

 输出：[1,2] 

 解释： 

 50 的二进制表示是 110010。 

 在下标 1，4，5 对应的值为 1。 

 示例 2： 

 
 输入：n = 2 
 

 输出：[0,1] 

 解释： 

 2 的二进制表示是 10。 

 只有下标 1 对应的值为 1。 

 

 提示： 

 
 1 <= n <= 1000 
 

 Related Topics 位运算 👍 30 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2595{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<int> evenOddBit(int n) {
        int even = 0, odd = 0, index = 0;
        while (n > 0) {
            if(n % 2 == 1) {
                if (index % 2 == 0) {
                    even++;
                } else {
                    odd++;
                }
            }
            index++;
            n /= 2;
        }
        return {even, odd};
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2595;
int main() {
    Solution solution;

    return 0;
}