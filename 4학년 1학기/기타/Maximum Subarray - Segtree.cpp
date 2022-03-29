// For testing MS Segtree.

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>
#include <random>

using Long = long long;

template <typename T>
T max(T t)  {
    return t;
}

template<typename T, typename... Args>
T max(T t, Args... args) {
    return std::max(t, max(args...));
}

class SegTree {
private:
    int originCount;
    std::vector<Long> leftMax, rightMax, overallMax, sum;

    void update(Long add, int index, int reqPos, int treeStart, int treeEnd) {
        if (treeStart == reqPos && treeEnd == reqPos) {
            leftMax[index] += add;
            rightMax[index] += add;
            overallMax[index] += add;
            sum[index] += add;
        } else if (treeStart <= reqPos && reqPos <= treeEnd) {
            int treeMid = (treeStart+treeEnd) / 2;
            update(add, index*2, reqPos, treeStart, treeMid);
            update(add, index*2+1, reqPos, treeMid+1, treeEnd);

            leftMax[index] = max(
                leftMax[index*2],
                sum[index*2] + leftMax[index*2+1]
            );
            rightMax[index] = max(
                rightMax[index*2+1],
                sum[index*2+1] + rightMax[index*2]
            );
            overallMax[index] = max(
                overallMax[index*2],
                overallMax[index*2+1],
                rightMax[index*2] + leftMax[index*2+1]
            );
            sum[index] = sum[index*2] + sum[index*2+1];
        }
    }

public:
    SegTree(int count) {
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        leftMax.resize(vecSize, 0);
        rightMax.resize(vecSize, 0);
        overallMax.resize(vecSize, 0);
        sum.resize(vecSize, 0);
    }

    Long getMaxSubarray() {
        return overallMax[1];
    }

    void update(int pos, Long add) {
        update(add, 1, pos, 0, originCount-1);
    }
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        SegTree tree(n);
        // for robust testing
        std::vector<std::pair<int, int>> inputs(n);
        for (int i = 0; i < n; ++i) {
            int add;
            scanf("%d", &add);
            inputs[i] = { i, add };
        }

        auto rng = std::default_random_engine {};
        std::shuffle(inputs.begin(), inputs.end(), rng);
        for (auto [i, add] : inputs) {
            tree.update(i, add);
        }

        printf("%lld\n", tree.getMaxSubarray());
    }

    return 0;
}