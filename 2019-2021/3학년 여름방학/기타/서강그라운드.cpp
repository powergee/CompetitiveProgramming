#include <iostream>
#include <algorithm>

int n, m, r;
int score[101];
int dist[101][101];

int main() {
    scanf("%d %d %d", &n, &m, &r);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", score+i);
        for (int j = 1; j <= n; ++j) {
            dist[i][j] = 1e9;
        }
        dist[i][i] = 0;
    }

    for (int i = 0; i < r; ++i) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        dist[a][b] = std::min(dist[a][b], l);
        dist[b][a] = std::min(dist[b][a], l);
    }

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dist[i][j] = std::min(dist[i][k] + dist[k][j], dist[i][j]);
            }
        }
    }

    int answer = -1;
    for (int i = 1; i <= n; ++i) {
        int curr = 0;
        for (int j = 1; j <= n; ++j) {
            if (dist[i][j] <= m) {
                curr += score[j];
            }
        }
        answer = std::max(answer, curr);
    }

    printf("%d", answer);

    return 0;
}