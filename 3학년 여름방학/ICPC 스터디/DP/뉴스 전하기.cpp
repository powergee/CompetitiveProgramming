#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

int n;
std::vector<int> graph[50];

int getMinTime(int node) {
    std::vector<int> subTimes;
    for (int child : graph[node]) {
        subTimes.push_back(getMinTime(child));
    }

    std::sort(subTimes.begin(), subTimes.end(), std::greater<int>());
    int maxTime = INT32_MIN;
    for (int i = 0; i < subTimes.size(); ++i) {
        maxTime = std::max(maxTime, subTimes[i]+i+1);
    }

    return std::max(maxTime, 0);
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int parent;
        scanf("%d", &parent);
        if (parent != -1) {
            graph[parent].push_back(i);
        }
    }

    printf("%d", getMinTime(0));
    return 0;
}