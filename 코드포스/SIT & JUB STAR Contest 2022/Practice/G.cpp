#include <iostream>
#include <vector>
#include <set>
#include <queue>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<int> record(n);
    std::vector<std::set<int>> empls(n);
    std::vector<int> kind(m+1, -1);
    for (int i = 0; i < n; ++i) {
        int a, k;
        scanf("%d %d", &a, &k);
        record[i] = a;

        for (int j = 0; j < k; ++j) {
            int id;
            scanf("%d", &id);
            empls[i].insert(id);
            if (a == 0) {
                kind[id] = 0;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        std::set<int> exceptGood;
        for (int empl : empls[i]) {
            if (kind[empl] != 0) {
                exceptGood.insert(empl);
            }
        }
        if (exceptGood.size() == 1) {
            kind[*exceptGood.begin()] = 1;
        }
    }

    int good = 0, bad = 0, unknown = 0;
    for (int i = 1; i <= m; ++i) {
        if (kind[i] == 0) {
            good++;
        } else if (kind[i] == 1) {
            bad++;
        } else {
            unknown++;
        }
    }

    printf("%d %d %d", good, bad, unknown);

    return 0;
}