#include <iostream>

int main() {
    long long val;
    scanf("%lld", &val);
    if (INT32_MIN <= val && val <= INT32_MAX) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}