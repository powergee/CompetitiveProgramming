#include <iostream>
#include <algorithm>

typedef long long Long;

int main() {
    Long a, b;
    std::cin >> a >> b;

    Long answer = -1;

    for (Long i = 1; i <= b; ++i) {
        Long c1 = (b / i) * i;
        Long c2 = c1 - i;

        if (a <= c1 && c1 <= b && a <= c2 && c2 <= b) {
            answer = i;
        }
    }

    std::cout << answer;
}