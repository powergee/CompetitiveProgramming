#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <string>
#include <deque>
#include <cassert>

const int dr[4] { -1, -1, +1, +1 };
const int dc[4] { -1, +1, -1, +1 };

struct SearchState {
    int row, col, dir;

    bool isValid(int n) {
        return 0 <= row && row < n && 0 <= col && col < n;
    }
};

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::pair<int, int> start, end;
    std::cin >> n;
    std::cin >> start.first >> start.second;
    std::cin >> end.first >> end.second;

    start.first--; start.second--;
    end.first--; end.second--;

    std::vector<std::string> map(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> map[i];
    }

    std::deque<SearchState> q;
    std::vector<std::vector<std::vector<int>>> dist(n, std::vector<std::vector<int>>(n, std::vector<int>(4, INT32_MAX)));
    for (int i = 0; i < 4; ++i) {
        SearchState state;
        state.row = start.first;
        state.col = start.second;
        state.dir = i;
        q.push_back(state);
        dist[state.row][state.col][state.dir] = 1;
    }

    while (!q.empty()) {
        SearchState state = q.front();
        q.pop_front();

        for (int i = 0; i < 4; ++i) {
            SearchState next = SearchState(state);
            next.dir = i;
            next.row += dr[i];
            next.col += dc[i];

            int currCost = state.dir == next.dir ? 0 : 1;
            int update = dist[state.row][state.col][state.dir]+currCost;
            if (next.isValid(n) && map[next.row][next.col] == '.' && update < dist[next.row][next.col][next.dir]) {
                dist[next.row][next.col][next.dir] = update;
                if (currCost == 0) {
                    q.push_front(next);
                } else {
                    q.push_back(next);
                }
            }
        }
    }
    int answer = *std::min_element(dist[end.first][end.second].begin(), dist[end.first][end.second].end());
    printf("%d", answer == INT32_MAX ? -1 : answer);

    return 0;
}