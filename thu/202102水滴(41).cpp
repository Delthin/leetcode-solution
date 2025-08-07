#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

map<pair<int, int>, int> board;
map<int, set<int>> x_coords;
map<int, set<int>> y_coords;

int spread_count_this_turn = 0;

void receive(int x, int y);

void erase(int x, int y)
{
    board.erase({x, y});
    if (x_coords.count(x)) {
        x_coords.at(x).erase(y);
        if (x_coords.at(x).empty()) {
            x_coords.erase(x);
        }
    }
    if (y_coords.count(y)) {
        y_coords.at(y).erase(x);
        if (y_coords.at(y).empty()) {
            y_coords.erase(y);
        }
    }
}

void spread(int x, int y)
{
    spread_count_this_turn++;

    if (y_coords.count(y)) {
        auto &col_set = y_coords.at(y);
        auto it = col_set.lower_bound(x);
        if (it != col_set.begin()) {
            receive(*(--it), y);
        }
    }

    if (x_coords.count(x)) {
        auto &row_set = x_coords.at(x);
        auto it = row_set.lower_bound(y);
        if (it != row_set.begin()) {
            receive(x, *(--it));
        }
    }

    if (y_coords.count(y)) {
        auto &col_set = y_coords.at(y);
        auto it = col_set.upper_bound(x);
        if (it != col_set.end()) {
            receive(*it, y);
        }
    }

    if (x_coords.count(x)) {
        auto &row_set = x_coords.at(x);
        auto it = row_set.upper_bound(y);
        if (it != row_set.end()) {
            receive(x, *it);
        }
    }
}

void receive(int x, int y)
{
    if (board.find({x, y}) == board.end()) {
        return;
    }
    board.at({x, y})++;
    if (board.at({x, y}) > 4) {
        erase(x, y);
        spread(x, y);
    }
}

void add(int x, int y, int cnt)
{
    if (board.find({x, y}) == board.end()) {
        board[{x, y}] = cnt;
        x_coords[x].insert(y);
        y_coords[y].insert(x);
    } else {
        board.at({x, y}) += cnt;
    }
}

int main()
{
    // 快速 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, c, T;
    cin >> n >> m >> c >> T;

    for (int i = 0; i < c; i++) {
        int x, y, a;
        cin >> x >> y >> a;
        add(x, y, a);
    }

    while (T--) {
        spread_count_this_turn = 0;
        int u, v;
        cin >> u >> v;
        receive(u, v);
        cout << spread_count_this_turn << "\n";
    }

    for (auto const &[pos, cnt] : board) {
        cout << pos.first << " " << pos.second << " " << cnt << "\n";
    }

    return 0;
}