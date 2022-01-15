#include <iostream>

int main() {
    int n;
    scanf("%d", &n);

    int prev, curr;
    scanf("%d", &prev);
    for (int i = 1; i < n; ++i) {
        scanf("%d", &curr);
        if (prev >= curr) {
            printf("%d", prev);
            return 0;
        }
        prev = curr;
    }
    printf("%d", prev);

    return 0;
}