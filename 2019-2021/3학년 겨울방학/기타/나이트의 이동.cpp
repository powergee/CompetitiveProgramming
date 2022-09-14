#include <iostream>
#include <queue>
#include <vector>

typedef std::pair<int, int> Point;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int width;
        scanf("%d", &width);
        Point start, end;
        scanf("%d%d%d%d", &start.first, &start.second, &end.first, &end.second);

        std::vector<std::vector<bool>> visited(width, std::vector<bool>(width, false));
        std::queue<std::pair<Point, int>> q;
        q.emplace(start, 0);
        visited[start.first][start.second] = true;

        while (!q.empty()) {
            auto [pos, dist] = q.front();
            q.pop();

            if (pos == end) {
                printf("%d\n", dist);
                break;
            }

            constexpr Point delta[] = {
                {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}
            };
            for (int i = 0; i < 8; ++i) {
                Point next = {
                    pos.first + delta[i].first,
                    pos.second + delta[i].second
                };
                if (0 <= next.first && next.first < width && 0 <= next.second && next.second < width && !visited[next.first][next.second]) {
                    visited[next.first][next.second] = true;
                    q.emplace(next, dist+1);
                }
            }
        }
    }

    return 0;
}