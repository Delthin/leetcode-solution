/**
给你一个 有向无环图 ， n 个节点编号为 0 到 n-1 ，以及一个边数组 edges ，其中 edges[i] = [fromi, toi] 表示一条从点 
fromi 到点 toi 的有向边。 

 找到最小的点集使得从这些点出发能到达图中所有点。题目保证解存在且唯一。 

 你可以以任意顺序返回这些节点编号。 

 

 示例 1： 

 

 输入：n = 6, edges = [[0,1],[0,2],[2,5],[3,4],[4,2]]
输出：[0,3]
解释：从单个节点出发无法到达所有节点。从 0 出发我们可以到达 [0,1,2,5] 。从 3 出发我们可以到达 [3,4,2,5] 。所以我们输出 [0,3] 
。 

 示例 2： 

 

 输入：n = 5, edges = [[0,1],[2,1],[3,1],[1,4],[2,4]]
输出：[0,2,3]
解释：注意到节点 0，3 和 2 无法从其他节点到达，所以我们必须将它们包含在结果点集中，这些点都能到达节点 1 和 4 。
 

 

 提示： 

 
 2 <= n <= 10^5 
 1 <= edges.length <= min(10^5, n * (n - 1) / 2) 
 edges[i].length == 2 
 0 <= fromi, toi < n 
 所有点对 (fromi, toi) 互不相同。 
 

 Related Topics 图 👍 108 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1557{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        auto ans = vector<int>();
        unordered_set<int> reachable;
        for (const auto& edge : edges) {
            reachable.insert(edge[1]);
        }
        for (int i = 0; i < n; ++i) {
            if (reachable.find(i) == reachable.end()) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1557;
int main() {
    Solution solution;

    return 0;
}