#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <numeric>
#define INF (INT32_MAX/2)

int main() {
    int w, h;
    while (scanf("%d %d", &w, &h), (w != 0 && h != 0)) {
        char map[20][21];
        std::vector<std::pair<int, int>> points(1);
        int dist[11][20][20];
        std::fill(&dist[0][0][0], &dist[0][0][0] + sizeof(dist) / sizeof(int), INT32_MAX/2);

        for (int i = 0; i < h; ++i) {
            scanf("%s", map[i]);
            for (int j = 0; j < w; ++j) {
                if (map[i][j] == 'o') {
                    points[0] = { i, j };
                } else if (map[i][j] == '*') {
                    points.emplace_back(i, j);
                }
            }
        }

        for (int i = 0; i < points.size(); ++i) {
            std::queue<std::pair<int, int>> q;
            q.emplace(points[i]);
            dist[i][points[i].first][points[i].second] = 0;

            while (!q.empty()) {
                auto curr = q.front();
                q.pop();

                const int dr[] { 0, 0, 1, -1 };
                const int dc[] { 1, -1, 0, 0 };
                for (int j = 0; j < 4; ++j) {
                    int nr = dr[j] + curr.first;
                    int nc = dc[j] + curr.second;
                    if (0 <= nr && nr < h && 0 <= nc && nc < w && 
                        dist[i][nr][nc] == INF && map[nr][nc] != 'x') {
                        dist[i][nr][nc] = dist[i][curr.first][curr.second]+1;
                        q.emplace(nr, nc);
                    }
                }
            }
        }

        std::vector<int> indexes(points.size());
        std::iota(indexes.begin(), indexes.end(), 0);
        bool possible = true;
        int answer = INF;
        
        do {
            int currCase = 0;
            for (int i = 0; i < (int)points.size()-1; ++i) {
                int curr = indexes[i];
                int next = indexes[i+1];
                int distBtw = dist[curr][points[next].first][points[next].second];
                if (distBtw == INF) {
                    possible = false;
                    break;
                } else {
                    currCase += distBtw;
                }
            }
            answer = std::min(answer, currCase);
        } while (possible && std::next_permutation(indexes.begin()+1, indexes.end()));

        if (possible) {
            printf("%d\n", answer);
        } else {
            printf("-1\n");
        }
    }

    return 0;
}