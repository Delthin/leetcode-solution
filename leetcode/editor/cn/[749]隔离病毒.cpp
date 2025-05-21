//病毒扩散得很快，现在你的任务是尽可能地通过安装防火墙来隔离病毒。 
//
// 假设世界由 m x n 的二维矩阵 isInfected 组成， isInfected[i][j] == 0 表示该区域未感染病毒，而 
//isInfected[i][j] == 1 表示该区域已感染病毒。可以在任意 2 个相邻单元之间的共享边界上安装一个防火墙（并且只有一个防火墙）。 
//
// 每天晚上，病毒会从被感染区域向相邻未感染区域扩散，除非被防火墙隔离。现由于资源有限，每天你只能安装一系列防火墙来隔离其中一个被病毒感染的区域（一个区域或连
//续的一片区域），且该感染区域对未感染区域的威胁最大且 保证唯一 。 
//
// 你需要努力使得最后有部分区域不被病毒感染，如果可以成功，那么返回需要使用的防火墙个数; 如果无法实现，则返回在世界被病毒全部感染时已安装的防火墙个数。 
//
// 
//
// 示例 1： 
//
// 
//
// 
//输入: isInfected = [[0,1,0,0,0,0,0,1],[0,1,0,0,0,0,0,1],[0,0,0,0,0,0,0,1],[0,0,0
//,0,0,0,0,0]]
//输出: 10
//解释:一共有两块被病毒感染的区域。
//在第一天，添加 5 墙隔离病毒区域的左侧。病毒传播后的状态是:
//
//第二天，在右侧添加 5 个墙来隔离病毒区域。此时病毒已经被完全控制住了。
//
// 
//
// 示例 2： 
//
// 
//
// 
//输入: isInfected = [[1,1,1],[1,0,1],[1,1,1]]
//输出: 4
//解释: 虽然只保存了一个小区域，但却有四面墙。
//注意，防火墙只建立在两个不同区域的共享边界上。
// 
//
// 示例 3: 
//
// 
//输入: isInfected = [[1,1,1,0,0,0,0,0,0],[1,0,1,0,1,1,1,1,1],[1,1,1,0,0,0,0,0,0]]
//
//输出: 13
//解释: 在隔离右边感染区域后，隔离左边病毒区域只需要 2 个防火墙。
// 
//
// 
//
// 提示: 
//
// 
// m == isInfected.length 
// n == isInfected[i].length 
// 1 <= m, n <= 50 
// isInfected[i][j] is either 0 or 1 
// 在整个描述的过程中，总有一个相邻的病毒区域，它将在下一轮 严格地感染更多未受污染的方块 
// 
//
// 
//
// Related Topics 深度优先搜索 广度优先搜索 数组 矩阵 模拟 👍 153 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution749{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    const int DIR[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    bool inArea(vector<vector<int>>& g, int x, int y) {
        return x >= 0 && x < g.size() && y >= 0 && y < g[0].size();
    }
    void dfs(vector<vector<int>>& isInfected, vector<vector<int>>& regions, unordered_set<int>& threat, int& wallCount, int x, int y) {
        for (auto& [dx, dy]: DIR) {
            int nx = x + dx, ny = y + dy;
            if (inArea(isInfected, nx, ny)) {
                if (isInfected[nx][ny] == 1 && regions[nx][ny] == -1) {
                    regions[nx][ny] = regions[x][y];
                    dfs(isInfected, regions, threat, wallCount, nx, ny);
                } else if (isInfected[nx][ny] == 0){
                    threat.insert(isInfected[0].size() * nx + ny);
                    wallCount++;
                }
            }
        }
    }
public:
    int containVirus(vector<vector<int>>& isInfected) {
        // 先dfs对感染区块分id，每轮都要重新刷一次 mn * max(m,n) 复杂度
        // 同时把新区域加入队列，
        int m = isInfected.size(), n = isInfected[0].size();
        int total = 0;
        while (true) {
            vector<vector<int>> regions(m, vector<int>(n, -1));
            vector<unordered_set<int>> threats; // n * x + y
            vector<int> wallCounts;
            int id = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n;j++) {
                    if (isInfected[i][j] == 1 && regions[i][j] == -1) {
                        unordered_set<int> threat;
                        int wallCount = 0;
                        regions[i][j] = id++;
                        dfs(isInfected, regions, threat, wallCount, i, j);
                        threats.emplace_back(threat);
                        wallCounts.emplace_back(wallCount);
                    }
                }
            }

            // 找最大威胁
            if (id == 0) break;
            int maxThreatId = 0;
            for (int i = 1; i < id; i++) {
                if (threats[i].size() > threats[maxThreatId].size()) {
                    maxThreatId = i;
                }
            }

            // 隔离
            total += wallCounts[maxThreatId];

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (regions[i][j] == maxThreatId) {
                        isInfected[i][j] = -1;
                    }
                }
            }

            // 感染
            for (int i = 0; i < id; i++) {
                if (i == maxThreatId) continue;
                for (int pos: threats[i]) {
                    // pos = n * x + y
                    int x = pos / n;
                    int y = pos - n * x;
                    isInfected[x][y] = 1;
                }
            }
        }
        return total;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution749;
int main() {
    Solution solution;

    return 0;
}