#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int NONE = -1;
const int FIRST = 1;
const int SECOND = 0;

struct Block {
    int owner = NONE;
    bool canput = true;
    int firstput = 0;
    int secondput = 0;
    vector<int> grid;
    Block() {
        grid.resize(9, -1);
    }
    bool put(int step, int j) {
        if (owner != NONE || grid[j] != NONE) {
            return false;
        }
        if (step % 2 == 0) {
            secondput++;
        } else {
            firstput++;
        }
        grid[j] = step % 2;
        if (firstput + secondput == 9) {
            canput = false;
        }
        return true;
    }
    bool occupy(int step) {
        if (owner != NONE) {
            return false;
        }
        int o = step % 2;
        // 检查横竖斜是否有三子相连
        for (int i = 0; i < 3; i++) {
            if (grid[i] == o && grid[i+3] == o && grid[i+6] == o) {
                owner = o;
                canput = false;
                return true;
            }
        }
        for (int i = 0; i < 9; i += 3) {
            if (grid[i] == o && grid[i+1] == o && grid[i+2] == o) {
                owner = o;
                canput = false;
                return true;
            }
        }
        if (grid[0] == o && grid[4] == o && grid[8] == o) {
            owner = o;
            canput = false;
            return true;
        }
        if (grid[2] == o && grid[4] == o && grid[6] == o) {
            owner = o;
            canput = false;
            return true;
        }
        return false;
    }
};
Block blocks[9];

bool win(int step) {
    int o = step % 2;
    for (int i = 0; i < 3; i++) {
        if (blocks[i].owner == o && blocks[i + 3].owner == o && blocks[i + 6].owner == o) {
            return true;
        }
    }
    for (int i = 0; i < 9; i += 3) {
        if (blocks[i].owner == o && blocks[i+1].owner == o && blocks[i+2].owner == o) {
            return true;
        }
    }
    if (blocks[0].owner == o && blocks[4].owner == o && blocks[8].owner == o) {
        return true;
    }
    if (blocks[2].owner == o && blocks[4].owner == o && blocks[6].owner == o) {
        return true;
    }
    return false;
}

void illegal(int step) {
    cout << "illegal" << endl;
    cout << step << endl;
}

int main() {
    int n;
    cin >> n;
    int last_y = -1;
    for (int step = 1; step <= n; step++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        if (step == 1 && x == 4 && y == 4) {
            illegal(step);
            return 0;
        };
        if (last_y != -1 && blocks[last_y].owner == NONE && x != last_y) {
            illegal(step);
            return 0;
        }
        last_y = y;
        if (!blocks[x].put(step, y)) {
            illegal(step);
            return 0;
        }
        if (blocks[x].occupy(step) && win(step)) {
            int o = step % 2;
            cout << (o == FIRST ? "first" : "second") << endl;
            cout << step << endl;
            return 0;
        }
    }
    // 如果所有格子都不能走了
    // 先比拼占领的大格数，多者获胜；若占领的大格数一样，则比拼未占领的大格中占领的小格数，多者获胜。
    bool canput = false;
    for (int i = 0; i < 9; i++) {
        if (blocks[i].canput) {
            canput = true;
            break;
        }
    }
    if (canput) {
        cout << "to be continued" << endl;
        return 0;
    }
    int firstwin = 0;
    int secondwin = 0;
    for (int i = 0; i < 9; i++) {
        if (blocks[i].owner == FIRST) {
            firstwin++;
        } else if (blocks[i].owner == SECOND) {
            secondwin++;
        }
    }
    if (firstwin == secondwin) {
        // 比较未占领的小格
        int first_cnt = 0;
        int second_cnt = 0;
        for (int i = 0; i < 9; i++) {
            if (blocks[i].owner == NONE) {
                first_cnt += blocks[i].firstput;
                second_cnt += blocks[i].secondput;
            }
        }
        if (first_cnt < second_cnt) {
            cout << "second" << endl;
        } else {
            cout << "first" << endl;
        }
    } else if (firstwin < secondwin) {
        cout << "second" << endl;
    } else {
        cout << "first" << endl;
    }
    cout << n << endl;
    return 0;

}