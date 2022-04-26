#include <iostream>

int main() {
    char input[100][33] = {0,};
    char answer[33] = {0,};
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%s", input[i]);
    }
    for (int i = 0; i <= 32; ++i) {
        answer[i] = input[0][i];
        for (int j = 0; j < n; ++j) {
            if (answer[i] != input[j][i]) {
                answer[i] = '?';
                break;
            }
        }
    }
    printf("%s", answer);

    return 0;
}