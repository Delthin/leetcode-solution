/**
有 n 个项目，每个项目或者不属于任何小组，或者属于 m 个小组之一。group[i] 表示第 i 个项目所属的小组，如果第 i 个项目不属于任何小组，则 
group[i] 等于 -1。项目和小组都是从零开始编号的。可能存在小组不负责任何项目，即没有任何项目属于这个小组。 

 请你帮忙按要求安排这些项目的进度，并返回排序后的项目列表： 

 
 同一小组的项目，排序后在列表中彼此相邻。 
 项目之间存在一定的依赖关系，我们用一个列表 beforeItems 来表示，其中 beforeItems[i] 表示在进行第 i 个项目前（位于第 i 个项目
左侧）应该完成的所有项目。 
 

 如果存在多个解决方案，只需要返回其中任意一个即可。如果没有合适的解决方案，就请返回一个 空列表 。 

 

 示例 1： 

 

 
输入：n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,
6],[],[],[]]
输出：[6,3,4,1,5,2,0,7]
 

 示例 2： 

 
输入：n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3]
,[],[4],[]]
输出：[]
解释：与示例 1 大致相同，但是在排序后的列表中，4 必须放在 6 的前面。
 

 

 提示： 

 
 1 <= m <= n <= 3 * 10⁴ 
 group.length == beforeItems.length == n 
 -1 <= group[i] <= m - 1 
 0 <= beforeItems[i].length <= n - 1 
 0 <= beforeItems[i][j] <= n - 1 
 i != beforeItems[i][j] 
 beforeItems[i] 不含重复元素 
 

 Related Topics 深度优先搜索 广度优先搜索 图 拓扑排序 👍 251 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1203{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {

vector<int> topological_sort(vector<vector<int>>& adj, vector<int>& in_degree, vector<int>& items) {
    queue<int> q;
    vector<int> topo_order;
    // 1. 将所有入度为0的节点入队
    for (auto& item : items) {
        if (in_degree[item] == 0) {
            q.push(item);
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
    return topo_order.size() == items.size() ? topo_order : vector<int>();
}
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        vector<vector<int>> groupItem(n + m);
        for (int i = 0; i < n; i++) {
            // 如果项目不属于任何组，则将其分配到一个新的组
            if (group[i] == -1) {
                group[i] = m++;
            }
            groupItem[group[i]].push_back(i);
        }
        vector<vector<int>> group_adj(m);
        vector<vector<int>> item_adj(n);
        vector<int> group_in_degree(m, 0);
        vector<int> item_in_degree(n, 0);
        for (int i = 0; i < n; i++) {
            int curGroup = group[i];
            for (int j: beforeItems[i]) {
                int preGroup = group[j];
                if (curGroup != preGroup) {
                    group_adj[preGroup].push_back(curGroup);
                    group_in_degree[curGroup]++;
                } else {
                    item_adj[j].push_back(i);
                    item_in_degree[i]++;
                }
            }
        }
        vector<int> group_id(m);
        iota(group_id.begin(), group_id.end(), 0);
        vector<int> group_order = topological_sort(group_adj, group_in_degree, group_id);
        if (group_order.empty()) {
            return {};
        }
        vector<int> res;
        for (int g : group_order) {
            int size = groupItem[g].size();
            if (size == 0) continue;
            vector<int> item_order = topological_sort(item_adj, item_in_degree, groupItem[g]);
            if (item_order.empty()) {
                return {};
            }
            res.insert(res.end(), item_order.begin(), item_order.end());
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1203;
int main() {
    Solution solution;
    int n = 8, m = 2;
    vector<int> group = {-1,-1,1,0,0,1,0,-1};
    vector<vector<int>> beforeItems = {{},{6},{5},{6},{3,6},{},{},{}}; // 注意这里的beforeItems是二维数组
    vector<int> res = solution.sortItems(n, m, group, beforeItems);
    for (int i : res) {
        cout << i << " ";
    }
    return 0;
}