#include <iostream>
#include <algorithm>

struct Athlete {
    int ranks[5];

    bool operator<(const Athlete& a) const {
        int count = 0;
        for (int i = 0; i < 5; ++i) {
            if (ranks[i] < a.ranks[i]) {
                ++count;
            }
        }
        return count >= 3;
    }
} athlete[50000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 5; ++j) {
                scanf("%d", &athlete[i].ranks[j]);
            }
        }

        Athlete* minPtr = athlete;
        for (int i = 1; i < n; ++i) {
            if (athlete[i] < *minPtr || ((*minPtr < athlete[i]) == false)) {
                minPtr = athlete+i;
            }
        }

        bool found = true;
        for (int i = 0; i < n; ++i) {
            if (minPtr == athlete+i) {
                continue;
            }
            if (athlete[i] < *minPtr) {
                found = false;
            }
        }

        if (found) {
            printf("%d\n", (int)(minPtr - athlete + 1));
        } else {
            printf("-1\n");
        }
    }

    return 0;
}