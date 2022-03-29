#include <iostream>
#include <string>

int main() {
    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::string goal, result;
        std::cin >> goal >> result;

        bool possible = true;
        int j = 0, passed = 0;
        for (int i = 0; i < goal.size(); ++i) {
            while (j < result.size() && result[j] != goal[i]) {
                ++j;
                ++passed;
            }

            if (j < result.size()) {
                ++j;
            } else {
                possible = false;
                break;
            }
        }

        std::cout << "Case #" << t << ": ";
        if (possible) {
            std::cout << passed + (int(result.size()) - j) << "\n";
        } else {
            std::cout << "IMPOSSIBLE\n";
        }
    }

    return 0;
}