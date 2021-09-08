#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        char str[n+2] = {0, };
        int count[n+1] = {0, };
        scanf("%s", str+1);

        for (int i = 1; i <= n; ++i) {
            count[i] = count[i-1] + (str[i] == 'a' ? 1 : 0);
        }

        std::pair<int, int> answer = {-1, -1};
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                if ((count[j]-count[i-1])*2 == j-i+1) {
                    answer = { i, j };
                    goto breakAll;
                }
            }
        } breakAll:

        printf("%d %d\n", answer.first, answer.second);
    }

    return 0;
}