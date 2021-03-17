#include <iostream>

struct Triplet {
    int a, b, c;

    void print() {
        printf("%d %d %d\n", a, b, c);
    }
};

Triplet getAnswer(int n) {
    if (n == 4) {
        return {2, 1, 1};
    } else if (n % 2 == 1) {
        return {(n-1)/2, (n-1)/2, 1};
    } else {
        Triplet sub = getAnswer(n/2);
        return {sub.a*2, sub.b*2, sub.c*2};
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);

        getAnswer(n).print();
    }

    return 0;
}