#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#define MOD 998244353LL

using Long = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::string s;
        std::cin >> n >> s;

        Long answer = 0;
        for (int i = 0; 2*i <= n-1; ++i) {
            answer = (26*answer) % MOD;
            answer = (answer+s[i]-'A') % MOD;
        }
        answer = (answer+1) % MOD;

        std::string maxPalin = s;
        for (int i = 0; 2*i <= n-1; ++i) {
            maxPalin[n-1-i] = maxPalin[i];
        }
        if (s < maxPalin) {
            answer = (answer+(MOD-1)) % MOD;
        }

        std::cout << answer << "\n";
    }

    return 0;
}