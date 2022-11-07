#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<std::string> cards(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> cards[i];
    }
    std::sort(cards.begin(), cards.end());

    std::string answer(2*n, '9');
    do {
        std::string curr;
        for (auto c : cards) {
            if (curr.empty() || curr.back() != c[0]) {
                curr += c;
            } else {
                curr += c.back();
            }
        }
        curr = std::string(2*n - curr.size(), '0') + curr;
        answer = std::min(answer, curr);
    } while (std::next_permutation(cards.begin(), cards.end()));

    std::cout << answer.substr(answer.find_first_not_of('0', 0));

    return 0;
}