#include <iostream>
#include <algorithm>
#include <vector>

bool parity[100000];
bool copy[100000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            parity[i] = (val % 2 == 0);
        }
        std::copy(parity, parity+n, copy);

        int minSwaps = __INT32_MAX__;
        for (int d = 0; d < 2; ++d) {
            int swaps = 0;
            bool success = true;
            int eIdx = std::find(parity, parity+n, true) - parity;
            int oIdx = std::find(parity, parity+n, false) - parity;
            
            for (int i = 0; i < n; ++i) {
                bool needEven = (((i+d) % 2 == 0) ? true : false);
                if (needEven) {
                    eIdx = std::max(eIdx, i);
                    bool* found = std::find(parity+eIdx, parity+n, true);
                    if (found == parity+n) {
                        success = false;
                        break;
                    }
                    int fIdx = found - parity;
                    if (fIdx != i) {
                        swaps += std::abs(fIdx - i);
                        parity[i] = true;
                        parity[fIdx] = false;
                    }
                    if (i <= oIdx && oIdx <= fIdx) {
                        ++oIdx;
                    } else if (fIdx <= oIdx && oIdx <= i) {
                        --oIdx;
                    }
                    eIdx = fIdx;
                } else {
                    oIdx = std::max(oIdx, i);
                    bool* found = std::find(parity+oIdx, parity+n, false);
                    if (found == parity+n) {
                        success = false;
                        break;
                    }
                    int fIdx = found - parity;
                    if (fIdx != i) {
                        swaps += std::abs(fIdx - i);
                        parity[i] = false;
                        parity[fIdx] = true;
                    }
                    if (i <= eIdx && eIdx <= fIdx) {
                        ++eIdx;
                    } else if (fIdx <= eIdx && eIdx <= i) {
                        --eIdx;
                    }
                    oIdx = fIdx;
                }
            }

            if (success) {
                minSwaps = std::min(minSwaps, swaps);
            }
            std::copy(copy, copy+n, parity);
        }

        if (minSwaps == __INT32_MAX__) {
            printf("-1\n");
        } else {
            printf("%d\n", minSwaps);
        }
    }

    return 0;
}