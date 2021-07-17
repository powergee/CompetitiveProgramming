#include <iostream>

char str[100001];

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", str);

    for (int i = 0; i < n; ++i) {
        if (str[i] == '1') {
            if (i % 2 == 0) {
                printf("Takahashi");
            } else {
                printf("Aoki");
            }
            break;
        }
    }

    return 0;
}