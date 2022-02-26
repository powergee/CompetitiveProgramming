#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

int main() {
    int h, w, n;
    scanf("%d %d %d", &h, &w, &n);

    std::pair<int, int> start, end;
    scanf("%d %d", &start.first, &start.second);
    scanf("%d %d", &end.first, &end.second);

    std::map<int, std::vector<int>> row, col;
    for (int i = 0; i < n; ++i) {
        int r, c;
        scanf("%d %d", &r, &c);
        row[r].push_back(c);
        col[c].push_back(r);
    }

    for (auto& r : row) {
        std::sort(r.second.begin(), r.second.end());
    }
    for (auto& c : col) {
        std::sort(c.second.begin(), c.second.end());
    }

    std::queue<std::tuple<int, int, int>> q;
    q.emplace(start.first, start.second, 0);
    std::map<std::pair<int, int>, bool> visited;
    visited[{start.first, start.second}] = true;
    int minTime = -1;

    while (!q.empty()) {
        auto [r, c, t] = q.front();
        q.pop();

        if (row.find(r) == row.end()) {
            row[r] = std::vector<int> ();
        }
        if (col.find(c) == col.end()) {
            col[c] = std::vector<int> ();
        }

        if (end.first == r && end.second == c) {
            minTime = t;
            break;
        }

        // DOWN
        auto found = std::lower_bound(col[c].begin(), col[c].end(), r);
        if (found != col[c].end()) {
            std::pair<int, int> next = { *found-1, c };
            if (!visited[next]) {
                visited[next] = true;
                q.emplace(next.first, next.second, t+1);
            }
        }

        // UP
        if (found != col[c].begin() && col[c].size() > 0) {
            found = std::prev(found);
            std::pair<int, int> next = { *found+1, c };
            if (!visited[next]) {
                visited[next] = true;
                q.emplace(next.first, next.second, t+1);
            }
        }

        // RIGHT
        found = std::lower_bound(row[r].begin(), row[r].end(), c);
        if (found != row[r].end()) {
            std::pair<int, int> next = { r, *found-1 };
            if (!visited[next]) {
                visited[next] = true;
                q.emplace(next.first, next.second, t+1);
            }
        }

        // LEFT
        if (found != row[r].begin() && row[r].size() > 0) {
            found = std::prev(found);
            std::pair<int, int> next = { r, *found+1 };
            if (!visited[next]) {
                visited[next] = true;
                q.emplace(next.first, next.second, t+1);
            }
        }
    }

    printf("%d", minTime);

    return 0;
}