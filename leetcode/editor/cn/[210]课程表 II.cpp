/**
现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。给你一个数组 prerequisites ，其中 
prerequisites[i] = [ai, bi] ，表示在选修课程 ai 前 必须 先选修 bi 。 

 
 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1] 。 
 

 返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组 。 

 

 示例 1： 

 
输入：numCourses = 2, prerequisites = [[1,0]]
输出：[0,1]
解释：总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。
 

 示例 2： 

 
输入：numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
输出：[0,2,1,3]
解释：总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。 

 示例 3： 

 
输入：numCourses = 1, prerequisites = []
输出：[0]
 

 
提示：

 
 1 <= numCourses <= 2000 
 0 <= prerequisites.length <= numCourses * (numCourses - 1) 
 prerequisites[i].length == 2 
 0 <= ai, bi < numCourses 
 ai != bi 
 所有[ai, bi] 互不相同 
 

 Related Topics 深度优先搜索 广度优先搜索 图 拓扑排序 👍 1042 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution210{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<vector<int>> adj; // 邻接表存图
    vector<int> in_degree;   // 存储每个节点的入度
    vector<int> topo_order;  // 存储拓扑排序的结果
    int n;                   // 节点数量

    bool topological_sort() {
        queue<int> q;

        // 1. 将所有入度为0的节点入队
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

        // 2. BFS过程
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo_order.push_back(u);

            // 遍历 u 的所有邻接点 v
            for (int v : adj[u]) {
                in_degree[v]--; // 将 v 的入度减1
                if (in_degree[v] == 0) {
                    q.push(v); // 如果 v 的入度变为0，则入队
                }
            }
        }

        // 3. 判断是否有环
        // 如果拓扑序列中的节点数等于图的总节点数，说明无环
        return topo_order.size() == n;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        n = numCourses;
        adj.resize(n);
        in_degree.resize(n);

        // 1. 构建邻接表和入度数组
        for (const auto& edge : prerequisites) {
            int u = edge[1];
            int v = edge[0];
            adj[u].push_back(v);
            in_degree[v]++;
        }

        // 2. 执行拓扑排序
        if (topological_sort()) {
            return topo_order; // 返回拓扑排序结果
        }
        return {}; // 存在环，返回空数组
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution210;
int main() {
    Solution solution;

    return 0;
}