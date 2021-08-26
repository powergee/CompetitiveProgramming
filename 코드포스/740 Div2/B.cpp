#include <iostream>
#include <vector>

bool isPossible(int a, int b, int k) {
    int total = a+b;
    int bCount = total / 2;
    int aCount = total - bCount;

    // aBreak : [std::max(0, k-bCount), std::min(aCount, k)]
    // aWin : bBreak + aCount-aBreak
    //      : k + aCount - 2*aBreak
    // k + aCount - 2*aBreak == a
    //                aBreak == -(a - k - aCount) / 2
    // bWin : aBreak + bCount-bBreak

    if ((a - k - aCount) % 2 != 0) {
        return false;
    }
    int aBreak = -(a - k - aCount) / 2;
    if (aBreak < std::max(0, k-bCount) || std::min(aCount, k) < aBreak) {
        return false;
    }
    int bWin = 2*aBreak + bCount - k;
    return bWin == b;

    // bool result = false;
    // for (int aBreak = std::max(0, k-bCount); aBreak <= std::min(aCount, k); ++aBreak) {
    //     int bBreak = k-aBreak;
    //     int aWin = bBreak + aCount-aBreak;
    //     int bWin = aBreak + bCount-bBreak;
    //     if (aWin == a && bWin == b) {
    //         result = true;
    //     }
    // }
    // return result;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a, b;
        scanf("%d %d", &a, &b);

        std::vector<int> answer;
        for (int k = 0; k <= a+b; ++k) {
            if (isPossible(a, b, k) || isPossible(b, a, k)) {
                answer.push_back(k);
            }
        }

        printf("%d\n", (int)answer.size());
        for (int ans : answer) {
            printf("%d ", ans);
        }
        printf("\n");
    }

    return 0;
}