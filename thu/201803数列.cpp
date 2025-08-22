// 平衡树做法ak
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node *l=nullptr, *r=nullptr;
    int val=0, sz=1; // val: 节点值, sz: 子树大小
    vector<int>cnt;
    unsigned pri;    // 随机优先级
    bool rev_tag=false; // 翻转懒标记
    int add_tag=0;
    // --- 扩展点: 在此添加其他维护信息, 如 sum, max_v ---
    // long long sum = 0;

    explicit Node(int v) : val(v), pri(rng()) {
        // --- 扩展点: 在此初始化新信息 ---
        // sum = v;
        cnt.resize(3, 0);
        cnt[v] = 1;
    }
};

int size(Node* t) { return t ? t->sz : 0; }

void pull(Node* t) { // pushup: 从子节点更新父节点信息
    if (!t) return;
    t->sz = 1 + size(t->l) + size(t->r);
    t->cnt = {0, 0, 0};
    if (t->l) {
        for (int i = 0; i < 3; i++) {
            t->cnt[i] += t->l->cnt[i];
        }
    }
    if (t->r) {
        for (int i = 0; i < 3; i++) {
            t->cnt[i] += t->r->cnt[i];
        }
    }
    t->cnt[t->val]++;
}

void apply_add(Node* t, int val_to_add) {
    if (!t || val_to_add == 0) return;
    int shift = val_to_add % 3;

    t->add_tag += val_to_add; // 更新 tag

    // 立刻更新 val 和 cnt
    t->val = (t->val + shift) % 3;
    vector<int> old_cnt = t->cnt;
    for (int i = 0; i < 3; i++) {
        t->cnt[(i + shift) % 3] = old_cnt[i];
    }
}

void apply_rev(Node* t) {
    if (!t) return;
    swap(t->l, t->r);
    t->rev_tag ^= 1;
}

// 你的 push 也要相应修改，因为它只负责传递，应用效果的事情 apply_add_immediately 会做
void push(Node* t) {
    if (!t) return;
    if (t->rev_tag) {
        apply_rev(t->l);
        apply_rev(t->r);
        t->rev_tag = false;
    }
    if (t->add_tag != 0) {
        if (t->add_tag % 3 == 0) {
            t->add_tag = 0;
            return;
        }
        // push 只负责把 tag 传递下去，并让子节点立刻更新
        apply_add(t->l, t->add_tag);
        apply_add(t->r, t->add_tag);
        t->add_tag = 0;
    }
}

Node* merge(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;
    if (a->pri < b->pri) { // 设 pri 越小优先级越高
        push(a); a->r = merge(a->r, b); pull(a); return a;
    } else {
        push(b); b->l = merge(a, b->l); pull(b); return b;
    }
}

void split_by_rank(Node* t, int k, Node*& a, Node*& b) {
    if (!t) { a = b = nullptr; return; }
    push(t);
    if (size(t->l) >= k) {
        b = t; split_by_rank(t->l, k, a, b->l); pull(b);
    } else {
        a = t; split_by_rank(t->r, k - size(t->l) - 1, a->r, b); pull(a);
    }
}

void point_set(Node*& root, int i, int x) {
    Node *a, *b, *c;
    split_by_rank(root, i - 1, a, b);
    split_by_rank(b, 1, b, c);
    if (b) {
        b->val = x;
        pull(b);// 维护类似sum的区间信息
    }
    root = merge(a, merge(b, c));
}

void range_add(Node*& root, int l, int r, int val) {
    if (l > r) return;
    Node *a, *b, *c;
    split_by_rank(root, l - 1, a, b);
    split_by_rank(b, r - l + 1, b, c);
    if (b) {
        apply_add(b, val);
    }
    root = merge(merge(a, b), c);
}

void reverse_interval(Node*& root, int l, int r) {
    if (l >= r) return;
    Node *a, *b, *c;
    split_by_rank(root, l - 1, a, b);
    split_by_rank(b, r - l + 1, b, c);
    if (b) apply_rev(b);
    root = merge(merge(a, b), c);
}

bool range_query(Node*& root, int l, int r) {
    if (l > r) return false;
    Node *a, *b, *c;
    split_by_rank(root, l - 1, a, b);
    split_by_rank(b, r - l + 1, b, c);
    bool result = false;
    if (b) {
        result = b->cnt[0] >= 3 || b->cnt[1] >= 3 || b->cnt[2] >= 3;
    }
    root = merge(merge(a, b), c);
    return result;
}

int main(){
    int n;
    cin>>n;
    Node* root = nullptr;
    for(int i=0,x;i<n;i++){
        cin>>x;
        root = merge(root,new Node(x));
    }
    int q;  cin>>q;
    while(q--){
        int op,l,r; cin>>op>>l>>r;
        if(op==1){                 // 1 i x
            point_set(root,l,r);    // 注意题面已经把 x 读到 r 里
        }else if(op==2){           // 2 i j
            range_add(root,l, r, 1);
        }else if(op==3){           // 3 i j
            reverse_interval(root,l,r);
        }else{                     // 4 i j
            cout<<(range_query(root,l,r)?"yes\n":"no\n");
        }
    }
    return 0;
}
