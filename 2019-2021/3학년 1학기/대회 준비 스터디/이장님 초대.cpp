#include <iostream>
#include <algorithm>
#include <functional>

int tree[100000];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", tree+i);
    }

    std::sort(tree, tree+n, std::greater<int>());

    int time = 0;
    for (int i = 0; i < n; ++i) {
        time = std::max(time, tree[i] + i + 2);
    }

    printf("%d", time);
    return 0;
}