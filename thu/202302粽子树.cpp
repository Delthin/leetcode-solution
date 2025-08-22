#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace FastIO {
    // 缓冲区大小，可以根据题目内存限制调整，一般 1MB (1 << 20) 或 2MB (1 << 21) 效果很好
    const int BUF_SIZE = 1 << 20;
    // 输入缓冲区
    char in_buf[BUF_SIZE], *in_S, *in_T;
    // 输出缓冲区
    char out_buf[BUF_SIZE], *out_O = out_buf;
    // 从标准输入读取一个字符，如果缓冲区用完则重新填充
    inline char Getchar() {
        if (in_S == in_T) {
            in_T = (in_S = in_buf) + fread(in_buf, 1, BUF_SIZE, stdin);
            if (in_S == in_T) {
                return EOF; // 文件结束
            }
        }
        return *in_S++;
    }
    // 模板化的读入函数，支持各种整数类型
    template <class T>
    inline void read(T &x) {
        char c;
        T op = 1; // 符号位，1表示正数，-1表示负数
        x = 0;
        // 跳过所有非数字和非负号的字符
        while ((c = Getchar()) < '0' || c > '9') {
            if (c == '-') {
                op = -1;
            }
            if (c == EOF) return; // 处理文件尾
        }
        // 读取数字部分
        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0'); // 等价于 (x << 1) + (x << 3) + (c - '0')
            c = Getchar();
        }
        x *= op;
    }
    // 向输出缓冲区写入一个字符，如果缓冲区满了则刷出到标准输出
    inline void Putchar(char c) {
        if (out_O == out_buf + BUF_SIZE) {
            fwrite(out_buf, 1, BUF_SIZE, stdout);
            out_O = out_buf;
        }
        *out_O++ = c;
    }
    // 模板化的写出函数，支持各种整数类型
    template <class T>
    inline void write(T x) {
        if (x < 0) {
            Putchar('-');
            x = -x;
        }
        if (x == 0) {
            Putchar('0');
            return;
        }
        // 使用一个栈来逆序存储数字的每一位
        static int sta[35]; // 对于 long long 足够大
        int top = 0;
        while (x) {
            sta[top++] = x % 10;
            x /= 10;
        }
        // 从栈顶开始输出
        while (top) {
            Putchar(sta[--top] + '0');
        }
    }
    // 定义一个结构体，利用其析构函数在程序结束时自动刷新缓冲区
    struct Flusher {
        ~Flusher() {
            if (out_O != out_buf) {
                fwrite(out_buf, 1, out_O - out_buf, stdout);
            }
        }
    };
    // 在main函数开始前，这个全局对象会被构造，程序结束时会被析构
    static Flusher flusher;
}

const int N = 1e6 + 10;
vector<vector<int>> adj;
int a[N];
int ans[N];
int cnt[N];
int now = 0;

void dfs(int u, int p) {
    if (cnt[a[u]] == 0) {
        now++;
    }
    cnt[a[u]]++;
    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        dfs(v, u);
    }
    ans[u] = now;
    cnt[a[u]]--;
    if (cnt[a[u]] == 0) {
        now--;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    FastIO::read(n);
    adj.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        int u, v;
        FastIO::read(u);
        FastIO::read(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> vals;
    for (int i = 1; i <= n; i++) {
        FastIO::read(a[i]);
        vals.push_back(a[i]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
    }
    dfs(n, 0);
    for (int i = 1; i <= n; i++) {
        FastIO::write(ans[i]);
        FastIO::Putchar(" \n"[i == n]);
    }
    return 0;
}
