#include <iostream>

int main() {
    int n;
    std::cin >> n;

    long long answer = 1;
    for (int i = 0; i < n; ++i) {
        long long v;
        std::cin >> v;
        answer *= v;
    }

    std::cout << answer;

    return 0;
}