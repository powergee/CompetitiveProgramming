#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <set>
#include <cmath>

using Long = long long;

template <typename T>
class SegTree {
private:
    int originCount;
    T globalMin;
    std::vector<T> tree;
    std::vector<T> lazy;
    
    void initialize(int index, int start, int end, const std::vector<T>& original) {
        if (start == end) {
            tree[index] = original[start];
        } else {
            int mid = (start + end) / 2;
            initialize(index*2, start, mid, original);
            initialize(index*2+1, mid+1, end, original);
            tree[index] = std::max(tree[index*2], tree[index*2+1]);
        }
    }

    void propagate(int index, int start, int end) {
        if (lazy[index] != globalMin) {
            tree[index] = std::max(lazy[index], tree[index]);
            if (start < end) {
                lazy[index*2] = std::max(lazy[index], lazy[index*2]);
                lazy[index*2+1] = std::max(lazy[index], lazy[index*2+1]);
            }
            lazy[index] = globalMin;
        }
    }

    T query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        propagate(index, treeStart, treeEnd);

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            return tree[index];
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            return std::max(query(index*2, reqStart, reqEnd, treeStart, treeMed)
                           ,query(index*2+1, reqStart, reqEnd, treeMed+1, treeEnd));
        } else {
            return globalMin;
        }
    }

    void update(T value, int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        propagate(index, treeStart, treeEnd);

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            lazy[index] = value;
            propagate(index, treeStart, treeEnd);
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            update(value, index*2, reqStart, reqEnd, treeStart, treeMed);
            update(value, index*2+1, reqStart, reqEnd, treeMed+1, treeEnd);
            tree[index] = std::max(tree[index*2], tree[index*2+1]);
        }
    }

public:
    SegTree(int count, T min) {
        originCount = count;
        globalMin = min;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize, globalMin);
        lazy.resize(vecSize, globalMin);
    }

    T query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int start, int end, T value) {
        update(value, 1, start, end, 0, originCount-1);
    }
};

std::vector<std::pair<int, int>> rows[300001];
std::set<int> posSet;
std::unordered_map<int, int> posMap;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int idx, s, e;
        scanf("%d %d %d", &idx, &s, &e);
        rows[idx].emplace_back(s, e);
        posSet.insert(s);
        posSet.insert(e);
    }

    int idx = 0;
    for (int val : posSet) {
        posMap[val] = idx++;
    }

    for (int i = 1; i <= n; ++i) {
        for (auto& range : rows[i]) {
            range.first = posMap[range.first];
            range.second = posMap[range.second];
        }
        std::sort(rows[i].begin(), rows[i].end());
    }

    SegTree<std::pair<int, int>> tree((int)posMap.size(), std::make_pair(0, 0));
    std::vector<int> prevMaxRow(n+1);

    for (int i = 1; i <= n; ++i) {
        int prevRight = -1;
        std::pair<int, int> overallMax(0, 0);
        for (auto& range : rows[i]) {
            int left = std::max(prevRight+1, range.first);
            int right = range.second;

            if (left <= right) {
                auto max = tree.query(left, right);
                overallMax = std::max(overallMax, max);
            }
            prevRight = range.second;
        }
        for (auto& range : rows[i]) {
            tree.update(range.first, range.second, {overallMax.first+1, i});
        }
        prevMaxRow[i] = overallMax.second;
    }

    auto answer = tree.query(0, (int)posMap.size()-1);
    printf("%d\n", n - answer.first);

    std::set<int> used;
    for (int r = answer.second; r != 0; r = prevMaxRow[r]) {
        used.insert(r);
    }

    for (int i = 1; i <= n; ++i) {
        if (used.find(i) == used.end()) {
            printf("%d ", i);
        }
    }

    return 0;
}