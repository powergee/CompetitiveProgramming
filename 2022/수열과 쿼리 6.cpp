#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;
    const int SQRT = int(std::sqrt(n))+1;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int q;
    std::cin >> q;
    using Query = std::tuple<int, int, int>;
    std::vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        queries[i] = { l-1, r-1, i };
    }

    std::sort(queries.begin(), queries.end(), [=](const Query& q1, const Query& q2) {
        auto [l1, r1, i1] = q1;
        auto [l2, r2, i2] = q2;
        int g1 = r1 / SQRT;
        int g2 = r2 / SQRT;
        if (g1 != g2) {
            return g1 < g2;
        }
        return l1 < l2;
    });

    std::vector<int> answer(q);
    std::pair<int, int> curr = { 0, 0 };
    std::vector<int> countPerValue(*std::max_element(arr.begin(), arr.end())+1, 0);
    std::vector<int> countCount(n+1, 0);
    countPerValue[arr[0]]++;
    countCount[1]++;
    countCount[0] += n-1;
    int maxCountCount = 1;    
    
    for (auto [l, r, qi] : queries) {
        while (curr.second < r) {
            curr.second++;
            int prevCount = countPerValue[arr[curr.second]]++;
            countCount[prevCount]--;
            countCount[prevCount+1]++;
            maxCountCount = std::max(maxCountCount, prevCount+1);
        }
        while (l < curr.first) {
            curr.first--;
            int prevCount = countPerValue[arr[curr.first]]++;
            countCount[prevCount]--;
            countCount[prevCount+1]++;
            maxCountCount = std::max(maxCountCount, prevCount+1);
        }
        while (r < curr.second) {
            int prevCount = countPerValue[arr[curr.second]]--;
            countCount[prevCount]--;
            countCount[prevCount-1]++;
            if (countCount[maxCountCount] == 0) {
                maxCountCount--;
            }
            curr.second--;
        }
        while (curr.first < l) {
            int prevCount = countPerValue[arr[curr.first]]--;
            countCount[prevCount]--;
            countCount[prevCount-1]++;
            if (countCount[maxCountCount] == 0) {
                maxCountCount--;
            }
            curr.first++;
        }
        answer[qi] = maxCountCount;
    }

    for (int i = 0; i < q; ++i) {
        std::cout << answer[i] << "\n";
    }

    return 0;
}