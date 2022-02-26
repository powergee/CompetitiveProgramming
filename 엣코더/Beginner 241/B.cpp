#include <iostream>
#include <vector>
#include <map>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::map<int, int> has;
    for (int i = 0; i < n; ++i) {
        int v;
        scanf("%d", &v);
        has[v]++;
    }

    bool possible = true;
    for (int i = 0; i < m; ++i) {
        int want;
        scanf("%d", &want);
        if (has[want] > 0) {
            has[want]--;
        } else {
            possible = false;
        }
    }
    printf(possible ? "Yes" : "No");

    return 0;
}