//给你一个细长的画，用数轴表示。这幅画由若干有重叠的线段表示，每个线段有 独一无二 的颜色。给你二维整数数组 segments ，其中 segments[i]
// = [starti, endi, colori] 表示线段为 半开区间 [starti, endi) 且颜色为 colori 。 
//
// 线段间重叠部分的颜色会被 混合 。如果有两种或者更多颜色混合时，它们会形成一种新的颜色，用一个 集合 表示这个混合颜色。 
//
// 
// 比方说，如果颜色 2 ，4 和 6 被混合，那么结果颜色为 {2,4,6} 。 
// 
//
// 为了简化题目，你不需要输出整个集合，只需要用集合中所有元素的 和 来表示颜色集合。 
//
// 你想要用 最少数目 不重叠 半开区间 来 表示 这幅混合颜色的画。这些线段可以用二维数组 painting 表示，其中 painting[j] = [
//leftj, rightj, mixj] 表示一个 半开区间[leftj, rightj) 的颜色 和 为 mixj 。 
//
// 
// 比方说，这幅画由 segments = [[1,4,5],[1,7,7]] 组成，那么它可以表示为 painting = [[1,4,12],[4,7,7
//]] ，因为： 
// 
//
// 
// [1,4) 由颜色 {5,7} 组成（和为 12），分别来自第一个线段和第二个线段。 
// [4,7) 由颜色 {7} 组成，来自第二个线段。 
// 
// 
//
//
// 请你返回二维数组 painting ，它表示最终绘画的结果（没有 被涂色的部分不出现在结果中）。你可以按 任意顺序 返回最终数组的结果。 
//
// 半开区间 [a, b) 是数轴上点 a 和点 b 之间的部分，包含 点 a 且 不包含 点 b 。 
//
// 
//
// 示例 1： 
// 
// 
//输入：segments = [[1,4,5],[4,7,7],[1,7,9]]
//输出：[[1,4,14],[4,7,16]]
//解释：绘画结果可以表示为：
//- [1,4) 颜色为 {5,9} （和为 14），分别来自第一和第二个线段。
//- [4,7) 颜色为 {7,9} （和为 16），分别来自第二和第三个线段。
// 
//
// 示例 2： 
// 
// 
//输入：segments = [[1,7,9],[6,8,15],[8,10,7]]
//输出：[[1,6,9],[6,7,24],[7,8,15],[8,10,7]]
//解释：绘画结果可以以表示为：
//- [1,6) 颜色为 9 ，来自第一个线段。
//- [6,7) 颜色为 {9,15} （和为 24），来自第一和第二个线段。
//- [7,8) 颜色为 15 ，来自第二个线段。
//- [8,10) 颜色为 7 ，来自第三个线段。
// 
//
// 示例 3： 
// 
// 
//输入：segments = [[1,4,5],[1,4,7],[4,7,1],[4,7,11]]
//输出：[[1,4,12],[4,7,12]]
//解释：绘画结果可以表示为：
//- [1,4) 颜色为 {5,7} （和为 12），分别来自第一和第二个线段。
//- [4,7) 颜色为 {1,11} （和为 12），分别来自第三和第四个线段。
//注意，只返回一个单独的线段 [1,7) 是不正确的，因为混合颜色的集合不相同。
// 
//
// 
//
// 提示： 
//
// 
// 1 <= segments.length <= 2 * 10⁴ 
// segments[i].length == 3 
// 1 <= starti < endi <= 10⁵ 
// 1 <= colori <= 10⁹ 
// 每种颜色 colori 互不相同。 
// 
//
// Related Topics 数组 哈希表 前缀和 排序 👍 38 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution1943{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        map<long long, long long> diff;
        for (auto &p : segments) {
            diff[p[0]] += p[2];
            diff[p[1]] -= p[2];
        }
        long long sum = 0;
        for (auto& [pos, color]: diff) {
            sum += color;
            color = sum;
        }
        long long l = diff.begin()->first;
        long long color = diff.begin()->second;
        long long r;
        vector<vector<long long>> ans;
        for (auto it = ++diff.begin(); it != diff.end(); it++) {
            r = it->first;
            if (color > 0) ans.emplace_back(vector<long long>{l, r, color});
            l = it->first;
            color = it->second;
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1943;
int main() {
    Solution solution;

    return 0;
}