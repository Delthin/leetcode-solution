//给你一个 m * n 的矩阵 mat，以及一个整数 k ，矩阵中的每一行都以非递减的顺序排列。 
//
// 你可以从每一行中选出 1 个元素形成一个数组。返回所有可能数组中的第 k 个 最小 数组和。 
//
// 
//
// 示例 1： 
//
// 输入：mat = [[1,3,11],[2,4,6]], k = 5
//输出：7
//解释：从每一行中选出一个元素，前 k 个和最小的数组分别是：
//[1,2], [1,4], [3,2], [3,4], [1,6]。其中第 5 个的和是 7 。  
//
// 示例 2： 
//
// 输入：mat = [[1,3,11],[2,4,6]], k = 9
//输出：17
// 
//
// 示例 3： 
//
// 输入：mat = [[1,10,10],[1,4,5],[2,3,6]], k = 7
//输出：9
//解释：从每一行中选出一个元素，前 k 个和最小的数组分别是：
//[1,1,2], [1,1,3], [1,4,2], [1,4,3], [1,1,6], [1,5,2], [1,5,3]。其中第 7 个的和是 9 。 
// 
//
// 示例 4： 
//
// 输入：mat = [[1,1,10],[2,2,9]], k = 7
//输出：12
// 
//
// 
//
// 提示： 
//
// 
// m == mat.length 
// n == mat.length[i] 
// 1 <= m, n <= 40 
// 1 <= k <= min(200, n ^ m) 
// 1 <= mat[i][j] <= 5000 
// mat[i] 是一个非递减数组 
// 
//
// Related Topics 数组 二分查找 矩阵 堆（优先队列） 👍 195 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution1439{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    bool dfs(vector<vector<int>> &mat, int &left_k, int i, int s) {
        if (i < 0) // 能递归到这里，说明数组和不超过二分的 mid
            return --left_k == 0; // 是否找到 k 个
        for (int x: mat[i]) { // 「枚举选哪个」，注意 mat[i] 是有序的
            if (x - mat[i][0] > s) // 超过剩余量，不管，等价于s<0的初始判断
                break; // 剪枝：后面的元素更大，无需枚举
            if (dfs(mat, left_k, i - 1, s - (x - mat[i][0]))) // 选 x 不选 mat[i][0]
                return true; // 找到 k 个就一直返回 true，不再递归
        }
        return false;
    }
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        int m = mat.size();
        int n = mat[0].size();
        auto check = [&] (int x)->bool {
            // 比x小的有k-1个
            int sum = 0;
            for (int i = 0; i < m; i++) {
                sum += mat[i][0];
            }
            if (sum > x) return false;
            int left_k = k;
            return dfs(mat, left_k, m - 1, x - sum);
        };
        int l = -1, r = 0;
        for (int i = 0; i < m; i++) {
            l += mat[i][0];
            r += mat[i][n - 1];
        }
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            (check(mid) ? r : l) = mid;
        }
        return r;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1439;
int main() {
    Solution solution;
    vector<vector<int>> mat = {{1,3,11}, {2,4,6}};
    solution.kthSmallest(mat, 5);
    return 0;
}