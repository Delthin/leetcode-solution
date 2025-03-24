#include <bits/stdc++.h>

using namespace std;

class Solution1 {
public:
    int maxContainers(int n, int w, int maxWeight) {
        return min(n * n, maxWeight / w);
    }
};

class Solution2 {
private:
    vector<int> father;
    int find(int u) {
        return u == father[u] ? u : father[u] = find(father[u]);
    }
    bool isSame(int u, int v) {
        u = find(u);
        v = find(v);
        return u == v;
    }
    void join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        father[v] = u;
    }
    int countCommonElements(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<int> freq;
        for (int num : arr1) {
            freq.insert(num);
        }

        int count = 0;
        for (int num : arr2) {
            if (freq.find(num) != freq.end()) {
                count++;
                freq.erase(num);
            }
        }
        return count;
    }

public:
    int numberOfComponents(vector<vector<int>>& properties, int k) {
        int n = properties.size();
        father.resize(n);
        for (int i = 0; i < n; i++) {
            father[i] = i;
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (countCommonElements(properties[i], properties[j]) >= k) {
                    join(i, j);
                }
            }
        }
        unordered_set<int> components;
        for (int i = 0; i < n; i++) {
            components.insert(find(i));
        }
        return components.size();
    }
};

class Solution3 {

public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        vector<long long> prev(skill.size() + 1, 0);
        vector<long long> now (skill.size() + 1, 0);
        for (int j = 1; j <= skill.size(); j++) {
            prev[j] = prev[j - 1] + mana[0] * skill[j - 1];
        }
        for (int i = 1; i < mana.size(); i++) {
            now[0] = prev[1];
            for (int j = 1; j <= skill.size() ; j++) {
                now[j] = now[j - 1] + mana[i] * skill[j - 1];
            }
            for (int j = skill.size() - 1; j >= 1; j--) {
                if (now[j] < prev[j + 1]) {
                    now[j] = prev[j + 1];
                    for (int k = j - 1; k >= 0; k--) {
                        now[k] = now[k + 1] - mana[i] * skill[k];
                    }
                    for (int k = j + 1; k <= skill.size(); k++) {
                        now[k] = now[k - 1] + mana[i] * skill[k - 1];
                    }
                }
            }
            prev = now;
        }
        return prev[skill.size()];
    }
};

class Solution4 {
private:
    long long operation(long long l, long long r) {
        long long minOp = log(l) / log(4) + 1;
        long long min2 = pow(4, minOp) - l;
        long long maxOp = log(r) / log(4) + 1;
        long long max2 = r - pow(4, maxOp - 1);
        long long ans = 0;
        if (maxOp > minOp) {
            ans += min2 * minOp + (max2 + 1) * maxOp;
        }
        else {
            ans = minOp * (r - l + 1);
        }
        for (long long i = minOp + 1; i < maxOp; i++) {
            ans += (pow(4, i) - pow(4, i - 1)) * i;
        }
        return (ans + 1) / 2;
    }
public:
    long long minOperations(vector<vector<int>>& queries) {
        long long ans = 0;
        for (auto query:queries) {
            ans += operation(query[0], query[1]);
        }
        return ans;
    }
};

int main(int argc, char *argv[]) {
    Solution4 solution4;
    vector<vector<int>> queries = {{1,2}, {2,4}};
    solution4.minOperations(queries);
}
