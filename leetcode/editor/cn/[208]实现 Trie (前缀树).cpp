/**
Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检
查。 

 请你实现 Trie 类： 

 
 Trie() 初始化前缀树对象。 
 void insert(String word) 向前缀树中插入字符串 word 。 
 boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
 
 boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，
返回 false 。 
 

 

 示例： 

 
输入
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
输出
[null, null, true, false, true, null, true]

解释
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回 True
trie.search("app");     // 返回 False
trie.startsWith("app"); // 返回 True
trie.insert("app");
trie.search("app");     // 返回 True
 

 

 提示： 

 
 1 <= word.length, prefix.length <= 2000 
 word 和 prefix 仅由小写英文字母组成 
 insert、search 和 startsWith 调用次数 总计 不超过 3 * 10⁴ 次 
 

 Related Topics 设计 字典树 哈希表 字符串 👍 1749 👎 0

*/
#include <bits/stdc++.h>

#include <utility>

using namespace std;
  
namespace solution208{
//leetcode submit region begin(Prohibit modification and deletion)
class Trie {
private:
    vector<Trie*> children;
    bool isEnd;
    Trie* findPrefix(string prefix) {
        if (prefix.empty()) {
            return this;
        }
        if (children[prefix[0] - 'a'] == nullptr) {
            return nullptr;
        }
        return children[prefix[0] - 'a']->findPrefix(prefix.substr(1));
    }
public:
    Trie(): children(26), isEnd(false) {
        
    }
    
    void insert(string word) {
        if (word.empty()) {
            isEnd = true;
            return;
        }
        char c = word[0];
        if (children[c - 'a'] == nullptr) {
            children[c - 'a'] = new Trie();
        }
        children[c - 'a']->insert(word.substr(1));
    }
    
    bool search(string word) {
        Trie* node = findPrefix(std::move(word));
        return node != nullptr && node->isEnd;
    }
    
    bool startsWith(string prefix) {
        return findPrefix(std::move(prefix)) != nullptr;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution208;
int main() {
    Trie* obj = new Trie();
    obj->insert("apple");
    bool param_2 = obj->search("apple");
    bool param_3 = obj->startsWith("apple");
    return 0;
}