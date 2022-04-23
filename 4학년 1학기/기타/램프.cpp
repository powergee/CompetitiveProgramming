#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    int r, c;
    scanf("%d %d", &r, &c);

    std::vector<Long> matrix(r, 0);
    for (int i = 0; i < r; ++i) {
        char line[c+1];
        scanf("%s", line);
        for (int j = 0; j < c; ++j) {
            if (line[j] == '1') {
                matrix[i] += (1LL<<(c-1-j));
            }
        }
    }
    int k;
    scanf("%d", &k);

    int answer = 0;
    for (int i = 0; i < r; ++i) {
        Long turnOn = ((1LL<<c)-1) - matrix[i];
        int pop = __builtin_popcountll(turnOn);
        if (pop <= k && (pop%2) == (k%2)) {
            int currAnswer = 0;
            for (int j = 0; j < r; ++j) {
                if (matrix[i] == matrix[j]) {
                    ++currAnswer;
                }
            }
            answer = std::max(answer, currAnswer);
        }
    }

    printf("%d", answer);

    return 0;
}