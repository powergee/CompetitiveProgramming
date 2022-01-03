#include <iostream>
#include <vector>
#include <string>

char answer[40][41];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                answer[i][j] = '.';
            }
            answer[i][n] = '\0';
        }
        
        bool success = true;
        for (int i = 0; i < k; ++i) {
            if (2*i < n) {
                answer[2*i][2*i] = 'R';
            } else {
                success = false;
                break;
            }
        }

        if (success) {
            for (int i = 0; i < n; ++i) {
                printf("%s\n", answer[i]);
            }
        } else {
            printf("-1\n");
        }
    }

    return 0;
}