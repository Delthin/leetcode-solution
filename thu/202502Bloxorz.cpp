//
// Created by lisiyi on 25-8-3.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int GLASS = 2;
constexpr int FLOOR = 1;
constexpr int EMPTY = -1;

const int dir[4][2] = {{1, 0},{-1,0}, {0, 1}, {0, -1}};

struct Pos {
    int x, y;
    const bool operator< (Pos& o) {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

bool check(const vector<vector<int>>& grid, vector<Pos>& pos);

int hash(vector<Pos>& pos) {
    int id = 1;
    if (pos.size() == 2) {
        if (pos[0].x == pos[1].x) {
            id = 2;
        } else {
            id = 3;
        }
    }
    return id * (500 * 500) + pos[0].x * 500 + pos[0].y;
}

struct State {
    vector<Pos> pos;

    int hash() {
        int id = 1;
        if (pos.size() == 2) {
            if (pos[0].x == pos[1].x) {
                id = 2;
            } else {
                id = 3;
            }
        }
        return id * (500 * 500) + pos[0].x * 500 + pos[0].y;
    };

    bool is_horizon() {
        if (pos.size() == 1) return false;
        bool horizon = true;
        if (pos[0].x - pos[1].x != 0) {
            horizon = false;
        }
        return horizon;
    }

    vector<State> get_next_s(const vector<vector<int>>& grid) {
        vector<State> states;
        if (pos.size() == 1) {
            int x = pos[0].x, y = pos[0].y;
            for (int i = 0; i < 4; i++) {
                int nx1 = x + dir[i][0];
                int nx2 = nx1 + dir[i][0];
                int ny1 = y + dir[i][1];
                int ny2 = ny1 +dir[i][1];
                vector<Pos> pos_ = {{nx1, ny1}, {nx2, ny2}};
                sort(pos_.begin(), pos_.end());
                if (check(grid, pos_)) {
                    states.push_back({pos_});
                }
            }
        } else {
            // 分滚成竖着还是继续躺着
            bool horizon = is_horizon();
            vector<vector<Pos>> poses;
            if (horizon) {
                // y + 1或者y - 1
                poses.push_back({{pos[0].x, pos[0].y - 1}});
                poses.push_back({{pos[1].x, pos[1].y + 1}});
                poses.push_back({{pos[0].x - 1, pos[0].y},
                {pos[1].x - 1, pos[1].y}});
                poses.push_back({{pos[0].x + 1, pos[0].y},
                {pos[1].x + 1, pos[1].y}});
            } else {
                poses.push_back({{pos[0].x - 1, pos[0].y}});
                poses.push_back({{pos[1].x + 1, pos[1].y}});
                poses.push_back({{pos[0].x, pos[0].y + 1},
                {pos[1].x, pos[1].y + 1}});
                poses.push_back({{pos[0].x, pos[0].y - 1},
                {pos[1].x, pos[1].y - 1}});
            }
            for (auto& pos_:poses) {
                if (check(grid, pos_)) {
                    states.push_back({pos_});
                }
            }
        }
        return states;
    }
};

bool check(const vector<vector<int>>& grid, vector<Pos>& pos) {
    State s = {pos};

    int a = 0, b = 0;
    Pos p_a = pos[0];
    if (p_a.x >= grid.size() || p_a.y >= grid[0].size() || p_a.x < 0 || p_a.y < 0) return false;
    a = grid[p_a.x][p_a.y];
    if (pos.size() == 2) {
        Pos p_b = pos[1];
        if (p_b.x >= grid.size() || p_b.y >= grid[0].size() || p_b.x < 0 || p_b.y < 0) return false;
        b = grid[p_b.x][p_b.y];
        if (a == FLOOR) {
            return b != EMPTY;
        } else if (a == GLASS) {
            return b != EMPTY;
        } else {
            return false;
        }
    } else {
        return a == FLOOR;
    }
}

void solve () {
    int n, m;
    cin >> n >> m;
    State start;
    Pos end_pos;
    vector<vector<int>> grid(n, vector<int>(m));
    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> c;
            if (c == '#') grid[i][j] = -1;
            else if (c == '.') grid[i][j] = 1;
            else if (c == 'X') {
                grid[i][j] = 1;
                start.pos.push_back({i, j});
            } else if (c == 'E') grid[i][j] = 2;
            else if (c == 'O') {
                grid[i][j] = 1;
                end_pos = {i, j};
            }
        }
    }
    sort(start.pos.begin(), start.pos.end());
    vector<bool> visited(2e6, false);
    queue<State> q;
    q.push(start);
    visited[start.hash()] = true;
    int step = 0;
    bool end = false;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            State s = q.front();
            q.pop();

            if (s.pos.size() == 1 && s.pos[0].x == end_pos.x && s.pos[0].y == end_pos.y) {
                end = true;
                break;
            }

            vector<State> states = s.get_next_s(grid);
            for (auto& next_s:states) {
                if (!visited[next_s.hash()]) {
                    q.emplace(next_s);
                    visited[next_s.hash()] = true;
                }
            }
        }
        if (end) break;
        step++;
    }
    if (!end) {
        cout << -1 << endl;
    } else {
        cout << step << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}