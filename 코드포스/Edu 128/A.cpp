#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int l1, r1, l2, r2;
        scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
        
        int answer = -1;
        for (int i = 0; i <= 50; ++i) {
            if (l1 <= i && i <= r1 && l2 <= i && i <= r2) {
                answer = i;
                break;
            }
        }

        if (answer == -1) {
            answer = l1+l2;
        }
        printf("%d\n", answer);
    }

    return 0;
}