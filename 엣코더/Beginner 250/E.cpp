#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &b[i]);
    }

    auto findNewValue = [](std::vector<int>& arr, int& index, std::set<int>& found) {
        while (index < arr.size()) {
            int curr = arr[index];
            if (found.count(curr) == 0) {
                found.insert(curr);
                return curr;
            }
            ++index;
        }
        return 0;
    };

    std::set<int> aFound, bFound;
    std::set<int> aOnly, bOnly;
    std::vector<int> aSetSize(n), bSetSize(n);
    std::vector<int> aMatched(n, -1), bMatched(n, -1);

    for (int i = 0; i < n; ++i) {
        aFound.insert(a[i]);
        aSetSize[i] = aFound.size();
    }
    aFound.clear();

    for (int i = 0; i < n; ++i) {
        bFound.insert(b[i]);
        bSetSize[i] = bFound.size();
    }
    bFound.clear();

    int i = 0, j = 0;
    while (i < n && j < n) {
        int aNew = findNewValue(a, i, aFound);
        int bNew = findNewValue(b, j, bFound);

        if (aNew == 0 || bNew == 0) {
            break;
        }
        if (aNew != bNew) {
            if (aOnly.count(bNew)) {
                aOnly.erase(bNew);
            } else {
                bOnly.insert(bNew);
            }
            if (bOnly.count(aNew)) {
                bOnly.erase(aNew);
            } else {
                aOnly.insert(aNew);
            }
        }

        if (aOnly.empty() && bOnly.empty()) {
            aMatched[i] = j;
            bMatched[j] = i;
        }
    }

    for (int i = 1; i < n; ++i) {
        aMatched[i] = std::max(aMatched[i], aMatched[i-1]);
        bMatched[i] = std::max(bMatched[i], bMatched[i-1]);
    }

    int q;
    scanf("%d", &q);

    while (q--) {
        int x, y;
        scanf("%d %d", &x, &y);
        --x, --y;
        if (aSetSize[x] != bSetSize[y]) {
            printf("No\n");
        } else if (aMatched[x] != -1 && bMatched[y] != -1 && aMatched[x] <= y && bMatched[y] <= x) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}