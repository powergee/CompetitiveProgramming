#include <iostream>
#include <cstring>

typedef long long Long;

char str[200001];
int dp[200000][2];
int n;

int getMaxLength(int start, int here) {
    if (start == n) {
        return 0;
    }

    int& result = dp[start][here];
    if (result != -1) {
        return result;
    }

    if (str[start] != char('0' + here) && str[start] != '?') {
        return result = 0;
    }

    return result = 1 + getMaxLength(start+1, here == 0 ? 1 : 0);
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%s", str);
        n = strlen(str);
        for (int i = 0; i < n; ++i) {
            dp[i][0] = dp[i][1] = -1;
        }

        Long answer = 0;
        for (int i = 0; i < n; ++i) {
            Long length = std::max(getMaxLength(i, 0), getMaxLength(i, 1));
            answer += length;
        }

        printf("%lld\n", answer);
    }

    return 0;
}