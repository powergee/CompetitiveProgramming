#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::vector<std::pair<int, int>> works(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> works[i].first >> works[i].second;
    }

    std::sort(works.begin(), works.end(), [](std::pair<int, int> w1, std::pair<int, int> w2) {
        return w1.second > w2.second;
    });

    long long answer = 0;
    for (int i = 0; i < k; ++i) {
        answer += works[i].first;
    }

    std::sort(works.begin()+k, works.end(), [](std::pair<int, int> w1, std::pair<int, int> w2) {
        return w1.first > w2.first;
    });

    for (int i = k; i < k+m; ++i) {
        answer += works[i].first;
    }

    std::cout << answer;

    return 0;
}