/**
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。 

 在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如
果要学习课程 ai 则 必须 先学习课程 bi 。 

 
 例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。 
 

 请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。 

 

 示例 1： 

 
输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。 

 示例 2： 

 
输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。 

 

 提示： 

 
 1 <= numCourses <= 2000 
 0 <= prerequisites.length <= 5000 
 prerequisites[i].length == 2 
 0 <= ai, bi < numCourses 
 prerequisites[i] 中的所有课程对 互不相同 
 

 Related Topics 深度优先搜索 广度优先搜索 图 拓扑排序 👍 2082 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution207{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> edges(numCourses);
        vector<int> indeg(numCourses, 0);
        for (auto pre:prerequisites) {
            edges[pre[1]].push_back(pre[0]);
            indeg[pre[0]]++;
        }
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }
        int visited = 0;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            visited++;
            for (int v: edges[u]) {
                --indeg[v];
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }
        return visited == numCourses;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution207;
int main() {
    Solution solution;
    return 0;
}