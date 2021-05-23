#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>

// 결과 LIS가 필요 없다면 result에 null.
template<typename T>
int getLIS(std::vector<T>& arr, std::vector<T>* result, T maxVal) {
    std::vector<T> lis(arr.size(), maxVal);
    std::vector<int> pos(arr.size());

    int length = 0;
    for (int i = 0; i < arr.size(); ++i) {
        auto found = std::lower_bound(lis.begin(), lis.end(), arr[i]);
        *found = arr[i];
        pos[i] = found - lis.begin();
        length = std::max(length, pos[i]+1);
    }

    if (result) {
        std::stack<T> s;
        int target = length-1;
        for (int i = arr.size()-1; i >= 0; --i) {
            if (target == pos[i]) {
                --target;
                s.push(arr[i]);
            }
        }

        while (!s.empty()) {
            result->push_back(s.top());
            s.pop();
        }
    }

    return length;
}

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::pair<int, int>> cables;
    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        cables.emplace_back(a, b);
    }

    std::sort(cables.begin(), cables.end());
    std::vector<std::pair<int, int>> arr;
    for (int i = 0; i < n; ++i) {
        arr.emplace_back(cables[i].second, cables[i].first);
    }

    std::vector<std::pair<int, int>> lis;
    printf("%d\n", n - getLIS(arr, &lis, {__INT32_MAX__, -1}));

    std::set<int> remaining;
    for (auto p : lis) {
        remaining.insert(p.second);
    }

    for (int i = 0; i < n; ++i) {
        if (remaining.find(cables[i].first) == remaining.end()) {
            printf("%d\n", cables[i].first);
        }
    }

    return 0;
}