#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

char str[1000001];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        scanf("%s", str);
        std::vector<int> sheep;
        std::map<int, int> pivotCount;

        for (int i = 0; i < n; ++i) {
            if (str[i] == '*') {
                sheep.push_back(i);
            }
        }
        int c = (int)sheep.size();
        for (int i = 0; i < c; ++i) {
            pivotCount[sheep[i] - i]++;
        }

        std::vector<long long> ops(n-c+1, 0);
        for (int i = 0; i < c; ++i) {
            ops[0] += std::abs(i-sheep[i]);
        }
        
        int decreasing = c;
        int increasing = 0;
        if (pivotCount.find(0) != pivotCount.end()) {
            decreasing -= pivotCount[0];
            increasing += pivotCount[0];
        }

        for (int p = 1; p <= n-c; ++p) {
            ops[p] = ops[p-1] - decreasing + increasing;
            if (pivotCount.find(p) != pivotCount.end()) {
                decreasing -= pivotCount[p];
                increasing += pivotCount[p];
            }
        }

        printf("%lld\n", *std::min_element(ops.begin(), ops.end()));
    }

    return 0;
}