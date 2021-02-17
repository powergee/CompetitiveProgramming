#include <iostream>

int dp[16][10][1<<17 - 1] = {0, };
int graph[16][16];
int n;

int getMaxCount(int receiver, int prevPrice, int bitset) {
    int& result = dp[receiver][prevPrice][bitset];
    if (result != 0) {
        return result;
    }
    
    bitset |= 1 << receiver;
    result = bitset;
    
    for (int i = 0; i < n; ++i) {
        if ((bitset & (1 << i)) == 0 && prevPrice <= graph[receiver][i]) {
            int current = getMaxCount(i, graph[receiver][i], bitset);
            if (__builtin_popcount(result) < __builtin_popcount(current)) {
                result = current;
            }
        }
    }

    return result;
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        char line[17];
        scanf("%s", line);

        for (int j = 0; j < n; ++j) {
            graph[i][j] = line[j] - '0';
        }
    }

    printf("%d", __builtin_popcount(getMaxCount(0, 0, 0)));

    return 0;
}