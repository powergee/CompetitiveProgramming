#include <iostream>

int tag[1001];

int main() {
    int l, n;
    scanf("%d%d", &l, &n);

    int wantMax = -1;
    int wantIdx = -1;
    int gotMax = -1;
    int gotIdx = -1;

    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);

        int len = b-a+1;
        if (wantMax < len) {
            wantMax = len;
            wantIdx = i+1;
        }

        int got = 0;
        for (int j = a; j <= b; ++j) {
            if (tag[j] != 0) {
                continue;
            }
            tag[j] = i+1;
            ++got;
        }

        if (gotMax < got) {
            gotMax = got;
            gotIdx = i+1;
        }
    }

    printf("%d\n%d", wantIdx, gotIdx);

    return 0;
}