//给你一个二维整数数组 intervals ，其中 intervals[i] = [lefti, righti] 表示 闭 区间 [lefti, 
//righti] 。 
//
// 你需要将 intervals 划分为一个或者多个区间 组 ，每个区间 只 属于一个组，且同一个组中任意两个区间 不相交 。 
//
// 请你返回 最少 需要划分成多少个组。 
//
// 如果两个区间覆盖的范围有重叠（即至少有一个公共数字），那么我们称这两个区间是 相交 的。比方说区间 [1, 5] 和 [5, 8] 相交。 
//
// 
//
// 示例 1： 
//
// 
//输入：intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
//输出：3
//解释：我们可以将区间划分为如下的区间组：
//- 第 1 组：[1, 5] ，[6, 8] 。
//- 第 2 组：[2, 3] ，[5, 10] 。
//- 第 3 组：[1, 10] 。
//可以证明无法将区间划分为少于 3 个组。
// 
//
// 示例 2： 
//
// 
//输入：intervals = [[1,3],[5,6],[8,10],[11,13]]
//输出：1
//解释：所有区间互不相交，所以我们可以把它们全部放在一个组内。 
//
// 
//
// 提示： 
//
// 
// 1 <= intervals.length <= 10⁵ 
// intervals[i].length == 2 
// 1 <= lefti <= righti <= 10⁶ 
// 
//
// Related Topics 贪心 数组 双指针 前缀和 排序 堆（优先队列） 👍 92 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution2406{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {
        map<int, int> diff;
        for (auto &p : intervals)
            ++diff[p[0]], --diff[p[1] + 1];
        int ans = 0, sum = 0;
        for (auto &[_, d] : diff)
            ans = max(ans, sum += d);
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2406;
int main() {
    Solution solution;

    return 0;
}