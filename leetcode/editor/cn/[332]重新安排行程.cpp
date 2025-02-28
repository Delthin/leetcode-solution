/**
给你一份航线列表 tickets ，其中 tickets[i] = [fromi, toi] 表示飞机出发和降落的机场地点。请你对该行程进行重新规划排序。 

 所有这些机票都属于一个从 JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK 开始。如果存在多种有效的行程，请你按字典排序返回最小的行程组合。 

 
 例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前。 
 

 假定所有机票至少存在一种合理的行程。且所有的机票 必须都用一次 且 只能用一次。 

 

 示例 1： 
 
 
输入：tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
输出：["JFK","MUC","LHR","SFO","SJC"]
 

 示例 2： 
 
 
输入：tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL",
"SFO"]]
输出：["JFK","ATL","JFK","SFO","ATL","SFO"]
解释：另一种有效的行程是 ["JFK","SFO","ATL","JFK","ATL","SFO"] ，但是它字典排序更大更靠后。
 

 

 提示： 

 
 1 <= tickets.length <= 300 
 tickets[i].length == 2 
 fromi.length == 3 
 toi.length == 3 
 fromi 和 toi 由大写英文字母组成 
 fromi != toi 
 

 Related Topics 深度优先搜索 图 欧拉回路 👍 957 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution332{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    vector<string> path;
    unordered_map<string, map<string, int>> adj;
    bool dfs(const string& first, int totalLen) {
        if (totalLen == path.size()) {
            return true;
        }
        if (!adj.count(first) || adj[first].empty()) {
            return false;
        }
        for (auto& [target, times]: adj[first]) {
            if (times > 0) {
                path.emplace_back(target);
                times--;
                if (dfs(target, totalLen)) {
                    return true;
                }
                path.pop_back();
                times++;
            }
        }
        return false;
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (const vector<string>& ticket: tickets) {
            adj[ticket[0]][ticket[1]]++;
        }
        path.emplace_back("JFK");
        dfs("JFK", tickets.size() + 1);
        return path;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution332;
int main() {
    Solution solution;
    vector<vector<string>> tickets = {
        {"MEL","PER"},{"SYD","CBR"},{"AUA","DRW"},{"JFK","EZE"},{"PER","AXA"},{"DRW","AUA"},{"EZE","SYD"},{"AUA","MEL"},{"DRW","AUA"},{"PER","ANU"},{"CBR","EZE"},{"EZE","PER"},{"MEL","EZE"},{"EZE","MEL"},{"EZE","TBI"},{"ADL","DRW"},{"ANU","EZE"},{"AXA","ADL"}
    };

    vector<string> result = solution.findItinerary(tickets);

    // Print the result
    for (const string& airport : result) {
        cout << airport << " ";
    }
    cout << endl;

    return 0;
}