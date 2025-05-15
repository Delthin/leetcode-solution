/**
给你一个下标从 0 开始长度为 n 的整数数组 stations ，其中 stations[i] 表示第 i 座城市的供电站数目。 

 每个供电站可以在一定 范围 内给所有城市提供电力。换句话说，如果给定的范围是 r ，在城市 i 处的供电站可以给所有满足 |i - j| <= r 且 0 <
= i, j <= n - 1 的城市 j 供电。 

 
 |x| 表示 x 的 绝对值 。比方说，|7 - 5| = 2 ，|3 - 10| = 7 。 
 

 一座城市的 电量 是所有能给它供电的供电站数目。 

 政府批准了可以额外建造 k 座供电站，你需要决定这些供电站分别应该建在哪里，这些供电站与已经存在的供电站有相同的供电范围。 

 给你两个整数 r 和 k ，如果以最优策略建造额外的发电站，返回所有城市中，最小电量的最大值是多少。 

 这 k 座供电站可以建在多个城市。 

 

 示例 1： 

 
输入：stations = [1,2,4,5,0], r = 1, k = 2
输出：5
解释：
最优方案之一是把 2 座供电站都建在城市 1 。
每座城市的供电站数目分别为 [1,4,4,5,0] 。
- 城市 0 的供电站数目为 1 + 4 = 5 。
- 城市 1 的供电站数目为 1 + 4 + 4 = 9 。
- 城市 2 的供电站数目为 4 + 4 + 5 = 13 。
- 城市 3 的供电站数目为 5 + 4 = 9 。
- 城市 4 的供电站数目为 5 + 0 = 5 。
供电站数目最少是 5 。
无法得到更优解，所以我们返回 5 。
 

 示例 2： 

 
输入：stations = [4,4,4,4], r = 0, k = 3
输出：4
解释：
无论如何安排，总有一座城市的供电站数目是 4 ，所以最优解是 4 。
 

 

 提示： 

 
 n == stations.length 
 1 <= n <= 10⁵ 
 0 <= stations[i] <= 10⁵ 
 0 <= r <= n - 1 
 0 <= k <= 10⁹ 
 

 Related Topics 贪心 队列 数组 二分查找 前缀和 滑动窗口 👍 60 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2528{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    long long maxPower(vector<int>& stations, int r, int k) {
        int n = stations.size();
        auto check = [&] (long long x)-> bool {
            vector<int> st(stations);
            long long window = 0;
            for (int i = 0; i < r; i++) {
                window += st[i];
            }
            long long total = 0;
            for (int i = 0; i < n; i++) {
                if (i < n - r) window += st[i + r];
                long long need = max(0LL, x - window);
                total += need;
                st[min(n - 1, i + r)] += need;
                window += need;
                if (i >= r) window -= st[i - r];
            }
            return total <= k;
        };
        long long w = 0, left = LONG_LONG_MAX;
        for (int i = 0; i < n; i++) {
            w += stations[i];
            left = min(w, left);
            if (i < 2 * r) continue;
            w -= stations[i - 2 * r];
        }
        long long right = accumulate(stations.begin(), stations.end(), 0LL) + k * (2 * r + 1LL) + 1;
        while (left + 1 < right) {
            long long mid = left + (right - left) / 2;
            if (check(mid)) left = mid;
            else right = mid;
        }
        return left;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2528;
int main() {
    Solution solution;
    vector<int> stations = {4,2};
    solution.maxPower(stations, 1, 1);
    return 0;
}