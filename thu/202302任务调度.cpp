//
// Created by lisiyi on 25-8-2.
//18:22->19:01
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    int id, a, next, pre;
};

vector<Node> nodes;
int idx = 0;
int cnt = 0;
int tail = 0; // 0作为dummy节点
priority_queue<pair<int, int>> max_a_pq;

int main() {
    int n, m;
    cin >> n >> m;
    nodes.resize(n + 1, {-1, -1, -1, -1});
    while (n--) {
        int type;
        cin >> type;
        if (type == 1) {
            int a;
            cin >> a;

            idx++;
            if (cnt >= m) {cout << "ERR" << endl; continue;}

            nodes[tail].next = idx;
            nodes[idx].pre = tail;

            nodes[idx].id = idx;
            nodes[idx].a = a;
            tail = idx;
            cnt++;
            max_a_pq.emplace(a, idx);
            cout << idx << endl;
        } else if (type == 2) {
            int a, x;
            cin >> a >> x;

            idx++;
            if (cnt >= m) {cout << "ERR" << endl; continue;}
            if (nodes[x].id == -1) {cout << "ERR" << endl; continue;}

            int prev = nodes[x].pre;
            nodes[prev].next = idx;
            nodes[x].pre = idx;
            nodes[idx].pre = prev;
            nodes[idx].next = x;

            nodes[idx].id = idx;
            nodes[idx].a = a;
            cnt++;
            max_a_pq.emplace(a, idx);
            cout << idx << endl;
        } else if (type == 3) {
            if (cnt == 0) {cout << "ERR" << endl; continue;}
            int head = nodes[0].next;

            nodes[0].next = nodes[head].next;
            if (nodes[head].next != -1) nodes[nodes[head].next].pre = 0;

            cnt--;
            nodes[head].id = -1;
            if (head == tail) tail = 0;
            cout << head << endl;
        } else if (type == 4) {
            if (cnt == 0) {cout << "ERR" << endl; continue;}
            int id = 0;
            while (nodes[max_a_pq.top().second].id == -1) {
                max_a_pq.pop();
            }
            id = max_a_pq.top().second;
            max_a_pq.pop();

            int prev = nodes[id].pre;
            int next = nodes[id].next;
            nodes[prev].next = next;
            if (next != -1) nodes[next].pre = prev;

            cnt--;
            nodes[id].id = -1;
            if (id == tail) tail = prev;
            cout << id << endl;
        }
    }
    return 0;
}