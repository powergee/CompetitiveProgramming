#include <iostream>
#include <vector>

int main() {
    std::vector<int> fibo = { 0, 1 };
    for (int i = 2; fibo.back() < 1000000000; ++i) {
        fibo.push_back(fibo[i-2] + fibo[i-1]);
    }
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> answer;
        while (n > 0) {
            auto lower = std::lower_bound(fibo.begin(), fibo.end(), n);
            if (*lower > n) {
                lower = std::prev(lower);
            }
            answer.push_back(*lower);
            n -= *lower;
        }

        for (auto it = answer.rbegin(); it != answer.rend(); ++it) {
            printf("%d ", *it);
        }
        printf("\n");
    }

    return 0;
}