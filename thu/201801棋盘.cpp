#include <bits/stdc++.h>
using namespace std;

const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int n, m, k, t;
struct Node {
    int x, y;
    int dir;
    int f;
    bool live = true;

    Node* move() {
        if (!live) return this;
        int nx = x + dirs[dir][0];
        int ny = y + dirs[dir][1];
        if (nx <= 0 || nx > n || ny <= 0 || ny > m) {
            if (dir == 0) {
                dir = 1;
            } else if (dir == 1) {
                dir = 0;
            } else if (dir == 2) {
                dir = 3;
            } else {
                dir = 2;
            }
        } else {
            x = nx;
            y = ny;
        }
        return this;
    }

};
vector<Node> nodes;

void simulate() {
    map<pair<int, int>, vector<Node*>> mp;
    for (int i = 0; i < k; i++) {
        if (!nodes[i].live) continue;
        Node* node = nodes[i].move();
        pair<int, int> pos = {node->x, node->y};
        mp[pos].push_back(node);
    }
    for (auto& [pos, nodes] : mp) {
        if (nodes.size() > 1) {
            int max_f = 0;
            Node* max_node = nullptr;
            for (auto node : nodes) {
                if (node->f > max_f) {
                    max_f = node->f;
                    max_node = node;
                }
            }
            for (auto node : nodes) {
                if (node != max_node) {
                    node->live = false;
                }
            }
        }
    }
}

int main() {
    cin >> n >> m >> k;
    nodes.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> nodes[i].x >> nodes[i].y >> nodes[i].dir >> nodes[i].f;
    }
    cin >> t;
    while (t --) {
        simulate();
    }
    for (int i = 0; i < k; i++) {
        cout << nodes[i].x << " " << nodes[i].y << endl;
    }
}