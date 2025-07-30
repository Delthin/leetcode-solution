// 平衡树做法ak
#include <bits/stdc++.h>
using namespace std;
struct Node {
    int val, sz;
    int cnt[3];
    int add;           // 懒标记：+add (mod 3)
    bool rev;          // 懒标记：翻转
    unsigned pri;
    Node *l, *r;
    Node(int v): val(v), sz(1), add(0), rev(false),
                 pri(((unsigned)rand()<<16)^rand()), l(nullptr), r(nullptr) {
        cnt[0]=cnt[1]=cnt[2]=0;
        ++cnt[v];
    }
};
using pNode = Node*;

int getsz(pNode t){ return t? t->sz : 0; }
void pull(pNode t){
    if(!t) return;
    t->sz = 1 + getsz(t->l) + getsz(t->r);
    t->cnt[0] = t->cnt[1] = t->cnt[2] = 0;
    if(t->l){
        t->cnt[0]+=t->l->cnt[0];
        t->cnt[1]+=t->l->cnt[1];
        t->cnt[2]+=t->l->cnt[2];
    }
    ++t->cnt[t->val];
    if(t->r){
        t->cnt[0]+=t->r->cnt[0];
        t->cnt[1]+=t->r->cnt[1];
        t->cnt[2]+=t->r->cnt[2];
    }
}
void apply_add(pNode t,int a){
    if(!t) return;
    t->add = (t->add + a)%3;
    t->val = (t->val + a)%3;
    // 循环移位 cnt 数组
    int tmp[3]={t->cnt[0],t->cnt[1],t->cnt[2]};
    for(int i=0;i<3;i++)
        t->cnt[(i+a)%3]=tmp[i];
}
void apply_rev(pNode t){
    if(!t) return;
    t->rev^=1;
    swap(t->l,t->r);
}
void push(pNode t){
    if(!t) return;
    if(t->add){
        apply_add(t->l,t->add);
        apply_add(t->r,t->add);
        t->add=0;
    }
    if(t->rev){
        apply_rev(t->l);
        apply_rev(t->r);
        t->rev=false;
    }
}
void split(pNode t,int k,pNode& a,pNode& b){//前k个进a
    if(!t){a=b=nullptr; return;}
    push(t);
    if(getsz(t->l)>=k){
        split(t->l,k,a,t->l);
        b=t;
    }else{
        split(t->r,k-getsz(t->l)-1,t->r,b);
        a=t;
    }
    pull(t);
}
pNode merge(pNode a,pNode b){
    if(!a||!b) return a?a:b;
    if(a->pri < b->pri){
        push(a);
        a->r = merge(a->r,b);
        pull(a);
        return a;
    }else{
        push(b);
        b->l = merge(a,b->l);
        pull(b);
        return b;
    }
}
// ------------------------------------------------------------
// 4 种操作
// 1) 单点赋值
void pointSet(pNode& root,int pos,int x){
    pNode a,b,c;
    split(root,pos-1,a,b);
    split(b,1,b,c);              // b 是目标点
    if(b){
        b->val = x;
        b->cnt[0]=b->cnt[1]=b->cnt[2]=0;
        ++b->cnt[x];
    }else b=new Node(x);         // 理论上不会走到
    pull(b);
    root = merge(merge(a,b),c);
}
// 2) 区间 +1 (mod3)
void rangeAdd(pNode& root,int l,int r){
    pNode a,b,c;
    split(root,l-1,a,b);
    split(b,r-l+1,b,c);
    apply_add(b,1);
    root = merge(merge(a,b),c);
}
// 3) 区间翻转
void rangeRev(pNode& root,int l,int r){
    pNode a,b,c;
    split(root,l-1,a,b);
    split(b,r-l+1,b,c);
    apply_rev(b);
    root = merge(merge(a,b),c);
}
// 4) 查询 >=3 个相同数字？
bool rangeQuery(pNode& root,int l,int r){
    pNode a,b,c;
    split(root,l-1,a,b);
    split(b,r-l+1,b,c);
    bool ok = (b->cnt[0]>=3||b->cnt[1]>=3||b->cnt[2]>=3);
    root = merge(merge(a,b),c);
    return ok;
}
// ------------------------------------------------------------
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
    int n;  cin>>n;
    pNode root=nullptr;
    for(int i=0,x;i<n;i++){
        cin>>x;
        root = merge(root,new Node(x));
    }
    int q;  cin>>q;
    while(q--){
        int op,l,r; cin>>op>>l>>r;
        if(op==1){                 // 1 i x
            pointSet(root,l,r);    // 注意题面已经把 x 读到 r 里
        }else if(op==2){           // 2 i j
            rangeAdd(root,l,r);
        }else if(op==3){           // 3 i j
            rangeRev(root,l,r);
        }else{                     // 4 i j
            cout<<(rangeQuery(root,l,r)?"yes\n":"no\n");
        }
    }
    return 0;
}

// 线段树做法——40分
// #include <bits/stdc++.h>
// using namespace std;
//
// struct SegTree {
//     struct Node { long long cnt_0, cnt_1;}; // 计数节点，cnt_0表示0的个数，cnt_1表示1的个数, 2的数量可以用长度减去
//     struct Tag  { long long add; }; // 懒标记，add表示加的值
//     Node E_NODE = {0, 0};
//     Tag  E_TAG  = {0};
//     Node merge(const Node& a, const Node& b) {
//         return {a.cnt_0 + b.cnt_0, a.cnt_1 + b.cnt_1};
//     }
//     Tag compose(const Tag& lz, const Tag& t) {
//         return {lz.add + t.add};
//     }
//     // 标记t(mul,add)作用于节点n
//     Node apply(const Node& n, const Tag& t, int len) {
//         int mod = t.add % 3;
//         if (mod < 0) mod += 3;
//         switch (mod) {
//             case 1: return {len - n.cnt_0 - n.cnt_1, n.cnt_0};
//             case 2: return {n.cnt_1, len - n.cnt_0 - n.cnt_1};
//             default: return n;
//         }
//     }
//     bool is_empty_tag(const Tag& t) { return t.add == 0; }
// };
//
// SegTree SEGT; // 实例化核心逻辑
// vector<SegTree::Node> tr;
// vector<SegTree::Tag> lazy;
// vector<long long> initial_arr;
// int n;
//
// void apply_tag(int u, int len, const SegTree::Tag& t) {
//     // 将懒标记 t 应用到编号为 u 的节点
//     tr[u] = SEGT.apply(tr[u], t, len);
//     lazy[u] = SEGT.compose(lazy[u], t);
// }
//
// void pushup(int u) { // 从左右子节点更新父节点
//     tr[u] = SEGT.merge(tr[u << 1], tr[u << 1 | 1]);
// }
//
// void pushdown(int u, int len) {
//     // 将父节点的懒标记下传给子节点
//     if (!SEGT.is_empty_tag(lazy[u])) {
//         // 分别给左右打上标记，再清空父
//         apply_tag(u << 1, len - (len / 2), lazy[u]);
//         apply_tag(u << 1 | 1, len / 2, lazy[u]);
//         lazy[u] = SEGT.E_TAG;
//     }
// }
//
// void build(int u, int l, int r) {
//     // u: 当前节点 l,r: 当前节点表示区间
//     lazy[u] = SEGT.E_TAG;
//     if (l == r) {
//         if (initial_arr[l] == 0) tr[u] = {1, 0};
//         if (initial_arr[l] == 1) tr[u] = {0, 1};
//         if (initial_arr[l] == 2) tr[u] = {0, 0};
//         return;
//     }
//     int mid = l + r >> 1;
//     build(u << 1, l, mid);
//     build(u << 1 | 1, mid + 1, r);
//     pushup(u);
// }
//
// void update(int u, int l, int r, int L, int R, const SegTree::Tag& t) {
//     // u: 当前节点, [l,r]: 当前节点区间, [L,R]: 目标修改区间, t: 修改的标记
//     if (L <= l && r <= R) { // 完全覆盖
//         apply_tag(u, r - l + 1, t);
//         return;
//     }
//     pushdown(u, r - l + 1);
//     int mid = l + r >> 1;
//     if (L <= mid) update(u << 1, l, mid, L, R, t);
//     if (R > mid) update(u << 1 | 1, mid + 1, r, L, R, t);
//     pushup(u);
// }
//
// SegTree::Node query(int u, int l, int r, int L, int R) {
//     // u: 当前节点, [l,r]: 当前节点区间, [L,R]: 目标查询区间
//     if (L <= l && r <= R) return tr[u];
//     pushdown(u, r - l + 1);
//     int mid = l + r >> 1;
//     if (R <= mid) return query(u << 1, l, mid, L, R);
//     if (L > mid) return query(u << 1 | 1, mid + 1, r, L, R);
//     return SEGT.merge(query(u << 1, l, mid, L, R), query(u << 1 | 1, mid + 1, r, L, R));
// }
//
// int get(int i) {
//     // 迭代实现单点查询（避免递归开销）
//     int u = 1;
//     int l = 0, r = n - 1; // 使用全局n
//     while (l != r) {
//         pushdown(u, r - l + 1); // 沿途处理懒标记
//         int mid = (l + r) >> 1;
//         if (i <= mid) {
//             u = u << 1;
//             r = mid;
//         } else {
//             u = u << 1 | 1;
//             l = mid + 1;
//         }
//     }
//     // 直接访问叶子节点（此时路径上的懒标记已处理完毕）
//     auto& node = tr[u];
//     int diff = node.cnt_0 - node.cnt_1;
//     if (diff > 0) return 0;
//     if (diff < 0) return 1;
//     return 2;
// }
//
// void flip(int l, int r) {
//     while (l < r) {
//         int diff = get(l) - get(r);
//         if (diff != 0) {
//             update(1, 0, n - 1, l, l, {-diff});
//             update(1, 0, n - 1, r, r, {diff});
//         }
//         l++;
//         r--;
//     }
// }
//
//
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);
//     cin >> n;
//     initial_arr.resize(n);
//     for (int i = 0; i < n; i++) {
//         cin >> initial_arr[i];
//     }
//     tr.resize(4 * n);
//     lazy.resize(4 * n);
//     build(1, 0, n - 1);
//     int q;
//     cin >> q;
//     while (q--) {
//         int type, l, r;
//         cin >> type >> l >> r;
//         l--; r--; // 转为0基索引
//         if (type == 1) {
//             // 把第i位改成x
//             int x = r + 1;
//             int diff = x - get(l);
//             if (diff == 0) continue;
//             update(1, 0, n - 1, l, l, {diff});
//         } else if (type == 2) {
//             // 把[l,r]区间的数加1
//             update(1, 0, n - 1, l, r, {1});
//         } else if (type == 3) {
//             // 把[l,r]区间的序列颠倒顺序
//             flip(l, r);
//         } else if (type == 4) {
//             // 查询[l,r]区间是否存在三个或以上相同数
//             SegTree::Node res = query(1, 0, n - 1, l, r);
//             if (res.cnt_0 >= 3 || res.cnt_1 >= 3 || (r - l + 1) - res.cnt_0 - res.cnt_1 >= 3) {
//                 cout << "yes" << endl;
//             } else {
//                 cout << "no" << endl;
//             }
//         }
//     }
//     return 0;
// }
// // 0 0 2 0 1 2 1 1 0 1
// // 0 0 2 0 1 2 2 0 0 1
// // 0 1
// // 5 1
// // 3 1