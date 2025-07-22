/**
给你一个 n 个节点的无向带权图，节点编号为 0 到 n - 1 。图中总共有 m 条边，用二维数组 edges 表示，其中 edges[i] = [ai, 
bi, wi] 表示节点 ai 和 bi 之间有一条边权为 wi 的边。 

 对于节点 0 为出发点，节点 n - 1 为结束点的所有最短路，你需要返回一个长度为 m 的 boolean 数组 answer ，如果 edges[i] 至
少 在其中一条最短路上，那么 answer[i] 为 true ，否则 answer[i] 为 false 。 

 请你返回数组 answer 。 

 注意，图可能不连通。 

 

 示例 1： 

 

 
 输入：n = 6, edges = [[0,1,4],[0,2,1],[1,3,2],[1,4,3],[1,5,1],[2,3,1],[3,5,3],[4,5
,2]] 
 

 输出：[true,true,true,false,true,true,true,false] 

 解释： 

 以下为节点 0 出发到达节点 5 的 所有 最短路： 

 
 路径 0 -> 1 -> 5 ：边权和为 4 + 1 = 5 。 
 路径 0 -> 2 -> 3 -> 5 ：边权和为 1 + 1 + 3 = 5 。 
 路径 0 -> 2 -> 3 -> 1 -> 5 ：边权和为 1 + 1 + 2 + 1 = 5 。 
 

 示例 2： 

 

 
 输入：n = 4, edges = [[2,0,1],[0,1,1],[0,3,4],[3,2,2]] 
 

 输出：[true,false,false,true] 

 解释： 

 只有一条从节点 0 出发到达节点 3 的最短路 0 -> 2 -> 3 ，边权和为 1 + 2 = 3 。 

 

 提示： 

 
 2 <= n <= 5 * 10⁴ 
 m == edges.length 
 1 <= m <= min(5 * 10⁴, n * (n - 1) / 2) 
 0 <= ai, bi < n 
 ai != bi 
 1 <= wi <= 10⁵ 
 图中没有重边。 
 

 Related Topics 深度优先搜索 广度优先搜索 图 最短路 堆（优先队列） 👍 21 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution3123{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    const long long INF = 1e18; // 使用long long防止溢出
    using PII = pair<long long, int>; // {distance, vertex}
public:
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        vector<vector<tuple<int, int, int>>> adj_weighted(n);
        for (int i = 0; i < edges.size(); ++i) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            adj_weighted[u].emplace_back(w, v, i);
            adj_weighted[v].emplace_back(w, u, i);
        }
        vector<bool> answer(edges.size(), false);
        vector<long long> dist(n, INF);
        dist[0] = 0;
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        pq.push({0, 0});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue; // 如果当前距离大于已知最短距离，跳过
            for (const auto& [w, v, i] : adj_weighted[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        // BFS倒序将最短路的边标记为true
        queue<int> q;
        vector<bool> visited(n, false);
        visited[n - 1] = true;
        q.emplace(n - 1);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto [w, u, i] : adj_weighted[v]) {
                if (dist[u] + w == dist[v]) { // 如果u到v的边在最短路上
                    answer[i] = true; // 标记这条边
                    if (!visited[u]) { // 如果u还没被访问过
                        visited[u] = true;
                        q.emplace(u);
                    }
                }
            }
        }
        return answer;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3123;
int main() {
    Solution solution;

    return 0;
}