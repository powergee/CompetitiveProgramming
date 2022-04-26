#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n[3];
    scanf("%d %d %d", n, n+1, n+2);

    std::vector<int> ingred[3];
    for (int i = 0; i < 3; ++i) {
        ingred[i].resize(n[i]);
        for (int j = 0; j < n[i]; ++j) {
            scanf("%d", &ingred[i][j]);
        }
        std::sort(ingred[i].begin(), ingred[i].end());
    }

    int count = 0;
    while (ingred[0].size() && ingred[1].size() && ingred[2].size()) {
        if (ingred[0].back() < ingred[1].back() && ingred[1].back() < ingred[2].back()) {
            ++count;
            ingred[0].pop_back();
            ingred[1].pop_back();
            ingred[2].pop_back();
        } else if (ingred[1].back() >= ingred[2].back()) {
            ingred[1].pop_back();
        } else if (ingred[0].back() >= ingred[1].back()) {
            ingred[0].pop_back();
        }
    }

    printf("%d", count);

    return 0;
}