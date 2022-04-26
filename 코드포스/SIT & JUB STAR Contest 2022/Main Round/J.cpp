#include <iostream>
#include <queue>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::queue<std::pair<int, int>> q;
    std::vector<int> parent(n+1);
    std::vector<int> indegree(n+1, 0);
    for (int i = 2; i <= n; ++i) {
        int p;
        scanf("%d", &p);
        indegree[p]++;
        parent[i] = p;
    }

    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            q.emplace(i, 1);
        }
    }

    std::vector<int> contextLengths;
    std::vector<std::vector<int>> waitingContexts(n+1);
    while (!q.empty()) {
        auto [curr, length] = q.front();
        q.pop();

        if (curr == 1) {
            contextLengths.push_back(length);
            continue;
        }

        indegree[parent[curr]]--;
        waitingContexts[parent[curr]].emplace_back(length+1);
        if (indegree[parent[curr]] == 0) {
            std::sort(waitingContexts[parent[curr]].begin(), waitingContexts[parent[curr]].end(), std::greater<int>());
            q.emplace(parent[curr], waitingContexts[parent[curr]][0]);
            for (int i = 1; i < waitingContexts[parent[curr]].size(); ++i) {
                contextLengths.push_back(waitingContexts[parent[curr]][i]-1);
            }
        }
    }

    std::sort(contextLengths.begin(), contextLengths.end(), std::greater<int>());
    int sum = 0;
    for (int i = 0; i < contextLengths.size(); ++i) {
        printf("%d ", sum+contextLengths[i]);
        sum += contextLengths[i];
    }
    for (int i = contextLengths.size(); i < n; ++i) {
        printf("%d ", sum);
    }

    return 0;
}