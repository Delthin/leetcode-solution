/**
按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。 

 n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。 

 给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。 

 
 
 每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。 
 
 

 

 示例 1： 
 
 
输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：如上图所示，4 皇后问题存在两个不同的解法。
 

 示例 2： 

 
输入：n = 1
输出：[["Q"]]
 

 

 提示： 

 
 1 <= n <= 9 
 

 Related Topics 数组 回溯 👍 2246 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution51{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    vector<vector<string>> ret;
    vector<string> chessboard;
    bool isValid(int row, int col, int n) {
        // 检查列
        for (int i = 0; i < row; i++) { // 这是一个剪枝
            if (chessboard[i][col] == 'Q') {
                return false;
            }
        }
        // 检查 45度角是否有皇后
        for (int i = row - 1, j = col - 1; i >=0 && j >= 0; i--, j--) {
            if (chessboard[i][j] == 'Q') {
                return false;
            }
        }
        // 检查 135度角是否有皇后
        for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (chessboard[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }
    void backTrace(int n, int row) {
        if (row == n) {
            ret.emplace_back(chessboard);
            return;
        }
        for (int col = 0; col < n; col++) {
            if (isValid(row, col, n)) {
                chessboard[row][col] = 'Q';
                backTrace(n, row + 1);
                chessboard[row][col] = '.';
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        chessboard.resize(n, string(n, '.'));
        backTrace(n, 0);
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution51;
int main() {
    Solution solution;

    return 0;
}