#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>
#include <map>

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

    void clear() {
        std::fill(leftMax.begin(), leftMax.end(), 0);
        std::fill(rightMax.begin(), rightMax.end(), 0);
        std::fill(overallMax.begin(), overallMax.end(), 0);
        std::fill(sum.begin(), sum.end(), 0);
    }
};

int main() {
    int n[2], w[2];
    std::vector<std::pair<int, int>> p[2];
    std::map<int, int> xMap, yMap;

    for (int i = 0; i < 2; ++i) {
        scanf("%d", n+i);
        p[i].resize(n[i]);
        for (int j = 0; j < n[i]; ++j) {
            int x, y;
            scanf("%d %d", &x, &y);
            p[i][j] = { x, y };
            xMap[x] = 0;
            yMap[y] = 0;
        }
    }
    scanf("%d %d", &w[0], &w[1]);
    w[1] = -w[1];

    int comp = 0;
    for (auto& m : xMap) {
        m.second = comp++;
    }
    comp = 0;
    for (auto& m : yMap) {
        m.second = comp++;
    }
    
    std::vector<std::vector<std::pair<int, int>>> column(xMap.size());
    for (int i = 0; i < 2; ++i) {
        for (auto [x, y] : p[i]) {
            column[xMap[x]].emplace_back(yMap[y], w[i]);
        }
    }

    Long result = INT64_MIN;
    SegTree msTree(yMap.size());
    for (int minX = 0; minX < xMap.size(); ++minX) {
        for (int maxX = minX; maxX < xMap.size(); ++maxX) {
            for (auto [y, w] : column[maxX]) {
                msTree.update(y, w);
            }
            result = std::max(result, msTree.getMaxSubarray());
        }
        msTree.clear();
    }

    printf("%lld\n", result);

    return 0;
}