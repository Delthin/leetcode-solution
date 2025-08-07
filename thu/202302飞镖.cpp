// // 44分
// #include <bits/stdc++.h>
// using namespace std;
//
// unordered_map<char, int> c2i = {{'.', 0}, {'+', 1}, {'x', 2}, {'*', 3}, {'o', -1}};
// unordered_map<int, char> i2c = {{0, '.'}, {1, '+'},  {2, 'x'}, {3, '*'}, {-1, 'o'}};
// // 按上下左右左上左下右上右下顺序
// const vector<pair<int, int>> dir1 = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
// const vector<pair<int, int>> dir2 = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
// const vector<pair<int, int>> dir3 = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
//
// bool isValid(vector<vector<int>>& board, int x, int y, char t) {
//     int n = board.size();
//     int m = board[0].size();
//     if (board[x][y] != 0) {
//         return false;
//     }
//     return true;
// }
//
// void simulate(vector<vector<int>>& board, int x, int y, char t) {
//     char original_mark = i2c[board[x][y]];
//     board[x][y] = c2i[t];
//     int n = board.size();
//     int m = board[0].size();
//     int time = 0;
//     int num = 4;
//     vector<pair<int, int>> pos(4, {x, y});
//     vector<pair<int, int>> dir;
//     if (t == '+') {
//         dir = dir1;
//     } else if (t == 'x') {
//         dir = dir2;
//     } else if (t == '*') {
//         dir = dir3;
//         num = 8;
//         pos.resize(8, {x, y});
//     }
//     bool flag = true;
//     while (flag) {
//         time++;
//         for (int i = 0; i < num; i++) {
//             int nx = pos[i].first + dir[i].first;
//             int ny = pos[i].second + dir[i].second;
//             if (!isValid(board, nx, ny, t)) {
//                 flag = false;
//             }
//             pos[i] = {nx, ny};
//         }
//     }
//     string s;
//     for (int i = 0; i < num; i++) {
//         auto [nx, ny] = pos[i];
//         if (isValid(board, nx, ny, t)) {
//             board[nx][ny] = c2i[t];
//             s += '.';
//         } else if (board[nx][ny] > 0) {
//             // 碰撞消除标记
//             s += i2c[board[nx][ny]];
//             board[nx][ny] = 0;
//         } else {
//             // 出界
//             s += 'o';
//         }
//     }
//
//     cout << original_mark << ' ' << time << ' ' << s << endl;
// }
//
// int main() {
//     int n, m, q;
//     cin >> n >> m >> q;
//     vector<vector<int>> board(n + 2, vector<int>(m + 2, 0));
//     // 出界为o, -1
//     for (int i = 0; i <= n + 1; i++) {
//         board[i][0] = -1;
//         board[i][m + 1] = -1;
//     }
//     for (int i = 0; i <= m + 1; i++) {
//         board[0][i] = -1;
//         board[n + 1][i] = -1;
//     }
//     // 1 -> n
//     while (q--) {
//         int x, y;
//         char t;
//         cin >> x >> y >> t;
//         simulate(board, x, y, t);
//     }
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> c2i = {{'.', 0}, {'+', 1}, {'x', 2}, {'*', 3}, {'o', -1}};
unordered_map<int, char> i2c = {{0, '.'}, {1, '+'},  {2, 'x'}, {3, '*'}, {-1, 'o'}};
// 按上下左右左上左下右上右下顺序
const vector<pair<int, int>> dir1 = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const vector<pair<int, int>> dir2 = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
const vector<pair<int, int>> dir3 = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}};


struct Node {
    int x, y;
    int tag = 0;

    Node(int x, int y, int tag) : x(x), y(y), tag(tag) {}
};

struct Tags {
    multimap<int, Node*> x;
    multimap<int, Node*> y;
    multimap<int, Node*> xpy;
    multimap<int, Node*> xmy;
    map<pair<int, int>, Node*> xy;

    void add(Node* node) {
        x.insert({node->x, node});
        y.insert({node->y, node});
        xpy.insert({node->x + node->y, node});
        xmy.insert({node->x - node->y, node});
        xy[{node->x, node->y}] = node;
    }

    void remove(Node* node) {
        vector<multimap<int, Node*>*> maps = {&x, &y, &xpy, &xmy};
        vector<int> vals = {node->x, node->y, node->x + node->y, node->x - node->y};
        for (int i = 0; i < 4; i++) {
            auto range = maps[i]->equal_range(vals[i]);
            for (auto it = range.first; it != range.second; it++) {
                if (it->second == node) {
                    maps[i]->erase(it);
                    break;
                }
            }
        }
        xy.erase({node->x, node->y});
        delete node;
    }

    void change_tag(Node* node, int tag) {
        node->tag = tag;
    }

    Node* find(int x, int y) {
        auto it = xy.find({x, y});
        if (it != xy.end()) {
            return it->second;
        }
        return nullptr;
    }

    int search_min_dis(int x, int y, int type, int n, int m) {
        // 1:搜索上下左右最短
        // 2:搜索斜向最短距离
        // 3:搜索上下左右和斜向最短距离
        int res = INT_MAX;
        int d_up = x;
        int d_down = n - x + 1;
        int d_left = y;
        int d_right = m - y + 1;
        res = min({d_up, d_down, d_left, d_right});
        if (type & 1) {
            auto range_col = this->y.equal_range(y);
            for (auto it = range_col.first; it != range_col.second; it++) {
                if (it->second->x == x || it->second->tag == 0) {
                    continue;
                }
                res = min(res, abs(it->second->x - x));
            }
            auto range_row = this->x.equal_range(x);
            for (auto it = range_row.first; it != range_row.second; it++) {
                if (it->second->y == y || it->second->tag == 0) {
                    continue;
                }
                res = min(res, abs(it->second->y - y));
            }
        }
        if (type & 2) {
            auto range_diag1 = this->xpy.equal_range(x + y);
            for (auto it = range_diag1.first; it != range_diag1.second; it++) {
                if ((it->second->x == x && it->second->y == y) || it->second->tag == 0) {
                    continue;
                }
                res = min(res, abs(it->second->x - x));
            }
            auto range_diag2 = this->xmy.equal_range(x - y);
            for (auto it = range_diag2.first; it != range_diag2.second; it++) {
                if ((it->second->x == x && it->second->y == y) || it->second->tag == 0) {
                    continue;
                }
                res = min(res, abs(it->second->x - x));
            }
        }
        return res;
    }
};

int dist(Node* a, Node* b, int type) {
    if (type == 1) {
        return abs(a->x - b->x) + abs(a->y - b->y);
    } else {
        // 斜向距离
        return abs(a->x - b->x);
    }
}

void simulate(Tags& tags, int x, int y, char t, int n, int m) {

    int original_tag = 0;
    Node* it = tags.find(x, y);
    if (it) {
        original_tag = it->tag;
        tags.change_tag(it, c2i[t]);
    } else {
        it = new Node(x, y, c2i[t]);
        tags.add(it);
    }

    vector<int> output;
    int d = 0;
    const vector<pair<int, int>>* current_dirs = nullptr;

    if (t == '+') {
        current_dirs = &dir1;
        d = tags.search_min_dis(x, y, 1, n, m);
    }
    else if (t == 'x') {
        current_dirs = &dir2;
        d = tags.search_min_dis(x, y, 2, n, m);
    }
    else if (t == '*') {
        current_dirs = &dir3;
        d = tags.search_min_dis(x, y, 3, n, m);
    }

    for (auto& dir : *current_dirs) {
        int nx = x + dir.first * d;
        int ny = y + dir.second * d;
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) { // 界内
            Node* node = tags.find(nx, ny);
            if (node && node->tag != 0) {
                output.push_back(node->tag);
                // tags.remove(node); 用修改为0代替remove
                tags.change_tag(node, 0);
            } else { // 未碰撞
                output.push_back(0);
                if (node) {
                    tags.change_tag(node, c2i[t]);
                } else {
                    tags.add(new Node(nx, ny, c2i[t]));
                }
            }
        } else { // 出界
            output.push_back(-1);
        }
    }

    cout << i2c[original_tag] << ' ' << d << ' ';
    for (auto& o : output) {
        cout << i2c[o];
    }
    cout << endl;

}

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    Tags tags;
    // 出界为o, -1
    // 1 -> n
    while (q--) {
        int x, y;
        char t;
        cin >> x >> y >> t;
        simulate(tags, x, y, t, n, m);
    }
    return 0;
}
