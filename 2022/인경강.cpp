#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> infoLength(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> infoLength[i];
    }

    using Column = std::vector<std::pair<int, int>>;
    std::vector<Column> ranges(m);
    for (int i = 0; i < m; ++i) {
        ranges[i].resize(infoLength[i]/2);
        for (int j = 0; j < infoLength[i]/2; ++j) {
            int l, r;
            std::cin >> l >> r;
            ranges[i][j] = { l, r };
        }
    }

    auto filter = [&](const Column& c1, const Column& c2) {
        Column result;
        for (auto next : c2) {
            bool possible = false;
            for (auto curr : c1) {
                if (!(curr.second < next.first || next.second < curr.first)) {
                    possible = true;
                    break;
                }
            }
            if (possible) {
                result.push_back(next);
            }
        }
        return result;
    };

    Column curr = ranges[0];
    for (int i = 1; i < m; ++i) {
        curr = filter(curr, ranges[i]);
    }

    if (curr.size()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}