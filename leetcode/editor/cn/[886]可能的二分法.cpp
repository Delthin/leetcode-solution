/**
给定一组 n 人（编号为 1, 2, ..., n）， 我们想把每个人分进任意大小的两组。每个人都可能不喜欢其他人，那么他们不应该属于同一组。 

 给定整数 n 和数组 dislikes ，其中 dislikes[i] = [ai, bi] ，表示不允许将编号为 ai 和 bi的人归入同一组。当可以用这种
方法将所有人分进两组时，返回 true；否则返回 false。 

 

 
 

 示例 1： 

 
输入：n = 4, dislikes = [[1,2],[1,3],[2,4]]
输出：true
解释：group1 [1,4], group2 [2,3]
 

 示例 2： 

 
输入：n = 3, dislikes = [[1,2],[1,3],[2,3]]
输出：false
 

 示例 3： 

 
输入：n = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
输出：false
 

 

 提示： 

 
 1 <= n <= 2000 
 0 <= dislikes.length <= 10⁴ 
 dislikes[i].length == 2 
 1 <= dislikes[i][j] <= n 
 ai < bi 
 dislikes 中每一组都 不同 
 

 

 Related Topics 深度优先搜索 广度优先搜索 并查集 图 👍 430 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution886{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    vector<vector<int>> adj; // 邻接表存图
    vector<int> color;       // 0:未染色, 1:颜色1, 2:颜色2
    int n = 0;                   // 节点数量
    bool dfs_color(int u, int c) {
        color[u] = c;
        for (int v : adj[u]) {
            if (color[v] == 0) { // 如果邻接点未染色
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
    bool possibleBipartition(int _n, vector<vector<int>>& dislikes) {
        n = _n;
        adj.resize(n);
        for (auto& dislike : dislikes) {
            int u = dislike[0], v = dislike[1];
            if (adj.size() < n) {
                adj.resize(n);
            }
            adj[u - 1].push_back(v - 1);
            adj[v - 1].push_back(u - 1);
        }
        color.resize( n, 0);
        return is_bipartite();
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution886;
int main() {
    Solution solution;
    int n = 4;
    vector<vector<int>> dislikes = {{1,2},{1,3},{2,4}};
    bool result = solution.possibleBipartition(n, dislikes);
    cout << result << endl;
    return 0;
}