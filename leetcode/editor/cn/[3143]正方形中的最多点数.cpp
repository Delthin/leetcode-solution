//给你一个二维数组 points 和一个字符串 s ，其中 points[i] 表示第 i 个点的坐标，s[i] 表示第 i 个点的 标签 。 
//
// 如果一个正方形的中心在 (0, 0) ，所有边都平行于坐标轴，且正方形内 不 存在标签相同的两个点，那么我们称这个正方形是 合法 的。 
//
// 请你返回 合法 正方形中可以包含的 最多 点数。 
//
// 注意： 
//
// 
// 如果一个点位于正方形的边上或者在边以内，则认为该点位于正方形内。 
// 正方形的边长可以为零。 
// 
//
// 
//
// 示例 1： 
//
// 
//
// 
// 输入：points = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], s = "abdca" 
// 
//
// 输出：2 
//
// 解释： 
//
// 边长为 4 的正方形包含两个点 points[0] 和 points[1] 。 
//
// 示例 2： 
//
// 
//
// 
// 输入：points = [[1,1],[-2,-2],[-2,2]], s = "abb" 
// 
//
// 输出：1 
//
// 解释： 
//
// 边长为 2 的正方形包含 1 个点 points[0] 。 
//
// 示例 3： 
//
// 
// 输入：points = [[1,1],[-1,-1],[2,-2]], s = "ccd" 
// 
//
// 输出：0 
//
// 解释： 
//
// 任何正方形都无法只包含 points[0] 和 points[1] 中的一个点，所以合法正方形中都不包含任何点。 
//
// 
//
// 提示： 
//
// 
// 1 <= s.length, points.length <= 10⁵ 
// points[i].length == 2 
// -10⁹ <= points[i][0], points[i][1] <= 10⁹ 
// s.length == points.length 
// points 中的点坐标互不相同。 
// s 只包含小写英文字母。 
// 
//
// Related Topics 数组 哈希表 字符串 二分查找 排序 👍 42 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution3143{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        int n = points.size();
        auto check = [&] (int w) -> tuple<bool, int>{
            vector<bool> set(26, false);
            int dots = 0;
            for (int i = 0; i < n; i++) {
                int x = points[i][0], y = points[i][1];
                if (abs(x) <= w && abs(y) <= w) {
                    dots++;
                    char c = s.at(i);
                    if (set[c - 'a'] == true) return {false, 0};
                    set[c - 'a'] = true;
                }
            }
            return {true, dots};
        };
        int l = -1, r = 1e9 + 1;
        int ans = 0;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            auto [valid, dots] = check(mid);
            if (valid) {
                ans = max(dots, ans);
                l = mid;
            } else r = mid;
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3143;
int main() {
    Solution solution;

    return 0;
}