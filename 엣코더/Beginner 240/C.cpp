#include <iostream>
#include <vector>

int main() {
    int n, x;
    scanf("%d %d", &n, &x);

    std::vector<std::vector<bool>> possible(n+1, std::vector<bool>(x+1, false));
    possible[0][0] = true;
    for (int i = 1; i <= n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        for (int j = x; j >= 0; --j) {
            if (j+a <= x && possible[i-1][j]) {
                possible[i][j+a] = true;
            }
            if (j+b <= x && possible[i-1][j]) {
                possible[i][j+b] = true;
            }
        }
    }

    if (possible[n][x]) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}