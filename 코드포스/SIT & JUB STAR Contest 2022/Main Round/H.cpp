#include <iostream>
#include <functional>
#include <vector>
#include <cmath>

using Long = long long;

template <typename T>
class SegTree {
private:
    int originCount;
    std::vector<T> tree;
    std::function<T(T, T)> reduce;
    
    void initialize(int index, int start, int end, const std::vector<T>& original) {
        if (start == end) {
            tree[index] = original[start];
        } else {
            int mid = (start + end) / 2;
            initialize(index*2, start, mid, original);
            initialize(index*2+1, mid+1, end, original);
            tree[index] = reduce(tree[index*2], tree[index*2+1]);
        }
    }

    T query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        reqStart = std::max(reqStart, treeStart);
        reqEnd = std::min(reqEnd, treeEnd);
        if (reqStart == treeStart && treeEnd == reqEnd) {
            return tree[index];
        }

        int treeMid = (treeStart+treeEnd)/2;
        bool left = !(treeMid < reqStart);
        bool right = !(reqEnd <= treeMid);

        if (left && right) {
            return reduce(query(index*2, reqStart, reqEnd, treeStart, treeMid),
                          query(index*2+1, reqStart, reqEnd, treeMid+1, treeEnd));
        } else if (left) {
            return query(index*2, reqStart, reqEnd, treeStart, treeMid);
        } else {
            return query(index*2+1, reqStart, reqEnd, treeMid+1, treeEnd);
        }
    }

    void update(T add, int index, int reqPos, int treeStart, int treeEnd) {
        if (treeStart == reqPos && treeEnd == reqPos) {
            tree[index] = reduce(tree[index], add);
        } else if (treeStart <= reqPos && reqPos <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            update(add, index*2, reqPos, treeStart, treeMed);
            update(add, index*2+1, reqPos, treeMed+1, treeEnd);
            tree[index] = reduce(tree[index*2], tree[index*2+1]);
        }
    }

    int findLowerBound(T sum, int index, int treeStart, int treeEnd) {
        int treeMid = (treeStart+treeEnd) / 2;
        if (treeStart == treeEnd) {
            return treeStart;
        } else if (tree[index*2] < sum) {
            return findLowerBound({sum.first-tree[index*2].first, sum.second-tree[index*2].second}, index*2+1, treeMid+1, treeEnd);
        } else {
            return findLowerBound(sum, index*2, treeStart, treeMid);
        }
    }

public:
    SegTree(int count, std::function<T(T, T)> reduce) : reduce(reduce) {
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
    }

    SegTree(const std::vector<T>& original, std::function<T(T, T)> reduce) : SegTree(original.size(), reduce) {
        initialize(1, 0, originCount-1, original);
    }

    T query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int pos, T add) {
        update(add, 1, pos, 0, originCount-1);
    }

    int findLowerBound(T sum) {
        return findLowerBound(sum, 1, 0, originCount-1);
    }
};

struct Passenger {
    int index, standPoint, pointBenefit, enter, leave;
};

int main() {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);

    std::vector<Passenger> pass(n);
    std::vector<std::vector<Passenger*>> in(p+1), out(p+1);
    SegTree<std::pair<int, Long>> countSumTree(2000001, [](std::pair<int, Long> p1, std::pair<int, Long> p2) -> std::pair<int, Long> { 
        return { p1.first+p2.first, p1.second+p2.second };
    });

    for (int i = 0; i < n; ++i) {
        int a, b, l, r;
        scanf("%d %d %d %d", &a, &b, &l, &r);
        pass[i] = { i, b, a-b, l, r };
        in[l].push_back(&pass[i]);
        out[r].push_back(&pass[i]);
    }

    int currSize = 0;
    Long answer = 0, base = 0;
    for (int t = 1; t <= p; ++t) {
        for (Passenger* p : out[t]) {
            base -= p->standPoint;
            int pos = -p->pointBenefit+2000000;
            if (pos < 2000001) {
                countSumTree.update(pos, {-1, -p->pointBenefit});
            }
            --currSize;
        }
        for (Passenger* p : in[t]) {
            base += p->standPoint;
            int pos = -p->pointBenefit+2000000;
            if (pos < 2000001) {
                countSumTree.update(pos, {1, p->pointBenefit});
            }
            ++currSize;
        }

        auto positiveBenefit = countSumTree.query(0, 2000000);
        if (positiveBenefit.first <= m) {
            answer += base + positiveBenefit.second;
        } else {
            int pos = countSumTree.findLowerBound({m, 0});
            auto bucket = countSumTree.query(0, pos);
            auto bound = countSumTree.query(pos, pos);
            Long sitBenefit = bucket.second - (bucket.first-m)*(bound.second/bound.first);
            answer += base + sitBenefit;
        }
    }

    printf("%lld", answer);

    return 0;
}