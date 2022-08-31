#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    std::cin >> n >> k;
    std::vector<int> b(n);
    std::vector<std::vector<int>> group(k+1);
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
        group[b[i]].push_back(i);
    }

    std::vector<std::vector<bool>> hasEdge(k+1, std::vector<bool>(k+1));
    for (int i = 1; i <= k; ++i) {
        std::string line;
        std::cin >> line;
        for (int j = 1; j <= line.size(); ++j) {
            hasEdge[i][j] = line[j-1] == '1';
        }
    }

    std::vector<int> dist(n, INT32_MAX/2);
    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>
    > q;

    q.emplace(0, 0);
    dist[0] = 0;

    while (q.size()) {
        auto [_, curr] = q.top();
        q.pop();
        
        int currB = b[curr];
        for (int nextB = 1; nextB <= k; ++nextB) {
            if (!hasEdge[currB][nextB]) {
                continue;
            }
            // right
            auto rit = std::lower_bound(group[nextB].begin(), group[nextB].end(), curr);
            if (rit != group[nextB].end()) {
                int next = *rit;
                int newDist = dist[curr] + (next-curr);
                if (newDist < dist[next]) {
                    dist[next] = newDist;
                    q.emplace(newDist, next);
                }
            }

            // left
            auto lit = std::lower_bound(group[nextB].rbegin(), group[nextB].rend(), curr, std::greater<int>());
            if (lit != group[nextB].rend()) {
                int next = *lit;
                int newDist = dist[curr] + (curr-next);
                if (newDist < dist[next]) {
                    dist[next] = newDist;
                    q.emplace(newDist, next);
                }
            }
        }
    }

    int answer = INT32_MAX/2;
    for (int v : group[b[n-1]]) {
        if (v == 0) {
            continue;
        }
        answer = std::min(answer, dist[v] + (n-1 - v));
    }

    if (answer == INT32_MAX/2) {
        std::cout << "-1\n";
    } else {
        std::cout << answer << "\n";
    }

    return 0;
}