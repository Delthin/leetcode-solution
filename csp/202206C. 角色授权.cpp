#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Character {
public:
    string name;
    unordered_set<string> ops;
    unordered_set<string> res_types;
    unordered_set<string> res_names;
    bool check(const string& op, const string& res_type, const string& res_name) const {
        if (!ops.count("*") && !ops.count(op)) return false;
        if (!res_types.count("*") && !res_types.count(res_type)) return false;
        if (!res_names.empty() && !res_names.count(res_name)) return false;
        return true;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;
    unordered_map<string, Character*> characters;
    unordered_map<string, unordered_set<Character*>> user2c;
    unordered_map<string, unordered_set<Character*>> group2c;
    while (n--) {
        Character* c = new Character;
        string name;
        cin >> name;
        c->name = name;
        int nv;
        cin >> nv;
        while (nv--) {
            string op;
            cin >> op;
            c->ops.insert(op);
        }
        int no;
        cin >> no;
        while (no--) {
            string res_type;
            cin >> res_type;
            c->res_types.insert(res_type);
        }
        int nn;
        cin >> nn;
        while (nn--) {
            string res_name;
            cin >> res_name;
            c->res_names.insert(res_name);
        }
        characters[name] = c;
    }
    while (m--) {
        string name;
        cin >> name;
        Character* c = characters[name];
        int ns;
        cin >> ns;
        while (ns > 0) {
            string type;
            string name_;
            cin >> type >> name_;
            if (type == "u") {
                user2c[name_].insert(c);
            } else {
                group2c[name_].insert(c);
            }
            ns -= 2;
        }
    }
    while (q--) {
        string user_name;
        cin >> user_name;
        int ng;
        cin >> ng;
        unordered_set<Character*> cs;
        if (user2c.count(user_name)) {
            for (const auto&c :user2c[user_name]) {
                cs.insert(c);
            }
        }
        while (ng--) {
            string group_name;
            cin >> group_name;
            if (group2c.count(group_name)) {
                for (const auto&c :group2c[group_name]) {
                    cs.insert(c);
                }
            }
        }
        string op, res_type, res_name;
        cin >> op >> res_type >> res_name;
        int can = 0;
        for (const auto&c :cs) {
            if (c->check(op, res_type, res_name)) {
                can = 1;
                break;
            }
        }
        cout << can << "\n";
    }
    return 0;
}