#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <queue>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::string data;
    std::cin >> data;
    
    int ops;
    std::cin >> ops;
    std::vector<int> distToInv(n, -1);
    std::vector<std::vector<int>> graph(n);
    std::queue<std::pair<int, int>> q;

    while (ops--) {
        int kind;
        std::cin >> kind;

        if (kind == 1) {
            int x;
            std::cin >> x;
            q.emplace(x-1, 0);
            distToInv[x-1] = 0;
        } else {
            int x, y;
            std::cin >> x >> y;
            graph[x-1].push_back(y-1);
            graph[y-1].push_back(x-1);
        }
    }

    while (!q.empty()) {
        auto [curr, dist] = q.front();
        q.pop();

        for (int next : graph[curr]) {
            if (distToInv[next] == -1) {
                distToInv[next] = dist+1;
                q.emplace(next, dist+1);
            }
        }
    }

    Long answer = 0;
    for (int i = 0; i < n; ++i) {
        if (data[i] == '1') {
            continue;
        } else if (distToInv[i] == -1) {
            answer = -1;
            break;
        } else {
            answer += distToInv[i]+1;
        }
    }

    std::cout << answer;

    return 0;
}