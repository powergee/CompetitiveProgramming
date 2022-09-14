#include <iostream>

int main() {
    int scores[18];
    int sum[18];

    for (int i = 0; i < 9; ++i) {
        scanf("%d", scores+i*2);
    }
    for (int i = 0; i < 9; ++i) {
        scanf("%d", scores+i*2+1);
        scores[i*2+1] = -scores[i*2+1];
    }
    
    sum[0] = scores[0];
    for (int i = 1; i < 18; ++i) {
        sum[i] = sum[i-1] + scores[i];
    }

    bool yes = false;
    for (int i = 0; i < 18; ++i) {
        if (sum[i] > 0) {
            yes = true;
        }
    }

    printf(yes ? "Yes" : "No");

    return 0;
}