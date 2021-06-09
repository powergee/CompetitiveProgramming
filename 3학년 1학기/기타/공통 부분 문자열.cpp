#include <iostream>
#include <cstring>
#include <algorithm>

char w1[4002], w2[4002];
int lcs[4001][4001];

int main() {
    scanf("%s%s", w1+1, w2+1);

    int n1 = strlen(w1+1);
    int n2 = strlen(w2+1);

    for (int i = 0; i <= n1; ++i) {
        for (int j = 0; j <= n2; ++j) {
            if (i == 0 || j == 0) {
                lcs[i][j] = 0;
            } else if (w1[i] == w2[j]) {
                lcs[i][j] = lcs[i-1][j-1] + 1;
            } else {
                lcs[i][j] = std::max(lcs[i-1][j], lcs[i][j-1]);
            }
        }
    }

    printf("%d", lcs[n1][n2]);

    return 0;
}