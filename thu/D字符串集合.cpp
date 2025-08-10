
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct TrieNode {
    TrieNode* children[26]{};
    ll count; // 以此节点结尾的单词数量
    ll sub_count; // 以此节点为前缀的单词数量
    TrieNode() {
        memset(children, 0, sizeof(children));
        count = 0;
        sub_count = 0;
    }
};

TrieNode root;

void insert(const string& word) {
    TrieNode* p = &root;
    for (char ch : word) {
        int c = ch - 'a'; // 可修改为其他字符集
        if (p->children[c] == nullptr) {
            p->children[c] = new TrieNode();
        }
        p = p->children[c];
        p->sub_count++;
    }
    p->count++;
}

ll query(const string& word) {
    TrieNode* p = &root;
    for (char ch : word) {
        int c = ch - 'a'; // 可修改为其他字符集
        if (p->children[c] == nullptr) {
            return 0;
        }
        p = p->children[c];
    }
    return p->count;
}

ll count_le(const string& word) {
    // 统计字典序小于等于word的单词数量
    TrieNode* p = &root;
    ll ans = 0;
    for (char ch : word) {
        int c = ch - 'a'; // 可修改为其他字符集
        for (int i = 0; i < c; i++) {
            if (p->children[i] != nullptr) {
                ans += p->children[i]->sub_count;
            }
        }
        if (p->children[c] == nullptr) {
            return ans;
        }
        ans += p->children[c]->count;
        p = p->children[c];
    }
    return ans;
}

void solve1() {
    string op;
    // map<string, ll, decltype(cmp)> cnt(cmp);
    cin >> op;
    if (op == "ADD") {
        string ori_s;
        cin >>ori_s;
        int len;
        cin >> len;
        for (int i = 0; i < ori_s.size() - len + 1; i++) {
            string s = ori_s.substr(i, len);
            insert(s);
        }
    } else if (op == "QUERY") {
        string s1, s2;
        cin >> s1 >> s2;
        ll ans = count_le(s2) - (count_le(s1) - query(s1));
        cout << ans << endl;
    }
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        solve1();
    }
    return 0;
}