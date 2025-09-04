#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    vector<vector<int>> board(15, vector<int>(10, 0));
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> board[i][j];
        }
    }
    vector<vector<int>> block(4, vector<int>(4, 0));
    int width = 0, height = 0;
    int min_i = 3, min_j = 3;
    int max_i = 0, max_j = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> block[i][j];
            if (block[i][j] == 1) {
                min_i = min(min_i, i);
                min_j = min(min_j, j);
                max_i = max(max_i, i);
                max_j = max(max_j, j);
            }
        }
    }
    width = max_j - min_j + 1;
    height = max_i - min_i + 1;
    int col = 0;
    cin >> col;
    col--;
    int last_row = -1;
    for (int i = 0; i <= 14; i++) {
        // 在i,col位置为左上角放block，看是否可以放
        bool flag = true;
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < width; k++) {
                if (i + min_i + j > 14 || k + col + min_j > 9 || (block[j + min_i][k + min_j] == 1 && board[i + min_i + j][k + col + min_j] == 1)) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag) {
            last_row = i;
        } else {
            break;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block[i][j] == 1) {
                if (last_row + i > 14 || col + j > 9) {
                    continue;
                }
                board[last_row + i][col + j] = 1;
            }
        }
    }
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
