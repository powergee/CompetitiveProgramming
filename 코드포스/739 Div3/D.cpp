#include <iostream>
#include <string>
#include <algorithm>

typedef long long Long;

Long findMinMoves(Long from, Long to) {
    std::string fStr = std::to_string(from);
    std::string tStr = std::to_string(to);

    Long j = 0;
    for (Long i = 0; i < fStr.size(); ++i) {
        if (j < tStr.size() && fStr[i] == tStr[j]) {
            ++j;
        }
    }

    return fStr.size() + tStr.size() - j*2;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        Long n;
        std::cin >> n;

        Long answer = __INT64_MAX__;
        for (Long power = 1; power < (1LL<<62); power <<= 1) {
            answer = std::min(answer, findMinMoves(n, power));
        }

        std::cout << answer << "\n";
    }

    return 0;
}