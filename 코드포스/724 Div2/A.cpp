#include <iostream>
#include <vector>
#include <set>

std::set<int> addNumbers(std::set<int> arr) {
    std::set<int> numSet(arr.begin(), arr.end());
    for (int u : arr) {
        numSet.insert(u);
        for (int v : arr) {
            numSet.insert(std::abs(u-v));
        }
    }
    return numSet;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        bool neg = false;
        std::set<int> arr;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            arr.insert(val);
            if (val < 0) {
                neg = true;
            }
        }

        bool yes = true;
        if (neg) {
            yes = false;
        } else {
            while (true) {
                std::set<int> added = addNumbers(arr);
                if (added.size() > 300) {
                    yes = false;
                    break;
                }
                if (added.size() == arr.size()) {
                    break;
                }
                arr = added;
            }
        }

        if (yes) {
            printf("YES\n%lu\n", arr.size());
            for (int v : arr) {
                printf("%d ", v);
            }
        } else {
            printf("NO\n");
        }
    }

    return 0;
}