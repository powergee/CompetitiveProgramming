#include <iostream>
#include <algorithm>

int main() {
    long long n;
    scanf("%lld", &n);
    int side[6];
    int sum = 0;

    for (int i = 0; i < 6; ++i) {
        scanf("%d", side+i);
        sum += side[i];
    }

    if (n == 1) {
        printf("%d", sum - *std::max_element(side, side+6));
    } else {
        int min1 = *std::min_element(side, side+6);
        std::vector<int> min2Cand = {
            side[0] + side[1],
            side[0] + side[2],
            side[0] + side[3],
            side[0] + side[4],

            side[1] + side[0],
            side[1] + side[2],
            side[1] + side[3],
            side[1] + side[5],

            side[2] + side[0],
            side[2] + side[1],
            side[2] + side[4],
            side[2] + side[5],

            side[3] + side[0],
            side[3] + side[1],
            side[3] + side[4],
            side[3] + side[5],

            side[4] + side[0],
            side[4] + side[2],
            side[4] + side[3],
            side[4] + side[5],

            side[5] + side[1],
            side[5] + side[2],
            side[5] + side[3],
            side[5] + side[4],
        };
        int min2 = *std::min_element(min2Cand.begin(), min2Cand.end());
        std::vector<int> min3Cand = {
            side[0] + side[1] + side[3],
            side[0] + side[3] + side[4],
            side[0] + side[2] + side[4],
            side[0] + side[1] + side[2],
            side[1] + side[3] + side[5],
            side[1] + side[2] + side[5],
            side[3] + side[4] + side[5],
            side[2] + side[4] + side[5],
        };
        int min3 = *std::min_element(min3Cand.begin(), min3Cand.end());

        long long answer = 0;
        answer += min3 * 4;
        answer += min2 * (8*n-12);
        answer += min1 * (n-2) * (5*n-6);
        printf("%lld", answer);
    }

    return 0;
}