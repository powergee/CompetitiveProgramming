#include <iostream>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int path[m], cost[n+1][n+1];

    for (int i = 0; i < m; ++i) {
        scanf("%d", path+i);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &cost[i][j]);
        }
    }

    int answer = 0;
    for (int i = 0; i < m-1; ++i) {
        answer += cost[path[i]][path[i+1]];
    }
    printf("%d", answer);

    return 0;
}