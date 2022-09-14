#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>

using Long = long long;

template <typename T>
class SegTree {
private:
    int originCount;
    std::vector<T> tree;
    
    void initialize(int index, int start, int end, const std::vector<T>& original) {
        if (start == end) {
            tree[index] = original[start];
        } else {
            int mid = (start + end) / 2;
            initialize(index*2, start, mid, original);
            initialize(index*2+1, mid+1, end, original);
            tree[index] = tree[index*2] + tree[index*2+1];
        }
    }

    T query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            return tree[index];
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            return query(index*2, reqStart, reqEnd, treeStart, treeMed)
                 + query(index*2+1, reqStart, reqEnd, treeMed+1, treeEnd);
        } else {
            return 0;
        }
    }

    void update(T add, int index, int reqPos, int treeStart, int treeEnd) {
        if (treeStart == reqPos && treeEnd == reqPos) {
            tree[index] += add;
        } else if (treeStart <= reqPos && reqPos <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            update(add, index*2, reqPos, treeStart, treeMed);
            update(add, index*2+1, reqPos, treeMed+1, treeEnd);
            tree[index] = tree[index*2] + tree[index*2+1];
        }
    }

public:
    SegTree(int count) {
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
    }

    T query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int pos, T add) {
        update(add, 1, pos, 0, originCount-1);
    }
};

int main() {
    int n;
    scanf("%d", &n);
    std::vector<std::pair<int, int>> pairs(n);

    std::set<int> valSet;
    std::map<int, int> comp;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &pairs[i].first);
        valSet.insert(pairs[i].first);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &pairs[i].second);
        valSet.insert(pairs[i].second);
    }

    int idx = 0;
    for (int val : valSet) {
        comp[val] = idx++;
    }
    for (auto& p : pairs) {
        p.first = comp[p.first];
        p.second = comp[p.second];
    }
    std::sort(pairs.begin(), pairs.end());

    std::vector<std::vector<int>> groups;
    groups.push_back({ pairs[0].second });
    for (int i = 1; i < n; ++i) {
        if (pairs[i-1].first != pairs[i].first) {
            groups.emplace_back();
        }
        groups.back().push_back(pairs[i].second);
    }

    int gSize = groups.size();
    SegTree<int> left(valSet.size()), right(valSet.size());
    for (int s : groups[0]) {
        left.update(s, 1);
    }
    for (int i = 2; i < gSize; ++i) {
        for (int s : groups[i]) {
            right.update(s, 1);
        }
    }

    Long total = 0;
    for (int i = 1; i < gSize-1; ++i) {
        for (int s : groups[i]) {
            total += Long(left.query(0, s-1)) * right.query(s+1, valSet.size()-1);
        }

        for (int s : groups[i]) {
            left.update(s, 1);
        }
        for (int s : groups[i+1]) {
            right.update(s, -1);
        }
    }

    printf("%lld", total);

    return 0;
}