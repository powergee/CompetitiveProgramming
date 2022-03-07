#include <iostream>

int main() {
    int n, x;
    scanf("%d %d", &n, &x);

    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        sum += val;
        if (i % 2 == 1) {
            sum -= 1;
        }
    }

    if (sum <= x) {
        printf("Yes");
    } else {
        printf("No");
    }
}