#include <iostream>
#include <map>
#include <set>
#include <vector>
#define MOD 998244353
 
typedef long long Long;
 
Long getModPow(Long val, Long exp, Long mod) {
    Long result = 1, subPower = val % mod;
    while (exp) {
        if (exp % 2 == 1) {
            result = (result * subPower) % mod;
        }
        exp /= 2;
        subPower = (subPower * subPower) % mod;
    }
    return result;
}
 
int main() {
    int T;
    scanf("%d", &T);
 
    while (T--) {
        int n, m, k, q;
        scanf("%d %d %d %d", &n, &m, &k, &q);
 
        std::vector<std::pair<int, int>> queries;
        for (int i = 0; i < q; ++i) {
            int r, c;
            scanf("%d %d", &r, &c);
            queries.emplace_back(r, c);
        }
 
        if (n == 1 || m == 1) {
            printf("%d\n", k);
        } else {
            int survived = 0;
            std::set<int> rowColored, colColored;
            for (auto it = queries.rbegin(); it != queries.rend(); ++it) {
                auto [r, c] = *it;
                if (rowColored.count(r) == 0 && colColored.count(c) == 0) {
                    survived++;
                    rowColored.insert(r);
                    colColored.insert(c);
                } else if (rowColored.count(r) == 0 && colColored.size() < m) {
                    survived++;
                    rowColored.insert(r);
                    colColored.insert(c);
                } else if (colColored.count(c) == 0 && rowColored.size() < n) {
                    survived++;
                    rowColored.insert(r);
                    colColored.insert(c);
                }
            }
            printf("%lld\n", getModPow(k, survived, MOD));
        }
    }
 
    return 0;
}