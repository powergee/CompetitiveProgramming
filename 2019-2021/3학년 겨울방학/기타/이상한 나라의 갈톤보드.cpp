#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

typedef long long Long;

int main() {
    Long h;
    scanf("%lld", &h);
    
    std::vector<Long> floorWidthSum(h), floorStart(h);
    floorWidthSum[0] = floorStart[0] = 1;
    for (int i = 1; i < h; ++i) {
        floorWidthSum[i] = floorWidthSum[i-1] + (i+1);
        floorStart[i] = floorStart[i-1] + i;
    }

    int q, r;
    scanf("%d %d", &q, &r);

    std::vector<double> add(h+2, 0), sub(h+2, 0);

    while (q--) {
        Long a, b;
        scanf("%lld %lld", &a, &b);
        Long floorIdx = std::lower_bound(floorWidthSum.begin(), floorWidthSum.end(), a) - floorWidthSum.begin();
        Long xIdx = a - floorStart[floorIdx];
        Long left = xIdx+1;
        Long right = xIdx+1+h-floorIdx;
        double width = right-left+1;
        add[left] += b/width;
        sub[right] += b/width;
    }

    double curr = 0;
    std::vector<double> expected(h+2, 0);
    for (int i = 1; i <= h+1; ++i) {
        curr += add[i];
        expected[i] = curr;
        curr -= sub[i];
    }

    std::vector<double> expectedSum(h+2);
    std::partial_sum(expected.begin(), expected.end(), expectedSum.begin());
    
    while (r--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%.10lf\n", expectedSum[b]-expectedSum[a-1]);
    }

    return 0;
}