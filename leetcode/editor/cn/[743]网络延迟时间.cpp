/**
有 n 个网络节点，标记为 1 到 n。 

 给你一个列表 times，表示信号经过 有向 边的传递时间。 times[i] = (ui, vi, wi)，其中 ui 是源节点，vi 是目标节点， wi 
是一个信号从源节点传递到目标节点的时间。 

 现在，从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1 。 

 

 示例 1： 

 

 
输入：times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
输出：2
 

 示例 2： 

 
输入：times = [[1,2,1]], n = 2, k = 1
输出：1
 

 示例 3： 

 
输入：times = [[1,2,1]], n = 2, k = 2
输出：-1
 

 

 提示： 

 
 1 <= k <= n <= 100 
 1 <= times.length <= 6000 
 times[i].length == 3 
 1 <= ui, vi <= n 
 ui != vi 
 0 <= wi <= 100 
 所有 (ui, vi) 对都 互不相同（即，不含重复边） 
 

 Related Topics 深度优先搜索 广度优先搜索 图 最短路 堆（优先队列） 👍 872 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution743{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:

    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 堆优化的dijkstra算法
        using PII = pair<int, int>;
        vector<vector<pair<int, int>>> g(n);
        for (const auto& t : times) {
            int u = t[0] - 1, v = t[1] - 1, w = t[2];// 存i - 1
            g[u].emplace_back(v, w);
        }
        vector<int> dist(n, 0x3f3f3f3f);  // 存储k号点到每个点的最短距离
        dist[k - 1] = 0;
        priority_queue<PII, vector<PII>, greater<PII>> pq; // 小顶堆
        pq.emplace(0, k - 1); // 距离为0，点为k - 1
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue; // 如果当前距离大于已知最短距离，跳过
            for (const auto& [v, w] : g[u]) {
                if (dist[v] > d + w) { // 如果通过u到v的距离更短
                    dist[v] = d + w;
                    pq.emplace(dist[v], v); // 更新堆
                }
            }
        }
        int ans = *max_element(dist.begin(), dist.end());
        return ans == 0x3f3f3f3f? -1 : ans;
        // vector<vector<int>> g(n, vector<int>(n, 0x3f3f3f3f));
        // for (const auto& t : times) {
        //     int u = t[0] - 1, v = t[1] - 1, w = t[2];// 存i - 1
        //     g[u][v] = min(g[u][v], w);
        // }
        // vector<int> dist(n, 0x3f3f3f3f);  // 存储k号点到每个点的最短距离
        // vector<bool> visited(n, false);   // 存储每个点的最短路是否已确定
        // dist[k - 1] = 0;
        //
        // for (int i = 0; i < n; i++) // 循环n次，每次确定一个点的最短路
        // {
        //     int u = -1;
        //     // 1. 找到未访问顶点中，dist最小的那个
        //     for (int j = 0; j < n; j++) {
        //         if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
        //             u = j;
        //         }
        //     }
        //
        //     if (u == -1) return -1;
        //     visited[u] = true;
        //
        //     // 2. 用u的距离更新其所有邻接点的距离
        //     for (int v = 0; v < n; v++) {
        //         dist[v] = min(dist[v], dist[u] + g[u][v]);
        //     }
        // }
        //
        // int ans = *max_element(dist.begin(), dist.end());
        // return ans == 0x3f3f3f3f ? -1 : ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution743;
int main() {
    Solution solution;

    return 0;
}