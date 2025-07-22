/**
你总共需要上
 numCourses 门课，课程编号依次为 0 到 numCourses-1 。你会得到一个数组 prerequisite ，其中
 prerequisites[i] = [ai, bi] 表示如果你想选
 bi 课程，你 必须 先选
 ai 课程。 

 
 有的课会有直接的先修课程，比如如果想上课程 1 ，你必须先上课程 0 ，那么会以 [0,1] 数对的形式给出先修课程数对。 
 

 先决条件也可以是 间接 的。如果课程 a 是课程 b 的先决条件，课程 b 是课程 c 的先决条件，那么课程 a 就是课程 c 的先决条件。 

 你也得到一个数组
 queries ，其中
 queries[j] = [uj, vj]。对于第 j 个查询，您应该回答课程
 uj 是否是课程
 vj 的先决条件。 

 返回一个布尔数组 answer ，其中 answer[j] 是第 j 个查询的答案。 

 

 示例 1： 

 

 
输入：numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
输出：[false,true]
解释：[1, 0] 数对表示在你上课程 0 之前必须先上课程 1。
课程 0 不是课程 1 的先修课程，但课程 1 是课程 0 的先修课程。
 

 示例 2： 

 
输入：numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
输出：[false,false]
解释：没有先修课程对，所以每门课程之间是独立的。
 

 示例 3： 

 

 
输入：numCourses = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
输出：[true,true]
 

 

 提示： 

 
 

 
 2 <= numCourses <= 100 
 0 <= prerequisites.length <= (numCourses * (numCourses - 1) / 2) 
 prerequisites[i].length == 2 
 0 <= ai, bi <= numCourses - 1 
 ai != bi 
 每一对
 [ai, bi] 都 不同 
 先修课程图中没有环。 
 1 <= queries.length <= 10⁴ 
 0 <= ui, vi <= numCourses - 1 
 ui != vi 
 

 Related Topics 深度优先搜索 广度优先搜索 图 拓扑排序 👍 221 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1462{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        // floyd
        vector<vector<bool>> f(n, vector<bool>(n, false));
        for (const auto& edge : edges) {
            f[edge[0]][edge[1]] = true; // edge[0] 是 edge[1] 的先修课程
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (f[i][k] && f[k][j]) {
                        f[i][j] = true; // 如果 i 是 k 的先修课程，且 k 是 j 的先修课程，那么 i 也是 j 的先修课程
                    }
                }
            }
        }
        vector<bool> ans;
        for (const auto& query : queries) {
            ans.push_back(f[query[0]][query[1]]);
        }
        return ans;

        // topological sort
        // vector<int> indegree(n, 0);
        // vector<vector<int>> graph(n);
        // vector<vector<bool>> f (n, vector<bool>(n, false));
        // for (const auto& edge : edges) {
        //     graph[edge[0]].push_back(edge[1]);
        //     indegree[edge[1]]++;
        // }
        // queue<int> q;
        // for (int i = 0; i < n; ++i) {
        //     if (indegree[i] == 0) {
        //         q.push(i);
        //         f[i][i] = true; // 自己是自己的先修课程
        //     }
        // }
        // while (!q.empty()) {
        //     int u = q.front();
        //     q.pop();
        //     for (int v : graph[u]) {
        //         indegree[v]--;
        //         if (indegree[v] == 0) {
        //             q.push(v);
        //         }
        //         // 如果 u 是 v 的先修课程，那么 u 的所有先修课程也是 v 的先修课程
        //         for (int k = 0; k < n; ++k) {
        //             if (f[k][u]) {
        //                 f[k][v] = true;
        //             }
        //         }
        //         f[u][v] = true; // u 是 v 的先修课程
        //     }
        // }
        // vector<bool> ans;
        // for (const auto& query : queries) {
        //     ans.push_back(f[query[0]][query[1]]);
        // }
        // return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1462;
int main() {
    Solution solution;

    return 0;
}