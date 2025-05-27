/**
给你一个 m x n 的二进制矩阵 mat ，请你返回有多少个 子矩形 的元素全部都是 1 。 

 

 示例 1： 

 

 
输入：mat = [[1,0,1],[1,1,0],[1,1,0]]
输出：13
解释：
有 6 个 1x1 的矩形。
有 2 个 1x2 的矩形。
有 3 个 2x1 的矩形。
有 1 个 2x2 的矩形。
有 1 个 3x1 的矩形。
矩形数目总共 = 6 + 2 + 3 + 1 + 1 = 13 。
 

 示例 2： 

 

 
输入：mat = [[0,1,1,0],[0,1,1,1],[1,1,1,0]]
输出：24
解释：
有 8 个 1x1 的子矩形。
有 5 个 1x2 的子矩形。
有 2 个 1x3 的子矩形。
有 4 个 2x1 的子矩形。
有 2 个 2x2 的子矩形。
有 2 个 3x1 的子矩形。
有 1 个 3x2 的子矩形。
矩形数目总共 = 8 + 5 + 2 + 4 + 2 + 2 + 1 = 24 。

 

 

 提示： 

 
 1 <= m, n <= 150 
 mat[i][j] 仅包含 0 或 1 
 

 Related Topics 栈 数组 动态规划 矩阵 单调栈 👍 213 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1504{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> sum(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n;j++) {
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + mat[i][j];
            }
        }
        int ans = 0;
        auto check = [&] (int r1,int c1,int r2,int c2){
            int tmp = sum[r2+1][c2+1]-sum[r2+1][c1]-sum[r1][c2+1]+sum[r1][c1];
            return tmp == (r2-r1+1)*(c2-c1+1);
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if(mat[i][j] != 1) continue;
                for (int c = j; c < n; c++) {
                    if(mat[i][c]!=1) break; // 小的不满足，大的也不满足
                    int l = i, r = m;
                    while (l + 1 < r) {
                        int mid = l + (r - l) / 2;
                        (check(i, j, mid, c) ? l : r) = mid;
                    }
                    ans += l - i + 1;
                }
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1504;
int main() {
    Solution solution;

    return 0;
}