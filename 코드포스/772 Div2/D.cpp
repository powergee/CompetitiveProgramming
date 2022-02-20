#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <functional>
#define MOD 1000000007LL

typedef long long Long;

int getBitLength(int x) {
    int bits;
    for (bits = 0; x != 0; ++bits) x >>= 1;
    return bits;
}

int main() {
    int n, p;
    scanf("%d %d", &n, &p);

    std::set<int> arr;
    for (int i = 0; i < n; ++i) {
        int v;
        scanf("%d", &v);
        arr.insert(v);
    }

    std::vector<int> seed;
    for (int v : arr) {
        int curr = v;
        bool isSeed = true;
        while (curr >= 1) {
            if (curr % 4 == 0) {
                if (arr.count(curr/4)) {
                    isSeed = false;
                    break;
                } else {
                    curr /= 4;
                }
            } else if (curr % 2 == 1) {
                if (arr.count((curr-1)/2)) {
                    isSeed = false;
                    break;
                } else {
                    curr = (curr-1) / 2;
                }
            } else {
                break;
            }
        }
        if (isSeed) {
            seed.push_back(v);
        }
    }

    std::vector<Long> dp(p+32, 0);
    for (int s : seed) {
        int bitLength = getBitLength(s);
        dp[bitLength]++;
    }

    for (int i = 2; i <= p; ++i) {
        dp[i] += dp[i-2] + dp[i-1];
        dp[i] %= MOD;
    }
    
    Long answer = 0;
    for (int i = 0; i <= p; ++i) {
        answer += dp[i];
        answer %= MOD;
    }
    printf("%lld", answer);

    return 0;
}