#include <iostream>
#include <vector>
#include <algorithm>

int count[10000];
int dp[10000][2];
std::vector<int> graph[10000];
bool visited[10000];
std::vector<int> child[10000];

void findChildren(int start) {
    visited[start] = true;
    for (int next : graph[start]) {

    }
}

int getMax(int start, int pChosen) {
    int& result = dp[start][pChosen];
    if (result != -1) {
        return result;
    }

    if (pChosen) {
        result = 0;
        for (int next : child[start]) {
            result += getMax(next, 0);
        }
        return result;
    } else {

    }
}

int main() {
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp)/sizeof(int), -1);
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", count+i);
    }

    for (int i = 0; i < n-1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    findChildren(0);

    return 0;
}