/**
力扣数据中心有 n 台服务器，分别按从 0 到 n-1 的方式进行了编号。它们之间以 服务器到服务器 的形式相互连接组成了一个内部集群，连接是无向的。用 
connections 表示集群网络，connections[i] = [a, b] 表示服务器 a 和 b 之间形成连接。任何服务器都可以直接或者间接地通过网络到达
任何其他服务器。 

 关键连接 是在该集群中的重要连接，假如我们将它移除，便会导致某些服务器无法访问其他服务器。 

 请你以任意顺序返回该集群内的所有 关键连接 。 

 

 示例 1： 

 

 
输入：n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
输出：[[1,3]]
解释：[[3,1]] 也是正确的。 

 示例 2: 

 
输入：n = 2, connections = [[0,1]]
输出：[[0,1]]
 

 

 提示： 

 
 2 <= n <= 10⁵ 
 n - 1 <= connections.length <= 10⁵ 
 0 <= ai, bi <= n - 1 
 ai != bi 
 不存在重复的连接 
 

 Related Topics 深度优先搜索 图 双连通分量 👍 304 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1192{
//leetcode submit region begin(Prohibit modification and deletion)
    class Solution {
    public:
        vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
            vector<vector<int>> adj(n); // 邻接表存图
            for (auto& conn : connections) {
                adj[conn[0]].push_back(conn[1]);
                adj[conn[1]].push_back(conn[0]);
            }
            vector<int> dfn(n, 0);    // 时间戳
            vector<int> low(n, 0);    // 能追溯到的最早祖先
            vector<vector<int>> res;
            int timestamp = 0;

            // 定义 tarjan 函数为 lambda 表达式
            function<void(int, int)> tarjan = [&](int u, int parent) mutable {
                // 1. 初始化 dfn 和 low
                dfn[u] = low[u] = ++timestamp;

                // 2. 遍历 u 的邻接点 v
                for (int v : adj[u]) {
                    if (v == parent) continue; // 避免重复访问父节点
                    if (dfn[v] == 0) { // Case 1: v 未被访问，是树边
                        tarjan(v, u);
                        low[u] = min(low[u], low[v]);
                        // 判断是否为桥
                        if (low[v] > dfn[u]) {
                            res.push_back({u, v});
                        }
                    } else { // Case 2: v 被访问过，是返祖边
                        low[u] = min(low[u], dfn[v]);
                    }
                }
            };

            // 4. 对每个未访问的节点执行 Tarjan 算法
            for (int i = 0; i < n; ++i) {
                if (dfn[i] == 0) {
                    tarjan(i, -1);
                }
            }
            return res;
        }
    };
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1192;

int main() {
    Solution solution;

    return 0;
}