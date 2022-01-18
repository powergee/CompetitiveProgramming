#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int getNearestPow2(int val) {
    int result = 1;
    while (result < val) {
        result *= 2;
    }
    return result;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::map<int, int> count;
        for (int i = 0; i < n; ++i) {
            int weight;
            scanf("%d", &weight);
            count[weight]++;
        }

        std::vector<int> sum(1, 0);
        for (auto p : count) {
            sum.push_back(sum.back() + p.second);
        }

        int answer = getNearestPow2(n) - n + 2;
        for (int i = 0; i < sum.size(); ++i) {
            int exist1 = sum[i];
            int div1 = getNearestPow2(exist1);
            int need1 = div1 - exist1;
            
            for (int div2 = 1; div2 <= (1<<22); div2 <<= 1) {
                auto bound = std::lower_bound(sum.begin()+i+1, sum.end(), exist1+div2);

                if (bound == sum.begin() && exist1+div2 < *bound) {
                    continue;
                }

                if (exist1+div2 < *bound) {
                    --bound;
                }
                int exist2 = *bound-exist1;
                int need2 = div2 - exist2;

                int exist3 = n-*bound;
                int div3 = getNearestPow2(exist3);
                int need3 = div3 - exist3;

                answer = std::min(answer, need1+need2+need3);
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}