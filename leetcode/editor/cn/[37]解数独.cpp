/**
编写一个程序，通过填充空格来解决数独问题。 

 数独的解法需 遵循如下规则： 

 
 数字 1-9 在每一行只能出现一次。 
 数字 1-9 在每一列只能出现一次。 
 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图） 
 

 数独部分空格内已填入了数字，空白格用 '.' 表示。 

 

 
 
 
 示例 1： 
 
 
输入：board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",
".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".",
"3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],
[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".
",".",".",".","8",".",".","7","9"]]
输出：[["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],
["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4
","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6
","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5
","2","8","6","1","7","9"]]
解释：输入的数独如上图所示，唯一有效的解决方案如下所示：
 
 
 
 



 

 提示： 

 
 board.length == 9 
 board[i].length == 9 
 board[i][j] 是一位数字或者 '.' 
 题目数据 保证 输入数独仅有一个解 
 

 Related Topics 数组 哈希表 回溯 矩阵 👍 1900 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution37{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    static constexpr int n = 9;
    static bool isValid(int row, int col, vector<vector<char>>& board, char c) {
        for (int i = 0; i < n; i++) {
            if(board[i][col] == c) {
                return false;
            }
        }
        for (int j = 0; j < n; j++) {
            if (board[row][j] == c) {
                return false;
            }
        }
        int startRow = row / 3 * 3;
        int startCol = col / 3 * 3;
        for (int i = startRow; i < startRow + 3; i++) {
            for (int j = startCol; j < startCol + 3; j++) {
                if (board[i][j] == c) {
                    return false;
                }
            }
        }
        return true;
    }
    static vector<char> canFill(int row, int col, vector<vector<char>>& board) {
        vector<char> ret;
        for (int i = 1; i <= 9; i++) {
            char c = '0' + i;
            if (!isValid(row, col, board, c)) continue;
            ret.emplace_back(c);
        }
        return ret;
    }
    static bool backTrace(vector<vector<char>>& board, int row, int col) {
        if (col == n) {
            col = 0;
            row++;
        }
        if (row == n) return true;
        if (board[row][col] == '.') {
            for (int i = 1; i <= 9; i++) {
                char c = '0' + i;
                if (!isValid(row, col, board, c)) continue;
                board[row][col] = c;
                if (backTrace(board, row, col+1)) return true;
            }
            board[row][col] = '.';
            return false;
        }
        return backTrace(board, row, col+1);
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        backTrace(board, 0, 0);
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution37;
int main() {
    Solution solution;
    vector<vector<char>>board = {{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}}
    ;
    solution.solveSudoku(board);
    return 0;
}