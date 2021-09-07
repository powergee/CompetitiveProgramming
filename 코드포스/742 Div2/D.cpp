#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long Long;
Long tenPow[10];

int getDigit(Long val, int e) {
    return val / tenPow[e] % 10;
}

int findNonZeroPos(Long val) {
    for (int e = 0; e < 10; ++e) {
        if (getDigit(val, e) > 0) {
            return e;
        }
    }
    return -1;
}

struct Comparer {
    bool operator()(Long v1, Long v2) const {
        v1 = (v1 == 1 ? __INT64_MAX__ : v1);
        v2 = (v2 == 1 ? __INT64_MAX__ : v2);

        return v1 > v2;
    }
};

int main() {
    tenPow[0] = 1;
    for (int i = 1; i < 10; ++i) {
        tenPow[i] = tenPow[i-1] * 10;
    }

    int T;
    scanf("%d", &T);

    while (T--) {
        Long s, n;
        scanf("%lld %lld", &s, &n);

        std::vector<Long> result;
        Long sOrigin = s;
        for (int e = 0; e < 10; ++e) {
            while (getDigit(s, e) > 0) {
                result.push_back(tenPow[e]);
                s -= tenPow[e];
            }
        }

        if (result.size() < n) {
            std::priority_queue<Long, std::vector<Long>, Comparer> q(result.begin(), result.end());
            while (q.size() < n) {
                Long val = q.top();
                q.pop();
                int e = findNonZeroPos(val);
                int digit = getDigit(val, e);
                
                int pushCount = std::min(10, (int)(n-q.size()));
                for (int i = 0; i < pushCount; ++i) {
                    if (i == pushCount-1) {
                        q.push((10-i) * tenPow[e-1]);
                    } else {
                        q.push(tenPow[e-1]);
                    }
                }
            }
            result.clear();
            while (!q.empty()) {
                Long val = q.top();
                q.pop();
                result.push_back(val);
            }
        } else {
            for (int i = (int)result.size()-1; n < result.size() && i > 0; --i) {
                Long sum = result[i] + result[i-1];
                result[i-1] = sum;
                result.pop_back();
            }
        }

        for (Long ans : result) {
            printf("%lld ", ans);
        }
        printf("\n");
    }

    return 0;
}