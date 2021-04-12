#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        int answer = 0;
        for (int i = 0; i < n; ++i) {
            int type;
            scanf("%d", &type);

            if (type != 2) {
                answer++;
            }
        }

        printf("%d\n", answer);
    }
}