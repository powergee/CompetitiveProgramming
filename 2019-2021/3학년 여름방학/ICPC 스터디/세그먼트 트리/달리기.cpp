#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_map>

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
    SegTree(const std::vector<T>& original) {
        originCount = (int)original.size();
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
        initialize(1, 0, originCount-1, original);
    }

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

void compress(std::vector<int>& arr) {
    std::vector<int> temp = arr;
    std::sort(temp.begin(), temp.end());
    std::unordered_map<int, int> compMap;
    for (int t : temp) {
        if (compMap.find(t) == compMap.end()) {
            compMap[t] = (int)compMap.size();
        }
    }
    for (int& v : arr) {
        v = compMap[v];
    }
}

int main() {
    int n;
    scanf("%d", &n);

    SegTree<int> tree(n);
    std::vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    
    compress(arr);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", tree.query(arr[i]+1, n-1)+1);
        tree.update(arr[i], 1);
    }

    return 0;
}