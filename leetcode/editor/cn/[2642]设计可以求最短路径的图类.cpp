/**
给你一个有 n 个节点的 有向带权 图，节点编号为 0 到 n - 1 。图中的初始边用数组 edges 表示，其中 edges[i] = [fromi, 
toi, edgeCosti] 表示从 fromi 到 toi 有一条代价为 edgeCosti 的边。 

 请你实现一个 Graph 类： 

 
 Graph(int n, int[][] edges) 初始化图有 n 个节点，并输入初始边。 
 addEdge(int[] edge) 向边集中添加一条边，其中 edge = [from, to, edgeCost] 。数据保证添加这条边之前对应的两个节
点之间没有有向边。 
 int shortestPath(int node1, int node2) 返回从节点 node1 到 node2 的路径 最小 代价。如果路径不存在，返回
 -1 。一条路径的代价是路径中所有边代价之和。 
 

 

 示例 1： 

 

 输入：
["Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"]
[[4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]], [3, 2], [0, 3], [[1, 3, 4]],
 [0, 3]]
输出：
[null, 6, -1, null, 6]

解释：
Graph g = new Graph(4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]);
g.shortestPath(3, 2); // 返回 6 。从 3 到 2 的最短路径如第一幅图所示：3 -> 0 -> 1 -> 2 ，总代价为 3 + 2
 + 1 = 6 。
g.shortestPath(0, 3); // 返回 -1 。没有从 0 到 3 的路径。
g.addEdge([1, 3, 4]); // 添加一条节点 1 到节点 3 的边，得到第二幅图。
g.shortestPath(0, 3); // 返回 6 。从 0 到 3 的最短路径为 0 -> 1 -> 3 ，总代价为 2 + 4 = 6 。
 

 

 提示： 

 
 1 <= n <= 100 
 0 <= edges.length <= n * (n - 1) 
 edges[i].length == edge.length == 3 
 0 <= fromi, toi, from, to, node1, node2 <= n - 1 
 1 <= edgeCosti, edgeCost <= 10⁶ 
 图中任何时候都不会有重边和自环。 
 调用 addEdge 至多 100 次。 
 调用 shortestPath 至多 100 次。 
 

 Related Topics 图 设计 最短路 堆（优先队列） 👍 66 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2642{
//leetcode submit region begin(Prohibit modification and deletion)
class Graph {
public:
    const long long INF = 1e18;
    using PII = pair<long long, int>; // {distance, vertex}
    vector<vector<PII>> adj_weighted;
    Graph(int n, vector<vector<int>>& edges) {
        adj_weighted.resize(n);
        for (auto& edge : edges) {
            adj_weighted[edge[0]].push_back({edge[1], edge[2]});
        }
    }
    
    void addEdge(vector<int> edge) {
        int from = edge[0], to = edge[1], weight = edge[2];
        adj_weighted[from].push_back({to, weight});
    }

    long long dijkstra(int start,int end, const vector<vector<pair<long long, int>>>& adj) {
        int n = adj.size();
        vector<long long> dist(n + 1, INF);
        dist[start] = 0;

        // 小根堆
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue; // 剪枝：已找到更短的路径
            if (u == end) return dist[end]; // 剪枝：到达目标节点

            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist[end] == INF ? -1 : dist[end]; // 如果到达不了目标节点，返回 -1
    }

    int shortestPath(int node1, int node2) {
        return dijkstra(node1, node2, adj_weighted);
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2642;
int main() {
    Solution solution;

    return 0;
}