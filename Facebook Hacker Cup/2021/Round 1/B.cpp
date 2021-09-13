#include <iostream>
#include <vector>

int map[50][50];

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);
        int n, m, a, b;
        scanf("%d %d %d %d", &n, &m, &a, &b);
        
        if (a < n+m-1 || b < n+m-1) {
            printf("Impossible\n");
        } else {
            printf("Possible\n");
            std::fill(&map[0][0], &map[0][0] + sizeof(map) / sizeof(int), 1);
            map[0][0] = a-(n+m-1)+1;
            map[0][m-1] = b-(n+m-1)+1;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    printf("%d ", map[i][j]);
                }
                printf("\n");
            }
        }
    }
    
    return 0;
}