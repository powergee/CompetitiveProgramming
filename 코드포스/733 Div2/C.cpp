#include <iostream>
#include <algorithm>
#include <deque>

int a[100000];
int b[100000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", a+i);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d", b+i);
        }

        std::sort(a, a+n, std::greater<int>());
        std::sort(b, b+n, std::greater<int>());

        int aSum = 0, bSum = 0;
        int considering = n-(n/4);
        std::deque<int> aHigh, bHigh;
        for (int i = 0; i < considering; ++i) {
            aHigh.push_back(a[i]);
            aSum += a[i];
            bHigh.push_back(b[i]);
            bSum += b[i];
        }

        int k = n;
        int bIdx = considering;
        while (aSum < bSum) {
            aHigh.push_front(100);
            aSum += 100;
            ++k;
            int currCon = k-(k/4);

            if (currCon < aHigh.size()) {
                aSum -= aHigh.back();
                aHigh.pop_back();
            }
            if (bHigh.size() < currCon) {
                if (bIdx < n) {
                    bSum += b[bIdx];
                    bHigh.push_back(b[bIdx++]);
                } else {
                    bHigh.push_back(0);
                }
            }
        }

        printf("%d\n", k-n);
    }

    return 0;
}