#include <bits/stdc++.h>

using namespace std;

class Solution1 {
public:
    int largestInteger(vector<int>& nums, int k) {

    }
};

class Solution2 {
private:
    int needK(char a, char b) {
        return min(abs(a - b), 26 - abs(a - b));
    }
public:
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = n - 1; i >= 0 ; i--) {
            for (int j = i + 1; j <= n; j++) {
                if (j == i + 1) {
                    continue;
                }
                dp[i][j] = dp[i + 1][j - 1] + needK(s.at(i), s.at(j - 1));
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (dp[i][j] <= k) {
                    ans = max(ans, j - i);
                }
            }
        }
        return ans;
    }
};

int main(int argc, char *argv[]) {
    Solution2 solution2;
    solution2.longestPalindromicSubsequence("wehzr", 3);
}
