#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    Long n;
    scanf("%lld", &n);

    std::vector<std::vector<Long>> answers(n);

    answers[0] = {1};
    for (int i = 1; i < n; ++i) {
        answers[i].resize(i+1);
        answers[i].front() = answers[i].back() = 1;
        for (int j = 1; j < i; ++j) {
            answers[i][j] = answers[i-1][j-1] + answers[i-1][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (Long v : answers[i]) {
            printf("%lld ", v);
        }
        printf("\n");
    }

    return 0;
}