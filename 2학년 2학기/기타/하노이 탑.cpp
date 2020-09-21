#include <iostream>

void printHanoi(int n, int left, int mid, int right) {
    if (n == 1) {
        printf("%d %d\n", left, right);
    } else {
        printHanoi(n-1, left, right, mid);
        printf("%d %d\n", left, right);
        printHanoi(n-1, mid, left, right);
    }
}

int main() {
    int k;
    scanf("%d", &k);

    printf("%d\n", (1<<k)-1);
    printHanoi(k, 1, 2, 3);

    return 0;
}