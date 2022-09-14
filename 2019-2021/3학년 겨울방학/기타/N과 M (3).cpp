#include <iostream>
#include <vector>
#include <functional>

int n, m;
std::vector<int> chosen;

void choose() {
    if (chosen.size() == m) {
        for (int c : chosen) {
            printf("%d ", c);
        }
        printf("\n");
    } else {
        for (int i = 1; i <= n; ++i) {
            chosen.push_back(i);
            choose();
            chosen.pop_back();
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    choose();
    return 0;
}