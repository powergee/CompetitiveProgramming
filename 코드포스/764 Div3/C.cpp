#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> arr(n);
        std::vector<std::set<int>> cands(n);
        std::vector<bool> used(n, false);

        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
            cands[i].insert(arr[i]);
            while (*cands[i].begin()/2 >= 1) {
                cands[i].insert(*cands[i].begin()/2);
            }
        }

        bool yes = true;
        for (int i = n; i >= 1; --i) {
            bool foundCurrent = false;
            for (int j = 0; j < n; ++j) {
                if (!used[j] && cands[j].find(i) != cands[j].end()) {
                    used[j] = true;
                    foundCurrent = true;
                    break;
                }
            }
            if (!foundCurrent) {
                yes = false;
            }
        }

        printf(yes ? "YES\n" : "NO\n");
    }

    return 0;
}