#include <iostream>
#include <algorithm>
#include <vector>
#define INCLUDE 1
#define EXCLUDE 0

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> weight(n+1);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &weight[i]);
    }

    std::vector<std::vector<int>> graph(n+1);
    std::vector<std::vector<int>> subTree(n+1);
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector<bool> visited(n+1, false);
    std::function<void(int)> recogTree;
    recogTree = [&](int start) -> void {
        visited[start] = true;
        
        for (int next : graph[start]) {
            if (!visited[next]) {
                subTree[start].push_back(next);
                recogTree(next);
            }
        }
    };
    recogTree(1);

    using SubTreeTrace = std::vector<std::pair<int, int>>;
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(2, -1));
    std::vector<std::vector<SubTreeTrace>> trace(n+1, std::vector<SubTreeTrace>(2));

    std::function<int(int, int)> foundMaxSet;
    foundMaxSet = [&](int start, int includeCurrent) -> int {
        int& result = dp[start][includeCurrent];
        if (result != -1) {
            return result;
        }

        result = (includeCurrent ? weight[start] : 0);
        for (int child : subTree[start]) {
            if (includeCurrent) {
                result += foundMaxSet(child, EXCLUDE);
                trace[start][includeCurrent].emplace_back(child, EXCLUDE);
            } else {
                if (foundMaxSet(child, INCLUDE) < foundMaxSet(child, EXCLUDE)) {
                    trace[start][includeCurrent].emplace_back(child, EXCLUDE);
                    result += foundMaxSet(child, EXCLUDE);
                } else {
                    trace[start][includeCurrent].emplace_back(child, INCLUDE);
                    result += foundMaxSet(child, INCLUDE);
                }
            }
        }
        return result;
    };

    printf("%d\n", std::max(foundMaxSet(1, INCLUDE), foundMaxSet(1, EXCLUDE)));

    std::vector<int> choosen;
    std::function<void(int, int)> collectHistory;
    collectHistory = [&](int start, int includeCurrent) -> void {
        if (includeCurrent) {
            choosen.push_back(start);
        }
        for (auto p : trace[start][includeCurrent]) {
            collectHistory(p.first, p.second);
        }
    };
    
    if (foundMaxSet(1, INCLUDE) < foundMaxSet(1, EXCLUDE)) {
        collectHistory(1, EXCLUDE);
    } else {
        collectHistory(1, INCLUDE);
    }
    std::sort(choosen.begin(), choosen.end());

    for (int v : choosen) {
        printf("%d ", v);
    }

    return 0;
}