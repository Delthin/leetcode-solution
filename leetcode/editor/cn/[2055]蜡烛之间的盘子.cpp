/**
给你一个长桌子，桌子上盘子和蜡烛排成一列。给你一个下标从 0 开始的字符串 s ，它只包含字符 '*' 和 '|' ，其中 '*' 表示一个 盘子 ，'|' 表
示一支 蜡烛 。 

 同时给你一个下标从 0 开始的二维整数数组 queries ，其中 queries[i] = [lefti, righti] 表示 子字符串 s[lefti.
..righti] （包含左右端点的字符）。对于每个查询，你需要找到 子字符串中 在 两支蜡烛之间 的盘子的 数目 。如果一个盘子在 子字符串中 左边和右边 都
 至少有一支蜡烛，那么这个盘子满足在 两支蜡烛之间 。 

 
 比方说，s = "||**||**|*" ，查询 [3, 8] ，表示的是子字符串 "*||**|" 。子字符串中在两支蜡烛之间的盘子数目为 2 ，子字符串中
右边两个盘子在它们左边和右边 都 至少有一支蜡烛。 
 

 请你返回一个整数数组 answer ，其中 answer[i] 是第 i 个查询的答案。 

 

 示例 1: 

 

 输入：s = "**|**|***|", queries = [[2,5],[5,9]]
输出：[2,3]
解释：
- queries[0] 有两个盘子在蜡烛之间。
- queries[1] 有三个盘子在蜡烛之间。
 

 示例 2: 

 

 输入：s = "***|**|*****|**||**|*", queries = [[1,17],[4,5],[14,17],[5,11],[15,16]]

输出：[9,0,0,0,0]
解释：
- queries[0] 有 9 个盘子在蜡烛之间。
- 另一个查询没有盘子在蜡烛之间。
 

 

 提示： 

 
 3 <= s.length <= 10⁵ 
 s 只包含字符 '*' 和 '|' 。 
 1 <= queries.length <= 10⁵ 
 queries[i].length == 2 
 0 <= lefti <= righti < s.length 
 

 Related Topics 数组 字符串 二分查找 前缀和 👍 195 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2055{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.size();
        // 预处理每个位置右侧最近的蜡烛位置
        vector<int> right(n, n);
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '|') {
                right[i] = i;
            } else if (i < n - 1) {
                right[i] = right[i + 1];
            }
        }

        // 预处理每个位置左侧最近的蜡烛位置
        vector<int> left(n, -1);
        for (int i = 0; i < n; i++) {
            if (s[i] == '|') {
                left[i] = i;
            } else if (i > 0) {
                left[i] = left[i - 1];
            }
        }

        // 预处理前缀和：到每个位置的盘子总数
        vector<int> plateCount(n + 1, 0);
        for (int i = 0; i < n; i++) {
            plateCount[i + 1] = plateCount[i] + (s[i] == '*' ? 1 : 0);
        }

        // 处理查询
        vector<int> answer;
        for (auto &q : queries) {
            int l = q[0], r = q[1];

            // 找到查询范围内最左和最右的蜡烛
            int leftCandle = right[l];  // l右侧最近的蜡烛
            int rightCandle = left[r];  // r左侧最近的蜡烛

            // 如果没有找到有效的蜡烛对，或者左蜡烛在右蜡烛右边
            if (leftCandle >= rightCandle) {
                answer.push_back(0);
            } else {
                // 计算两蜡烛之间的盘子数
                answer.push_back(plateCount[rightCandle] - plateCount[leftCandle + 1]);
            }
        }

        return answer;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2055;
int main() {
    Solution solution;
    string s = "**|**|***|";
    vector<vector<int>> queries = {{2,5}, {5,9}};
    solution.platesBetweenCandles(s,queries);
    return 0;
}