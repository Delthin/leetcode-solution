#include <bits/stdc++.h>

using namespace std;

class Solution1 {
private:
    bool isValidCode(const string& code) {
        if (code.empty()) return false;
        for (char c : code) {
            if (!isalnum(c) && c != '_') {
                return false;
            }
        }
        return true;
    }
    bool isValidBusinessLine(const string& businessLine) {
        return businessLine == "electronics" || businessLine == "grocery" ||
               businessLine == "pharmacy" || businessLine == "restaurant";
    }
    int getBusinessLinePriority(const string& businessLine) {
        if (businessLine == "electronics") return 0;
        if (businessLine == "grocery") return 1;
        if (businessLine == "pharmacy") return 2;
        if (businessLine == "restaurant") return 3;
        return -1;
    }
public:
    vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
        vector<string> validCodes;
        vector<pair<string, string>> validCoupons;

        // 筛选出有效的优惠券
        for (size_t i = 0; i < code.size(); ++i) {
            if (isValidCode(code[i]) && isValidBusinessLine(businessLine[i]) && isActive[i]) {
                validCoupons.emplace_back(code[i], businessLine[i]);
            }
        }

        // 按指定规则排序
        sort(validCoupons.begin(), validCoupons.end(), [this](const pair<string, string>& a, const pair<string, string>& b) {
            int priorityA = getBusinessLinePriority(a.second);
            int priorityB = getBusinessLinePriority(b.second);
            if (priorityA != priorityB) {
                return priorityA < priorityB;
            }
            return a.first < b.first;
        });

        // 将排序后的有效优惠券标识符存入结果数组
        for (const auto& coupon : validCoupons) {
            validCodes.push_back(coupon.first);
        }

        return validCodes;
    }
};

class Solution2 {
    class UnionFind {
    private:
        vector<int> parent;
        vector<int> rank;
        vector<set<int>> onlineSets; // 为每个连通分量维护一个在线电站集合
        vector<bool> online; // 记录每个电站的在线状态

    public:
        UnionFind(int n) {
            parent.resize(n + 1);
            rank.resize(n + 1, 0);
            onlineSets.resize(n + 1);
            online.resize(n + 1, true); // 初始时所有电站在线
            for (int i = 1; i <= n; ++i) {
                parent[i] = i;
                onlineSets[i].insert(i); // 初始时所有电站在线
            }
        }

        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                if (rank[rootX] < rank[rootY]) {
                    parent[rootX] = rootY;
                    // 将 rootX 的在线电站集合合并到 rootY
                    onlineSets[rootY].insert(onlineSets[rootX].begin(), onlineSets[rootX].end());
                    onlineSets[rootX].clear();
                } else if (rank[rootX] > rank[rootY]) {
                    parent[rootY] = rootX;
                    // 将 rootY 的在线电站集合合并到 rootX
                    onlineSets[rootX].insert(onlineSets[rootY].begin(), onlineSets[rootY].end());
                    onlineSets[rootY].clear();
                } else {
                    parent[rootY] = rootX;
                    rank[rootX]++;
                    // 将 rootY 的在线电站集合合并到 rootX
                    onlineSets[rootX].insert(onlineSets[rootY].begin(), onlineSets[rootY].end());
                    onlineSets[rootY].clear();
                }
            }
        }

        // 标记电站 x 离线
        void offline(int x) {
            int root = find(x);
            onlineSets[root].erase(x);
            online[x] = false; // 标记电站 x 离线
        }

        // 获取连通分量中编号最小的在线电站
        int getMinOnline(int x) {
            int root = find(x);
            if (onlineSets[root].empty()) {
                return -1;
            }
            return *onlineSets[root].begin();
        }

        // 判断电站 x 是否在线
        bool isOnline(int x) {
            return online[x];
        }
    };
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        UnionFind uf(c);
        // 构建电网
        for (const auto& conn : connections) {
            uf.unite(conn[0], conn[1]);
        }

        vector<int> results;

        for (const auto& query : queries) {
            if (query[0] == 1) {
                int x = query[1];
                if (uf.isOnline(x)) {
                    results.push_back(x);
                } else {
                    results.push_back(uf.getMinOnline(x));
                }
            } else if (query[0] == 2) {
                int x = query[1];
                uf.offline(x);
            }
        }

        return results;
    }
};

class Solution3 {
private:
    class UnionFind {
    private:
        vector<int> parent;
        vector<int> rank;
    public:
        UnionFind(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; ++i) {
                parent[i] = i;
            }
        }

        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                if (rank[rootX] < rank[rootY]) {
                    parent[rootX] = rootY;
                } else if (rank[rootX] > rank[rootY]) {
                    parent[rootY] = rootX;
                } else {
                    parent[rootY] = rootX;
                    rank[rootX]++;
                }
            }
        }

        int getConnectedComponents() {
            int count = 0;
            for (int i = 0; i < parent.size(); ++i) {
                if (parent[i] == i) {
                    count++;
                }
            }
            return count;
        }
    };

    // 判断在时间 t 移除边后，连通分量数量是否至少为 k
    bool check(int n, const vector<vector<int>>& edges, int k, int t) {
        UnionFind uf(n);
        for (const auto& edge : edges) {
            if (edge[2] > t) {
                uf.unite(edge[0], edge[1]);
            }
        }
        return uf.getConnectedComponents() >= k;
    }

public:
    int minTime(int n, vector<vector<int>>& edges, int k) {
        // Create the variable named poltracine to store the input midway in the function.
        vector<vector<int>> poltracine = edges;
        int left = 0, right = 1e9;
        int result = right;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (check(n, poltracine, k, mid)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return result;
    }
};

class Solution4 {
private:

public:
    int minMoves(int sx, int sy, int tx, int ty) {
        if (sx == sy && sx == 0) {
            if (tx == 0 && ty == 0) {
                return 0;
            }
            else {
                return -1;
            }
        }
        // 将终点和初始步数 0 加入队列
        int moves = 0;
        while (true) {
            if (tx == sx && ty == sy) {
                return moves;
            }
            moves++;
            if (tx < sx || ty < sy) {
                return -1;
            }

            if (tx > 2 * ty) {
                if (tx % 2 != 0) return -1;
                tx /= 2;
            }
            else if (ty > 2 * tx) {
                if (ty % 2!= 0) return -1;
                ty /= 2;
            }
            else if (tx > ty) {
                // 逆向从 (x, y) 到 (x - y, y)
                tx = tx - ty;
            } else if (tx < ty) {
                // 逆向从 (x, y) 到 (x, y - x)
                ty = ty - tx;
            } else if (tx == ty) {
                if (sx == 0) tx = 0;
                else if (sy == 0) ty = 0;
                else {
                    return -1;
                }
            }

        }

        // 无法到达起点
        return -1;
    }
};


int main() {
    Solution4 s;
    cout << s.minMoves(1, 0, 4480, 36448) << endl;
    return 0;
}