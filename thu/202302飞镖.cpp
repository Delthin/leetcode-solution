#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> c2i = {{'.', 0}, {'+', 1}, {'x', 2}, {'*', 3}, {'o', -1}};
unordered_map<int, char> i2c = {{0, '.'}, {1, '+'},  {2, 'x'}, {3, '*'}, {-1, 'o'}};
// 按上下左右左上左下右上右下顺序
const vector<pair<int, int>> dir1 = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const vector<pair<int, int>> dir2 = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
const vector<pair<int, int>> dir3 = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}};

bool isValid(vector<vector<int>>& board, int x, int y, char t) {
    int n = board.size();
    int m = board[0].size();
    if (board[x][y] != 0) {
        return false;
    }
    return true;
}

void simulate(vector<vector<int>>& board, int x, int y, char t) {
    char original_mark = i2c[board[x][y]];
    board[x][y] = c2i[t];
    int n = board.size();
    int m = board[0].size();
    int time = 0;
    int num = 4;
    vector<pair<int, int>> pos(4, {x, y});
    vector<pair<int, int>> dir;
    if (t == '+') {
        dir = dir1;
    } else if (t == 'x') {
        dir = dir2;
    } else if (t == '*') {
        dir = dir3;
        num = 8;
        pos.resize(8, {x, y});
    }
    bool flag = true;
    while (flag) {
        time++;
        for (int i = 0; i < num; i++) {
            int nx = pos[i].first + dir[i].first;
            int ny = pos[i].second + dir[i].second;
            if (!isValid(board, nx, ny, t)) {
                flag = false;
            }
            pos[i] = {nx, ny};
        }
    }
    string s;
    for (int i = 0; i < num; i++) {
        auto [nx, ny] = pos[i];
        if (isValid(board, nx, ny, t)) {
            board[nx][ny] = c2i[t];
            s += '.';
        } else if (board[nx][ny] > 0) {
            // 碰撞消除标记
            s += i2c[board[nx][ny]];
            board[nx][ny] = 0;
        } else {
            // 出界
            s += 'o';
        }
    }

    cout << original_mark << ' ' << time << ' ' << s << endl;
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> board(n + 2, vector<int>(m + 2, 0));
    // 出界为o, -1
    for (int i = 0; i <= n + 1; i++) {
        board[i][0] = -1;
        board[i][m + 1] = -1;
    }
    for (int i = 0; i <= m + 1; i++) {
        board[0][i] = -1;
        board[n + 1][i] = -1;
    }
    // 1 -> n
    while (q--) {
        int x, y;
        char t;
        cin >> x >> y >> t;
        simulate(board, x, y, t);
    }
    return 0;
}
