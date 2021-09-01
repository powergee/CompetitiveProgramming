#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }

        bool yes = false;
        std::set<int> sums;

        for (int i = 0; i < n; ++i) {
            if (sums.find(arr[i]) != sums.end()) {
                yes = true;
                break;
            }
            std::vector<int> add;
            for (int s : sums) {
                add.push_back(s+arr[i]);
            }
            for (int s : sums) {
                add.push_back(s-arr[i]);
            }
            add.push_back(arr[i]);
            add.push_back(-arr[i]);

            for (int a : add) {
                sums.insert(a);
            }
        }

        if (std::find(arr, arr+n, 0) != arr+n) {
            yes = true;
        }

        if (yes) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}