/**
给你一个points 数组，表示 2D 平面上的一些点，其中 points[i] = [xi, yi] 。 

 连接点 [xi, yi] 和点 [xj, yj] 的费用为它们之间的 曼哈顿距离 ：|xi - xj| + |yi - yj| ，其中 |val| 表示 
val 的绝对值。 

 请你返回将所有点连接的最小总费用。只有任意两点之间 有且仅有 一条简单路径时，才认为所有点都已连接。 

 

 示例 1： 

 

 
输入：points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
输出：20
解释：

我们可以按照上图所示连接所有点得到最小总费用，总费用为 20 。
注意到任意两个点之间只有唯一一条路径互相到达。
 

 示例 2： 

 
输入：points = [[3,12],[-2,5],[-4,1]]
输出：18
 

 示例 3： 

 
输入：points = [[0,0],[1,1],[1,0],[-1,1]]
输出：4
 

 示例 4： 

 
输入：points = [[-1000000,-1000000],[1000000,1000000]]
输出：4000000
 

 示例 5： 

 
输入：points = [[0,0]]
输出：0
 

 

 提示： 

 
 1 <= points.length <= 1000 
 -10⁶ <= xi, yi <= 10⁶ 
 所有点 (xi, yi) 两两不同。 
 

 Related Topics 并查集 图 数组 最小生成树 👍 347 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1584{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    class UnionFind
    {
    private:
        vector<int> parent, rank;
        int components;

    public:
        UnionFind(int n) : parent(n), rank(n, 0), components(n)
        {
            iota(parent.begin(), parent.end(), 0);
        }

        int find(int x)
        {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        bool unite(int x, int y)
        {
            int px = find(x), py = find(y);
            if (px == py)
                return false;

            if (rank[px] < rank[py])
                swap(px, py);
            parent[py] = px;
            if (rank[px] == rank[py])
                rank[px]++;
            components--;
            return true;
        }

        bool connected(int x, int y)
        {
            return find(x) == find(y);
        }

        int get_components() const
        {
            return components;
        }
    };
    using ll = long long;
    struct Edge {
    public:
        Edge(int u, int v, int w) : u(u), v(v), w(w){}
        int u, v, w;
        bool operator<(const Edge &other) const
        {
            return w < other.w;
        }
    };

    ll kruskal_mst(int n, vector<Edge> &edges)
    {
        sort(edges.begin(), edges.end());
        UnionFind uf(n);

        ll mst_weight = 0;
        int edges_added = 0;

        for (const Edge &e : edges) {
            if (uf.unite(e.u, e.v)) {
                mst_weight += e.w;
                edges_added++;
                if (edges_added == n - 1)
                    break;
            }
        }

        return edges_added == n - 1 ? mst_weight : -1;
    }
    int minCostConnectPoints(vector<vector<int>>& points) {
        auto dist = [&](int x, int y) -> int {
            return abs(points[x][0] - points[y][0]) + abs(points[x][1] - points[y][1]);
        };
        vector<Edge> edges;
        for (int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++) {
                edges.emplace_back(i, j, dist(i,j));
            }
        }
        return kruskal_mst(points.size(), edges);
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1584;
int main() {
    Solution solution;

    return 0;
}