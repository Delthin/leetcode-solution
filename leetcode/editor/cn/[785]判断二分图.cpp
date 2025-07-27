/**
存在一个 无向图 ，图中有 n 个节点。其中每个节点都有一个介于 0 到 n - 1 之间的唯一编号。给你一个二维数组 graph ，其中 graph[u] 是
一个节点数组，由节点 u 的邻接节点组成。形式上，对于 graph[u] 中的每个 v ，都存在一条位于节点 u 和节点 v 之间的无向边。该无向图同时具有以下
属性：

 
 不存在自环（graph[u] 不包含 u）。 
 不存在平行边（graph[u] 不包含重复值）。 
 如果 v 在 graph[u] 内，那么 u 也应该在 graph[v] 内（该图是无向图） 
 这个图可能不是连通图，也就是说两个节点 u 和 v 之间可能不存在一条连通彼此的路径。 
 

 二分图 定义：如果能将一个图的节点集合分割成两个独立的子集 A 和 B ，并使图中的每一条边的两个节点一个来自 A 集合，一个来自 B 集合，就将这个图称为 
二分图 。 

 如果图是二分图，返回 true ；否则，返回 false 。 

 

 示例 1： 
 
 
输入：graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
输出：false
解释：不能将节点分割成两个独立的子集，以使每条边都连通一个子集中的一个节点与另一个子集中的一个节点。 

 示例 2： 
 
 
输入：graph = [[1,3],[0,2],[1,3],[0,2]]
输出：true
解释：可以将节点分成两组: {0, 2} 和 {1, 3} 。 

 

 提示： 

 
 graph.length == n 
 1 <= n <= 100 
 0 <= graph[u].length < n 
 0 <= graph[u][i] <= n - 1 
 graph[u] 不会包含 u 
 graph[u] 的所有值 互不相同 
 如果 graph[u] 包含 v，那么 graph[v] 也会包含 u 
 

 Related Topics 深度优先搜索 广度优先搜索 并查集 图 👍 573 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution785{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    vector<vector<int>> adj; // 邻接表存图
    vector<int> color;       // 0:未染色, 1:颜色1, 2:颜色2
    int n = 0;                   // 节点数量
    bool dfs_color(int u, int c) {
        color[u] = c;
        for (int v : adj[u]) {
            if (color[v] == 0) { // 如果邻接点未染色
                // 递归地给v染上另一种颜色，如果子过程失败，则直接返回false
                if (!dfs_color(v, 3 - c)) {
                    return false;
                }
            } else if (color[v] == c) { // 如果邻接点颜色与当前点相同，产生冲突
                return false;
            }
        }
        return true;
    }

// 检查整个图是否是二分图
    bool is_bipartite() {
        for (int i = 0; i < n; ++i) {
            if (color[i] == 0) { // 如果节点i所在的连通分量还未被染色
                // 从节点i开始，用颜色1进行染色，如果失败则图不是二分图
                if (!dfs_color(i, 1)) {
                    return false;
                }
            }
        }
        return true;
    }

public:
    bool isBipartite(vector<vector<int>>& graph) {
        n = graph.size();
        adj = graph;
        color.resize(n, 0);
        return is_bipartite();
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution785;
int main() {
    Solution solution;

    return 0;
}