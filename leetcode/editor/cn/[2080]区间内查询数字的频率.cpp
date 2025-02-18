//请你设计一个数据结构，它能求出给定子数组内一个给定值的 频率 。 
//
// 子数组中一个值的 频率 指的是这个子数组中这个值的出现次数。 
//
// 请你实现 RangeFreqQuery 类： 
//
// 
// RangeFreqQuery(int[] arr) 用下标从 0 开始的整数数组 arr 构造一个类的实例。 
// int query(int left, int right, int value) 返回子数组 arr[left...right] 中 value 的 频
//率 。 
// 
//
// 一个 子数组 指的是数组中一段连续的元素。arr[left...right] 指的是 nums 中包含下标 left 和 right 在内 的中间一段连续
//元素。 
//
// 
//
// 示例 1： 
//
// 输入：
//["RangeFreqQuery", "query", "query"]
//[[[12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56]], [1, 2, 4], [0, 11, 33]]
//输出：
//[null, 1, 2]
//
//解释：
//RangeFreqQuery rangeFreqQuery = new RangeFreqQuery([12, 33, 4, 56, 22, 2, 34, 
//33, 22, 12, 34, 56]);
//rangeFreqQuery.query(1, 2, 4); // 返回 1 。4 在子数组 [33, 4] 中出现 1 次。
//rangeFreqQuery.query(0, 11, 33); // 返回 2 。33 在整个子数组中出现 2 次。
// 
//
// 
//
// 提示： 
//
// 
// 1 <= arr.length <= 10⁵ 
// 1 <= arr[i], value <= 10⁴ 
// 0 <= left <= right < arr.length 
// 调用 query 不超过 10⁵ 次。 
// 
//
// Related Topics 设计 线段树 数组 哈希表 二分查找 👍 86 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution2080{
//leetcode submit region begin(Prohibit modification and deletion)
class RangeFreqQuery {
private:
    vector<unordered_map<int, int>> tree;
    void build(int node, int left, int right, vector<int>& arr) {
        if (left == right) {
            // if (!tree[node].count(arr[left])) {
            //     tree[node][arr[left]] = 0;
            // };
            tree[node][arr[left]]++;
            return;
        }
        int mid = (left + right) / 2;
        build(node * 2, left, mid, arr);
        build(node * 2 + 1, mid + 1, right, arr);
        for (auto& [key, value]: tree[node * 2]) {
            // if (!tree[node].count(key)) {
            //     tree[node][key] = 0;
            // }
            tree[node][key] += value;
        }
        for (auto& [key, value]: tree[node * 2 + 1]) {
            // if (!tree[node].count(key)) {
            //     tree[node][key] = 0;
            // }
            tree[node][key] += value;
        }
    }
    int recur_query(int node, int left, int right, int value, int ori_left, int ori_right) {
        if (left >= ori_left && right <= ori_right) {
            return tree[node].count(value) ? tree[node][value] : 0;
        }
        int mid = (left + right) / 2;
        int ret = 0;
        if (ori_right > mid) {
            ret += recur_query(node * 2 + 1, mid + 1, right, value, ori_left, ori_right);
        }
        if (ori_left <= mid) {
            ret += recur_query(node * 2, left, mid, value, ori_left, ori_right);
        }
        return ret;
    }
public:
    RangeFreqQuery(vector<int>& arr) {
        int n = arr.size();
        tree.resize((n << 1) + 1);
        build(1, 0, n - 1, arr);
    }
    
    int query(int left, int right, int value) {
        return recur_query(1, left, right, value, left, right);
    }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2080;
int main() {
    vector<int> arr = {1,1,1,2,2};
    auto rangeFreqQuery = new RangeFreqQuery(arr);
    cout << rangeFreqQuery->query(0, 1, 2) << endl;
    return 0;
}