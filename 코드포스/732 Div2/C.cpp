#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>

int arr[100000];

struct Count {
    int even, odd;

    Count() {
        even = odd = 0;
    }

    Count(int e, int o) {
        even = e;
        odd = o;
    }
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::set<int> valSet;
        std::map<int, Count> indexCount;
        std::map<int, Count> availCount;

        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
            valSet.insert(arr[i]);
            
            if (i % 2 == 0) {
                indexCount[arr[i]].even++;
            } else {
                indexCount[arr[i]].odd++;
            }
        }
        std::sort(arr, arr+n);

        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                availCount[arr[i]].even++;
            } else {
                availCount[arr[i]].odd++;
            }
        }

        bool isPossible = true;
        for (int val : valSet) {
            auto avail = availCount[val];
            auto need = indexCount[val];

            if (avail.even < need.even || avail.odd < need.odd) {
                isPossible = false;
                break;
            }
        }

        if (isPossible) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}