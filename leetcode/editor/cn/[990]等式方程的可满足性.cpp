/**
给定一个由表示变量之间关系的字符串方程组成的数组，每个字符串方程 equations[i] 的长度为 4，并采用两种不同的形式之一："a==b" 或 "a!=
b"。在这里，a 和 b 是小写字母（不一定不同），表示单字母变量名。 

 只有当可以将整数分配给变量名，以便满足所有给定的方程时才返回 true，否则返回 false。 

 

 
 

 示例 1： 

 输入：["a==b","b!=a"]
输出：false
解释：如果我们指定，a = 1 且 b = 1，那么可以满足第一个方程，但无法满足第二个方程。没有办法分配变量同时满足这两个方程。
 

 示例 2： 

 输入：["b==a","a==b"]
输出：true
解释：我们可以指定 a = 1 且 b = 1 以满足满足这两个方程。
 

 示例 3： 

 输入：["a==b","b==c","a==c"]
输出：true
 

 示例 4： 

 输入：["a==b","b!=c","c==a"]
输出：false
 

 示例 5： 

 输入：["c==c","b==d","x!=z"]
输出：true
 

 

 提示： 

 
 1 <= equations.length <= 500 
 equations[i].length == 4 
 equations[i][0] 和 equations[i][3] 是小写字母 
 equations[i][1] 要么是 '='，要么是 '!' 
 equations[i][2] 是 '=' 
 

 Related Topics 并查集 图 数组 字符串 👍 350 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution990{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
 struct DSU {
    vector<int> parent;
    vector<int> sz; // 可选：用于按秩合并

    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0); // iota: parent[i] = i
        sz.assign(n + 1, 1);
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // 路径压缩
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            // 按秩合并(可选，通常路径压缩已足够快)
            if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
        }
    }
};
public:
    bool equationsPossible(vector<string>& equations) {
        DSU dsu(26);
        for (const string& eq : equations) {
            int a = eq[0] - 'a';
            int b = eq[3] - 'a';
            if (eq[1] == '=') {
                dsu.unite(a, b);
            }
        }
        for (const string& eq : equations) {
            int a = eq[0] - 'a';
            int b = eq[3] - 'a';
            if (eq[1] == '!') {
                if (dsu.find(a) == dsu.find(b)) {
                    return false; // 如果两个变量在同一集合中，且是“不等”关系，则不可能满足
                }
            }
        }
        return true;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution990;
int main() {
    Solution solution;
    vector<string> equations = {"a==b","b==a"};
    bool result = solution.equationsPossible(equations);
    return 0;
}