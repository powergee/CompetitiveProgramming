#include <iostream>
#include <unordered_set>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::unordered_set<int> set;
    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        set.insert(val);
    }
    for (int i = 0; i < m; ++i) {
        int val;
        scanf("%d", &val);
        if (set.find(val) == set.end()) {
            set.insert(val);
        } else {
            set.erase(val);
        }
    }

    printf("%d", (int)set.size());

    return 0;
}