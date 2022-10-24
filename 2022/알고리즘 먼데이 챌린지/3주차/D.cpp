#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::vector<bool> visited(n+1, false);
    std::vector<int> callStack;
    std::vector<int> answer;
    
    std::function<bool(int, int)> findCycle = [&](int start, int parent) -> bool {
        callStack.push_back(start);
        for (int next : graph[start]) {
            if (next == parent) {
                continue;
            }
            if (visited[next]) {
                for (auto it = callStack.rbegin(); *it != next; ++it) {
                    answer.push_back(*it);
                }
                answer.push_back(next);
                return true;
            }
            visited[next] = true;
            if (findCycle(next, start)) {
                return true;
            }
        }
        callStack.pop_back();
        return false;
    };

    assert(findCycle(1, 0));
    std::cout << answer.size() << "\n";
    std::sort(answer.begin(), answer.end());
    for (int i = 0; i < answer.size(); ++i) {
        std::cout << answer[i] << " ";
    }

    return 0;
}