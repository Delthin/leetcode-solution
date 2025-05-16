/**
给你一个正整数数组 price ，其中 price[i] 表示第 i 类糖果的价格，另给你一个正整数 k 。 

 商店组合 k 类 不同 糖果打包成礼盒出售。礼盒的 甜蜜度 是礼盒中任意两种糖果 价格 绝对差的最小值。 

 返回礼盒的 最大 甜蜜度。 

 

 示例 1： 

 
输入：price = [13,5,1,8,21,2], k = 3
输出：8
解释：选出价格分别为 [13,5,21] 的三类糖果。
礼盒的甜蜜度为 min(|13 - 5|, |13 - 21|, |5 - 21|) = min(8, 8, 16) = 8 。
可以证明能够取得的最大甜蜜度就是 8 。
 

 示例 2： 

 
输入：price = [1,3,1], k = 2
输出：2
解释：选出价格分别为 [1,3] 的两类糖果。 
礼盒的甜蜜度为 min(|1 - 3|) = min(2) = 2 。
可以证明能够取得的最大甜蜜度就是 2 。
 

 示例 3： 

 
输入：price = [7,7,7,7], k = 2
输出：0
解释：从现有的糖果中任选两类糖果，甜蜜度都会是 0 。
 

 

 提示： 

 
 2 <= k <= price.length <= 10⁵ 
 1 <= price[i] <= 10⁹ 
 

 Related Topics 贪心 数组 二分查找 排序 👍 186 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2517{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maximumTastiness(vector<int>& price, int k) {
        sort(price.begin(), price.end());
        auto check = [&] (int x) -> bool {
            int last = price[0], cnt = 1;
            for (int p: price) {
                if (p >= last + x) {
                    last = p;
                    cnt++;
                }
            }
            return cnt >= k;
        };
        int l = 0, r = *max_element(price.begin(), price.end());
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) l = mid;
            else r = mid;
        }
        return l;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2517;
int main() {
    Solution solution;

    return 0;
}