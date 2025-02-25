//给定 m 个数组，每个数组都已经按照升序排好序了。 
//
// 现在你需要从两个不同的数组中选择两个整数（每个数组选一个）并且计算它们的距离。两个整数 a 和 b 之间的距离定义为它们差的绝对值 |a-b| 。 
//
// 返回最大距离。 
//
// 示例 1： 
//
// 
//输入：[[1,2,3],[4,5],[1,2,3]]
//输出：4
//解释：
//一种得到答案 4 的方法是从第一个数组或者第三个数组中选择 1，同时从第二个数组中选择 5 。
// 
//
// 示例 2： 
//
// 
//输入：arrays = [[1],[1]]
//输出：0
// 
//
// 
//
// 提示： 
//
// 
// m == arrays.length 
// 2 <= m <= 10⁵ 
// 1 <= arrays[i].length <= 500 
// -10⁴ <= arrays[i][j] <= 10⁴ 
// arrays[i] 以 升序 排序。 
// 所有数组中最多有 10⁵ 个整数。 
// 
//
// 
//
// Related Topics 贪心 数组 👍 130 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution624{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int min_ans = 10005, min_all = 10005;
        int max_ans = -10005, max_all = -10005;
        for (const auto& arr: arrays) {
            int min_arr = arr[0];
            int max_arr = arr[arr.size()-1];
            if (max_all - min_arr >= max_ans - min_ans) {
                min_ans = min_arr;
                max_ans = max_all;
            }
            if (max_arr - min_all > max_ans - min_ans) {
                min_ans = min_all;
                max_ans = max_arr;
            }
            max_all = max(max_arr, max_all);
            min_all = min(min_arr, min_all);
        }
        return max_ans - min_ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution624;
int main() {
    Solution solution;

    return 0;
}