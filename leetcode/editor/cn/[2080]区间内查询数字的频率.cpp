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
        // 数值为键，出现下标数组为值的哈希表
        unordered_map<int, vector<int>> occurence;

    public:
        RangeFreqQuery(vector<int>& arr) {
            // 顺序遍历数组初始化哈希表
            int n = arr.size();
            for (int i = 0; i < n; ++i){
                occurence[arr[i]].push_back(i);
            }
        }

        int query(int left, int right, int value) {
            // 查找对应的出现下标数组，不存在则为空
            const vector<int>& pos = occurence[value];
            // 两次二分查找计算子数组内出现次数
            auto l = lower_bound(pos.begin(), pos.end(), left);
            auto r = upper_bound(pos.begin(), pos.end(), right);
            return r - l;
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
    vector<int> arr = {12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56};
    auto rangeFreqQuery = new RangeFreqQuery(arr);
    cout << rangeFreqQuery->query(1, 2, 4) << endl;
    cout << rangeFreqQuery->query(0, 11, 33) << endl;
    return 0;
}