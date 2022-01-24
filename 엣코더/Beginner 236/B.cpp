#include <iostream>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> count(n+1, 0);
    for (int i = 0; i < 4*n-1; ++i) {
        int val;
        scanf("%d", &val);
        count[val]++;
    }

    for (int i = 1; i <= n; ++i) {
        if (count[i] == 3) {
            printf("%d", i);
        }
    }

    return 0;
}