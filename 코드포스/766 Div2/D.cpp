#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

const int MAX_VAL = 1e6;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<bool> exists(MAX_VAL+1, false);
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        exists[val] = true;
    }

    for (int i = MAX_VAL; i >= 1; --i) {
        if (exists[i]) {
            continue;
        }

        int first = -1;
        for (int j = i*2; j <= MAX_VAL; j += i) {
            if (exists[j]) {
                if (first == -1) {
                    first = j;
                } else if (std::gcd(j, first) == i) {
                    exists[i] = true;
                    ++answer;
                    break;
                }
            }
        }
    }

    printf("%d", answer);
    
    return 0;
}