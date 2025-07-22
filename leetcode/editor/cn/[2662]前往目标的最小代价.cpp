/**
给你一个数组 start ，其中 start = [startX, startY] 表示你的初始位置位于二维空间上的 (startX, startY) 。另给你
一个数组 target ，其中 target = [targetX, targetY] 表示你的目标位置 (targetX, targetY) 。 

 从位置 (x1, y1) 到空间中任一其他位置 (x2, y2) 的 代价 是 |x2 - x1| + |y2 - y1| 。 

 给你一个二维数组 specialRoads ，表示空间中存在的一些 特殊路径。其中 specialRoads[i] = [x1i, y1i, x2i, y2
i, costi] 表示第 i 条特殊路径可以从 (x1i, y1i) 到 (x2i, y2i) ，但成本等于 costi 。你可以使用每条特殊路径任意次数。 

 返回从 (startX, startY) 到 (targetX, targetY) 所需的 最小 代价。 

 

 示例 1： 

 
 输入：start = [1,1], target = [4,5], specialRoads = [[1,2,3,3,2],[3,4,4,5,1]] 
 

 输出：5 

 解释： 

 
 (1,1) 到 (1,2) 花费为 |1 - 1| + |2 - 1| = 1。 
 (1,2) 到 (3,3)。使用 specialRoads[0] 花费为 2。 
 (3,3) 到 (3,4) 花费为 |3 - 3| + |4 - 3| = 1。 
 (3,4) 到 (4,5)。使用 specialRoads[1] 花费为 1。 
 

 所以总花费是 1 + 2 + 1 + 1 = 5。 

 示例 2： 

 
 输入：start = [3,2], target = [5,7], specialRoads = [[5,7,3,2,1],[3,2,3,4,4],[3,3,
5,5,5],[3,4,5,6,6]] 
 

 输出：7 

 解释： 

 不使用任何特殊路径，直接从开始到结束位置是最优的，花费为 |5 - 3| + |7 - 2| = 7。 

 注意 specialRoads[0] 直接从 (5,7) 到 (3,2)。 

 示例 3： 

 
 输入：start = [1,1], target = [10,4], specialRoads = [[4,2,1,1,3],[1,2,7,4,4],[10,
3,6,1,2],[6,1,1,2,3]] 
 

 输出：8 

 解释： 

 
 (1,1) 到 (1,2) 花费为 |1 - 1| + |2 - 1| = 1。 
 (1,2) 到 (7,4)。使用 specialRoads[1] 花费为 4。 
 (7,4) 到 (10,4) 花费为 |10 - 7| + |4 - 4| = 3。 
 

 

 提示： 

 
 start.length == target.length == 2 
 1 <= startX <= targetX <= 10⁵ 
 1 <= startY <= targetY <= 10⁵ 
 1 <= specialRoads.length <= 200 
 specialRoads[i].length == 5 
 startX <= x1i, x2i <= targetX 
 startY <= y1i, y2i <= targetY 
 1 <= costi <= 10⁵ 
 

 Related Topics 图 数组 最短路 堆（优先队列） 👍 45 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2662{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    int mdistance(int x1, int y1, int x2, int y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    }
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        // 分两步，从起点到特殊路径，从特殊路径到终点
        // 先构建特殊路径内部的图，标记起点和终点距离最近的点
        // 然后以起点最近的点为起点，终点最近的点为终点，跑最短路
        // 相当于两个点加n条边建图
        // 以上错误！！！不能把特殊路径当做一个整体，这样确定不了从起点开始的最短路
        // 所以还是要把起点和终点当作一个点，特殊路径当作边
        // 然后跑最短路
        int n = specialRoads.size();
        set<pair<int, int>> s;//先取点集
        s.insert({start[0], start[1]});
        s.insert({target[0], target[1]});
        for (int i = 0; i < n; ++i) {
            int x1 = specialRoads[i][0], y1 = specialRoads[i][1];
            int x2 = specialRoads[i][2], y2 = specialRoads[i][3];
            s.insert({x1, y1});
            s.insert({x2, y2});
        }
        int startIndex = -1, targetIndex = -1;
        int m = s.size();
        map<pair<int, int>, int> pointIndex;
        vector<vector<int>> graph(m, vector<int>(m, INT_MAX));
        vector<pair<int, int>> points(s.begin(), s.end());
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == j) {
                    graph[i][j] = 0;
                }
                else {
                    graph[i][j] = mdistance(points[i].first, points[i].second, points[j].first, points[j].second);
                }
            }
            pointIndex[points[i]] = i;
            if (points[i].first == start[0] && points[i].second == start[1]) {
                startIndex = i;
            }
            if (points[i].first == target[0] && points[i].second == target[1]) {
                targetIndex = i;
            }
        }
        // 特殊路径边权
        for (auto& road : specialRoads) {
            int i = pointIndex[{road[0], road[1]}];
            int j = pointIndex[{road[2], road[3]}];
            graph[i][j] = min(graph[i][j], road[4]);
        }
        // 添加起点和终点(其实可以建图时就添加，因为不过多了2（n+1）条边，以下做法只是省去这些边，记录起终点序号就行)
        // int startIndex = -1, targetIndex = -1;
        // for (int i = 0; i < m; ++i) {
        //     if (points[i].first == start[0] && points[i].second == start[1]) {
        //         startIndex = i;
        //     }
        //     if (points[i].first == target[0] && points[i].second == target[1]) {
        //         targetIndex = i;
        //     }
        // }
        // if (startIndex == -1) {
        //     startIndex = m;
        // }
        // if (targetIndex == -1) {
        //     targetIndex = m + 1;
        // }
        // // 添加起点到所有点的边和所有点到终点的边
        // for (int i = 0; i < m; ++i) {
        //     // 如果起点和终点不在特殊路径中，才添加边
        //     if (graph[startIndex][i] == INT_MAX) {
        //         graph[startIndex][i] = mdistance(start[0], start[1], points[i].first, points[i].second);
        //     }
        //     if (graph[i][targetIndex] == INT_MAX) {
        //         graph[i][targetIndex] = mdistance(points[i].first, points[i].second, target[0], target[1]);
        //     }
        // }
        // // 起点终点直达特判
        // graph[startIndex][targetIndex] = min(graph[startIndex][targetIndex], mdistance(start[0], start[1], target[0], target[1]));
        vector<int> dist(m, INT_MAX);
        dist[startIndex] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, startIndex});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue; // 这条边已经不是最短的了
            for (int v = 0; v < m; ++v) {
                if (graph[u][v] != INT_MAX) {
                    if (dist[v] > dist[u] + graph[u][v]) {
                        dist[v] = dist[u] + graph[u][v];
                        pq.push({dist[v], v});
                    }
                }
            }
        }
        return dist[targetIndex] == INT_MAX ? -1 : dist[targetIndex];
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2662;
int main() {
    Solution solution;

    return 0;
}