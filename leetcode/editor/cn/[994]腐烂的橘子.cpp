/**
在给定的 m x n 网格
 grid 中，每个单元格可以有以下三个值之一： 

 
 值 0 代表空单元格； 
 值 1 代表新鲜橘子； 
 值 2 代表腐烂的橘子。 
 

 每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。 

 返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。 

 

 示例 1： 

 

 
输入：grid = [[2,1,1],[1,1,0],[0,1,1]]
输出：4
 

 示例 2： 

 
输入：grid = [[2,1,1],[0,1,1],[1,0,1]]
输出：-1
解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个方向上。
 

 示例 3： 

 
输入：grid = [[0,2]]
输出：0
解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。
 

 

 提示： 

 
 m == grid.length 
 n == grid[i].length 
 1 <= m, n <= 10 
 grid[i][j] 仅为 0、1 或 2 
 

 Related Topics 广度优先搜索 数组 矩阵 👍 969 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution994{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
     int n = grid.size();
     int m = grid[0].size();
     vector<vector<bool>> visited(n, vector<bool>(m, false));
     int ans = 0;
     constexpr int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
     queue<pair<int, int>> que;
     for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
       if (!visited[i][j] && grid[i][j] == 2) {
        que.emplace(i, j);
        visited[i][j] = true;
         for (auto k : direction) {
          int new_x = i + k[0];
          int new_y = j + k[1];
          if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m && !visited[new_x][new_y] && grid[new_x][new_y] == 1) {
           que.emplace(new_x, new_y);
           visited[new_x][new_y] = true;
          }
         }
       }
      }
     }
     while (!que.empty()) {
      bool finished = true;
      for (int i = 0; i < n; i++) {
       for (int j = 0; j < m; j++) {
        if (grid[i][j] == 1) {
         finished = false;
        }
       }
      }
      if (finished) {
       break;
      }
      int rot_num = que.size();
      for (int i = 0; i < rot_num; i++) {
       auto [x, y] = que.front();
       que.pop();
       grid[x][y] = 2;
       for (auto k : direction) {
        int new_x = x + k[0];
        int new_y = y + k[1];
        if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m && !visited[new_x][new_y] && grid[new_x][new_y] == 1) {
         que.emplace(new_x, new_y);
         visited[new_x][new_y] = true;
        }
       }
      }
      ans++;
     };
     for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
       if (grid[i][j] == 1) {
        return -1;
       }
      }
     }
     return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution994;
int main() {
    Solution solution;

    return 0;
}