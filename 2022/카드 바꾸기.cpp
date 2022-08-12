#include <iostream>
#include <vector>
#include <set>
#include <map>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<Long> cards(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> cards[i];
    }

    int answer = INT32_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            Long diff = (cards[j]-cards[i])/(j-i);
            Long first = cards[i] - i*diff;
            int count = 0;
            for (int k = 0; k < n; ++k) {
                if (first+k*diff == cards[k]) {
                    ++count;
                }
            }
            answer = std::min(answer, n-count);
        }
    }
    std::cout << answer;

    return 0;
}