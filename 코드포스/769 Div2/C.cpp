#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a, b;
        scanf("%d %d", &a, &b);

        int answer = INT32_MAX;
        for (int i = a; i <= b; ++i) {
            int count = i-a + (i != b ? 1 + std::abs((i|b) - b) : 0);
            answer = std::min(answer, count);
        }
        for (int i = b; i <= (a|b); ++i) {
            int count = i-b + 1 + std::abs((i|a)-i);
            answer = std::min(answer, count);
        }
        printf("%d\n", answer);
    }

    return 0;
}