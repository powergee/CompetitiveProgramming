#include <iostream>

int main() {
    long long val;
    scanf("%lld", &val);

    int k = 0;
    long long curr = 1;
    while (curr <= val) {
        curr *= 2;
        ++k;
    }

    printf("%d", k-1);

    return 0;
}