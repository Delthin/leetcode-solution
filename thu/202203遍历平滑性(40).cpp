#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;

struct Node {
    int a = 0;
    int l = 0, r = 0;
    Node(int a, int id): a(a) {
    }
};

Node* root;
vector<Node*> nodes;

// vector<int> get_preorder() {
//     vector<int> preorder;
//     preorder.push_back(0);
//     function<void(Node*)> dfs = [&](Node* node) {
//         preorder.push_back(node->id);
//         if (node->l) dfs(node->l);
//         if (node->r) dfs(node->r);
//     };
//     dfs(root);
//     return preorder;
// }
//
// ll get_ans() {
//     auto preorder = get_preorder();
//     ll ans = 0;
//     int prev_a = nodes[1]->a;
//     for (int i = 2; i <= n; i++) {
//         int now_a = nodes[preorder[i]]->a;
//         ans += abs(now_a - prev_a);
//         prev_a = now_a;
//     }
//     return ans;
// }
//
// void solve() {
//     vector<Node*> swappable_nodes;
//     for (int i = 1; i <= n; ++i) {
//         if (nodes[i]->l && nodes[i]->r) {
//             swappable_nodes.push_back(nodes[i]);
//         }
//     }
//     ll ans = LONG_LONG_MAX;
//     function<void(int k)> dfs = [&](int k) {
//         if (k == swappable_nodes.size()) {
//             ans = min(get_ans(), ans);
//             return;
//         }
//         Node* node = swappable_nodes[k];
//         dfs(k + 1);
//         swap(node->l, node->r);
//         dfs(k + 1);
//         swap(node->r, node->r);
//     };
//     dfs(0);
//     cout << ans << endl;
// }

vector<vector<ll>> dp;
vector<vector<int>> leaves;

// DFS 预处理，得到每个子树包含的节点列表
void get_leaves(int u) {
    if (u == 0) return;
    Node* node = nodes[u];
    int l = node->l, r = node->r;
    // 后序遍历
    get_leaves(l);
    get_leaves(r);

    if (l == 0 && r == 0) {
        // u 本身是叶子
        leaves[u].push_back(u);
    } else {
        // 合并左右子树的叶子列表
        if (l) {
            leaves[u].insert(leaves[u].end(), leaves[l].begin(), leaves[l].end());
        }
        if (r) {
            leaves[u].insert(leaves[u].end(), leaves[r].begin(), leaves[r].end());
        }
    }
}
void dp_dfs(int u) {
    if (u == 0) return;
    int l = nodes[u]->l, r = nodes[u]->r;
    dp_dfs(l);
    dp_dfs(r);
    if (l == 0 && r == 0) {
        // u 本身是叶子
        dp[u][u] = 0;
        return;
    }
    if (r == 0) {
        // 只有左子树，左子树的end_leaf必然是自己的end_leaf
        for (int leaf: leaves[l]) {
            dp[u][leaf] = abs(nodes[u]->a - nodes[l]->a) + dp[l][leaf];
        }
        return;
    }
    // 左右都有，分别遍历左右子树的最终叶子，不用实际swap，只需要分别计算就行
    // 情况一：u->l->r，l的leaf连接r, u连接r的leaf
    ll min_l_to_r = LONG_LONG_MAX;
    for (int l_leaf: leaves[l]) {
        min_l_to_r = min(min_l_to_r, dp[l][l_leaf] + abs(nodes[l_leaf]->a - nodes[r]->a));
    }
    for (int r_leaf: leaves[r]) {
        // u->l->l_leaf->r->r_leaf
        dp[u][r_leaf] = abs(nodes[u]->a - nodes[l]->a) + min_l_to_r + dp[r][r_leaf];
    }
    // 情况二：u->r->l相当于做了swap
    ll min_r_to_l = LONG_LONG_MAX;
    for (int r_leaf: leaves[r]) {
        min_r_to_l = min(min_r_to_l, dp[r][r_leaf] + abs(nodes[r_leaf]->a - nodes[l]->a));
    }
    for (int l_leaf: leaves[l]) {
        dp[u][l_leaf] = abs(nodes[u]->a - nodes[r]->a) + min_r_to_l + dp[l][l_leaf];
    }
}

void solve2() {
    dp.resize(n + 1, vector<ll>(n + 1, LONG_LONG_MAX));
    leaves.resize(n + 1);
    get_leaves(1);
    // dp[i][j] 表示以 i 为根，末端为 j 的最小平滑值
    // dp[i][j] = abs(a_i - a_i->l) + dp[i->l][i->l->end] + abs(a_i->l->end - a_i->r) + dp[i->r][i->r->end];
    // for(int
    dp_dfs(1);
    ll ans = LONG_LONG_MAX;
    for (int leaf: leaves[1]) {
        ans = min(ans, dp[1][leaf]);
    }
    cout << ans << endl;
}

int main() {
    cin >> n;
    nodes.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        nodes[i] = new Node(a, i);
    }
    for (int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        if (!nodes[fa]->l) {
            nodes[fa]->l = i;
        } else {
            nodes[fa]->r = i;
        }
    }
    root = nodes[1];
    solve2();
    return 0;
}