#include <iostream>
#include <vector>

enum Operation {
    DoNothing, Divide2, Divide3, Minus1
};

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> dp(n+1), oper(n+1);
    dp[1] = 0;
    oper[1] = DoNothing;
    dp[2] = dp[3] = 1;
    oper[2] = Minus1;
    oper[3] = Divide3;

    for (int i = 4; i <= n; ++i) {
        dp[i] = dp[i-1]+1;
        oper[i] = Minus1;
        if (i % 3 == 0 && dp[i/3]+1 < dp[i]) {
            dp[i] = dp[i/3]+1;
            oper[i] = Divide3;
        }
        if (i % 2 == 0 && dp[i/2]+1 < dp[i]) {
            dp[i] = dp[i/2]+1;
            oper[i] = Divide2;
        }
    }
    printf("%d\n", dp[n]);
    while (n > 1) {
        printf("%d ", n);
        switch (oper[n])
        {
        case Divide2:
            n /= 2;
            break;
        case Divide3:
            n /= 3;
            break;
        case Minus1:
            n -= 1;
            break;
        }
    }
    printf("1");

    return 0;
}