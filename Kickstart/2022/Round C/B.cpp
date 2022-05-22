#include <iostream>
#include <string>
#include <vector>

typedef long long Long;

void solve() {
    Long n, x, y;
    std::cin >> n >> x >> y;

    Long num = x*n*(n+1);
    Long den = 2*(x+y);
    if (num % den != 0) {
        std::cout << "IMPOSSIBLE\n";
        return;
    }

    Long need = num / den;
    std::vector<Long> answer;
    for (Long element = n; element >= 1; --element) {
        if (element <= need) {
            answer.push_back(element);
            need -= element;
        }
    }

    if (need) {
        std::cout << "IMPOSSIBLE\n";
        return;
    }

    std::cout << "POSSIBLE\n";
    std::cout << answer.size() << "\n";
    for (Long ans : answer) {
        std::cout << ans << " ";
    }
    std::cout << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}