#include <iostream>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> codes(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &codes[i]);
    }

    int bonus = 0;
    for (int i = 0; i < n; ++i) {
        int currSum = 0;
        for (int j = i; j < n; ++j) {
            currSum += codes[j];
            if (100*(j-i+1) < currSum) {
                bonus = std::max(bonus, j-i+1);
            }
        }
    }

    printf("%d", bonus);

    return 0;
}