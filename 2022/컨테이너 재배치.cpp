#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    int total = 0;
    std::vector<int> status(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> status[i];
        total += status[i];
    }

    int answer = 0;
    int lower = total / n;
    int upperCount = total % n;
    int lowerCount = n - upperCount;
    for (int i = 0; i < n; ++i) {
        if (lowerCount && status[i] <= lower) {
            answer += lower - status[i];
            lowerCount--;
        } else if (upperCount && status[i] <= lower+1) {
            answer += lower+1 - status[i];
            upperCount--;
        }
    }

    std::cout << answer;

    return 0;
}