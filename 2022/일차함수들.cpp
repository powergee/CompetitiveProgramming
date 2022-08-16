#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    Long answer = 0;
    std::vector<std::pair<Long, Long>> funcs(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> funcs[i].first >> funcs[i].second;
        answer += funcs[i].second;
    }

    std::sort(funcs.begin(), funcs.end());
    for (int i = 0; i < n; ++i) {
        answer += funcs[i].first * (i+1);
    }

    std::cout << answer;

    return 0;
}