#include <bits/stdc++.h>

using namespace std;

class Solution1 {
private:
public:
    long long minCuttingCost(int n, int m, int k) {
        long long ans = 0;
        if (n > k) {
            ans += static_cast<long long>(n - k) * k;
        }
        if (m > k) {
            ans += static_cast<long long>(m - k) * k;
        }
        return ans;
    }
};

class Solution2 {
public:
    string resultingString(string s) {
        vector<char> stack;

        for (char c : s) {
            if (!stack.empty()) {
                char top = stack.back();
                int diff = abs(top - c);
                if (diff == 1 || (top == 'a' && c == 'z') || (top == 'z' && c == 'a')) {
                    stack.pop_back();
                } else {
                    stack.push_back(c);
                }
            } else {
                stack.push_back(c);
            }
        }

        return string(stack.begin(), stack.end());
    }
};

class Solution3 {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        vector<int> rawProfits(n, 0);
        vector<int> halfProfits(n, 0);
        for (int i = 0; i < n; i++) {
            rawProfits[i] = future[i] - present[i];
            halfProfits[i] = future[i] - present[i] / 2;
        }
        halfProfits[0] = rawProfits[0];


        auto check = [&] (int x) {

        };
        int l = 0, r = accumulate(halfProfits.begin(), halfProfits.end(), 0) + 1;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            (check(mid) ? l : r) = mid;
        }
        return l;
};

class Solution4 {
private:
    bool isConsecutive(char a, char b) {
        return abs(a - b) == 1 || (a == 'a' && b == 'z') || (a == 'z' && b == 'a');
    }

    bool isLexSmaller(const string& a, const string& b) {
        int n = min(a.size(), b.size());
        for (int i = 0; i < n; i++) {
            if (a[i] != b[i]) {
                return a[i] < b[i];
            }
        }
        return a.size() < b.size();
    }
    unordered_map<string, string> memo;
public:
    string lexicographicallySmallestString(string s) {
        if (memo.count(s)) return memo[s];
        string smallest = s;
        if (s == "") return s;
        for (int i = 0; i < s.size() - 1; i++) {
            if (isConsecutive(s[i], s[i+1])) {
                string next = s.substr(0, i);
                if (i < s.size() - 2) {
                    next += s.substr(i+2);
                }
                string candidate = lexicographicallySmallestString(next);

                if (isLexSmaller(candidate, smallest)) {
                    smallest = candidate;
                }
            }
        }
        memo[s] = smallest;
        return smallest;
    }
};

int main(int argc, char *argv[]) {
    Solution4 solution4;
    string s = "bcda";
    solution4.lexicographicallySmallestString(s);
}
