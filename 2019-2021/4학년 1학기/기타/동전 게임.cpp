#include <iostream>
#include <algorithm>

int main() {
    int k, q;
    scanf("%d%d", &k, &q);

    while (q--) {
        int n, m;
        scanf("%d %d", &n, &m);

        bool possible = false;
        for (int nGain = 0; nGain <= 1; ++nGain) {
            for (int mGain = 0; mGain <= 1; ++mGain) {
                int nPrev = n - nGain;
                int mPrev = m - mGain;
                if (std::max(nPrev, mPrev) == k) {
                    continue;
                }
                int min = std::min(nPrev, mPrev);
                int max = std::max(nPrev, mPrev);
                int spare = k - max;
                if (min+spare < max) {
                    continue;
                }
                if (mGain && (n+spare-1 < mPrev || mPrev+spare < n)) {
                    continue;
                }
                possible = true;
            }
        }
        printf(possible ? "1\n" : "0\n");
    }

    return 0;
}