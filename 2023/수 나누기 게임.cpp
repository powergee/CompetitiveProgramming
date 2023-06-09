#include <iostream>
#include <vector>

int main() {
    const int MAX = 1000000;
    const int UND = -2 * MAX;
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<int> player(n);
    std::vector<int> score(MAX + 1, UND);
    for (int i = 0; i < n; ++i) {
        std::cin >> player[i];
        score[player[i]] = 0;
    }

    for (int i = 0; i < n; ++i) {
        if (player[i] == 1) {
            continue;
        }
        std::vector<std::pair<int, int>> prime;
        int curr = player[i];
        for (int div = 2; div * div <= player[i] && curr > 1; ++div) {
            if (curr % div == 0) {
                prime.emplace_back(div, 0);
            }
            while (curr % div == 0) {
                curr /= div;
                prime.back().second += 1;
            }
        }
        if (curr != 1) {
            prime.emplace_back(curr, 1);
        }

        int total = 1;
        for (auto [_, cnt] : prime) {
            total *= cnt + 1;
        }

        for (int j = 0; j < total - 1; ++j) {
            int cand = 1, index = j;
            for (auto [p, cnt] : prime) {
                int curr = index % (cnt + 1);
                index /= (cnt + 1);
                while (curr--) {
                    cand *= p;
                }
            }

            if (score[cand] != UND) {
                score[cand] += 1;
                score[player[i]] -= 1;
            }
        }
    }

    for (int p : player) {
        std::cout << score[p] << " ";
    }
    std::cout << '\n';

    return 0;
}