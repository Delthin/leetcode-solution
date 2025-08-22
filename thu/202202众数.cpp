// ios_base::sync_with_stdio(false);
// cin.tie(nullptr);
// endl -> "\n" 加速
// 维护众数，每次改变都删除插入到set
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
    // 如果需要读写字符串，可以添加以下函数
    inline void read_str(char* s) {
        char c = Getchar();
        while (c <= ' ') { // 跳过前导空白字符
            c = Getchar();
        }
        while (c > ' ') {
            *s++ = c;
            c = Getchar();
        }
        *s = '\0';
    }
    inline void write_str(const char* s) {
        while (*s) {
            Putchar(*s++);
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

struct Block {
    int x;
    int c;
};

vector<unordered_map<int, ll>> cnts;
vector<vector<Block>> blocks;

// 用{-cnts[i][x], x}方便排序
vector<set<pair<ll, int>>> candidates;

void update(int i, int k, int x) {
    if (cnts[i].count(x)) {
        candidates[i].erase({-cnts[i][x], x});
    }
    cnts[i][x] += k;
    if (cnts[i][x] == 0) {
        cnts[i].erase(x);
    } else {
        candidates[i].insert({-cnts[i][x], x});
    }
}

void insert(int i, int k, int x) {

    blocks[i].push_back({x, k});
    update(i, k, x);
}

void remove(int i, int k) {
    auto& vec = blocks[i];
    while (k > 0 && !vec.empty()) {
        Block& b = vec.back();
        int t = min(k, b.c);
        update(i, -t, b.x);
        b.c -= t;
        k -= t;
        if (b.c == 0) {
            vec.pop_back();
        }
    }
}

void query(int i) {
    ll res = -1;
    if (!candidates[i].empty()) {
        res = candidates[i].begin()->second;
    }
    FastIO::write(res);
    FastIO::Putchar('\n');
}

void solve1() {
    int n, q;
    FastIO::read(n);
    FastIO::read(q);
    cnts.resize(n);
    blocks.resize(n);
    candidates.resize(n);
    while (q--) {
        int op, i;
        FastIO::read(op);
        FastIO::read(i);
        if (op == 1) {
            int k, x;
            FastIO::read(k);
            FastIO::read(x);
            insert(i, k, x);
        } else if (op == 2) {
            int k;
            FastIO::read(k);
            remove(i, k);
        } else {
            query(i);
        }
    }
}

int main() {
    solve1();
    return 0;
}