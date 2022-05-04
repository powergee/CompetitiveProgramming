#include <iostream>

int count[100001];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d.%d", &a, &b);
        int score = a*1000 + b;
        count[score]++;
    }

    int printed = 0;
    for (int i = 0; i < sizeof(count)/sizeof(int); ++i) {
        for (int j = 0; j < count[i] && printed < 7; ++j) {
            printf("%d.%03d\n", i/1000, i%1000);
            ++printed;
        }
        if (printed == 7) {
            break;
        }
    }

    return 0;
}