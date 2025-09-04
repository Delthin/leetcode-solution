#include <bits/stdc++.h>
using namespace std;
const int N_MAX = 100005;

vector<double> slopes(N_MAX, 0.0);

struct SegTree {
    struct Node {
        double max_slope; // 维护区间最大斜率
        int count;        // 维护区间内可见楼房数量（这是在“无外部遮挡”的情况下）
    };

    vector<Node> tr;
    int n;

    SegTree(int size) : n(size) {
        tr.resize(4 * n + 5);
        // 初始高度均为0，所以无需 build，在 update 时会自下而上建立
    }
    // 计算在节点 u（区间[l,r]）中，以 threshold 为前提斜率，能看到的楼房数
    int calc_contrib_with_threshold(int u, int l, int r, double threshold) {
        // 剪枝1：如果当前区间的最大斜率都不如门槛高，那这个区间贡献为0
        if (tr[u].max_slope <= threshold) {
            return 0;
        }
        // 基准情况：到达叶子节点
        if (l == r) {
            return (slopes[l] > threshold) ? 1 : 0;
        }
        // 优化：如果当前区间的第一个楼的斜率就大于门槛，那么在这个区间内部的相对可见关系不变。我们可以直接返回预先计算好的 count 值。
        if (slopes[l] > threshold) {
            return tr[u].count;
        }
        int mid = l + (r - l) / 2;
        int lc = u << 1, rc = u << 1 | 1;

        // 如果左子树的最大斜率都无法超过门槛，那么左子树贡献为0，我们只用带着原门槛去查右子树
        if (tr[lc].max_slope <= threshold) {
            return calc_contrib_with_threshold(rc, mid + 1, r, threshold);
        } else {
            // 否则，总贡献 = 左子树的贡献 + 右子树的贡献
            return calc_contrib_with_threshold(lc, l, mid, threshold) + (tr[u].count - tr[lc].count);
        }
    }

    void pushup(int u, int l, int r) {
        int mid = l + (r - l) / 2;
        int lc = u << 1, rc = u << 1 | 1;
        tr[u].max_slope = max(tr[lc].max_slope, tr[rc].max_slope);
        // 总数 = 左子树的可见数 + 在右子树中以左子树最大斜率为门槛能看到的数量
        tr[u].count = tr[lc].count + calc_contrib_with_threshold(rc, mid + 1, r, tr[lc].max_slope);
    }

    void update(int p, int H) {
        _update(1, 1, n, p, H);
    }

    void _update(int u, int l, int r, int p, int H) {
        if (l == r) {
            slopes[p] = (p == 0) ? 0.0 : (double)H / p; // 计算斜率
            tr[u].max_slope = slopes[p];
            tr[u].count = (H > 0) ? 1 : 0; // 高度为0的楼看不见，算0
            return;
        }
        int mid = l + (r - l) / 2;
        if (p <= mid) {
            _update(u << 1, l, mid, p, H);
        } else {
            _update(u << 1 | 1, mid + 1, r, p, H);
        }
        pushup(u, l, r);
    }

    int get_answer() {
        return tr[1].count;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;

    SegTree seg_tree(N);

    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        seg_tree.update(x, y);
        cout << seg_tree.get_answer() << "\n";
    }

    return 0;
}

