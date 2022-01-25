#include <iostream>

int main() {
    int n;
    scanf("%d", &n);

    int odd = 0, even = 0;
    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        (val % 2 == 0 ? even : odd)++;
    }

    printf("%d\n", odd/2 + even/2);
    
    return 0;
}