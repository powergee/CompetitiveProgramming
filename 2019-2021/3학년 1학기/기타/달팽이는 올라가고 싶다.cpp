#include <iostream>
#include <cmath>

int main() {
    int a, b, v;
    scanf("%d %d %d", &a, &b, &v);

    // x -> (a-b)(x-1) + a >= v
    // x >= (v-b) / (a-b)
    printf("%d", (v-b)/(a-b) + ((v-b)%(a-b) ? 1 : 0));
    return 0;
}