#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        char str[n+1], answer[n+1];
        scanf("%s", str);
        answer[n] = 0;

        for (int i = 0; i < n; ++i) {
            if (str[i] == 'L' || str[i] == 'R') {
                answer[i] = str[i];
            } else if (str[i] == 'U') {
                answer[i] = 'D';
            } else {
                answer[i] = 'U';
            }
        }

        printf("%s\n", answer);
    }

    return 0;
}