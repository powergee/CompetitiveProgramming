#include <iostream>
#include <algorithm>

using Long = long long;
const Long MOD = 1000000007;

Long getModPow(Long val, Long exp) {
    if (val == 0) {
        return 0;
    } else if (exp == 0) {
        return 1;
    } else {
        Long pow = getModPow(val, exp/2);
        return (((pow * pow) % MOD) * (exp%2 == 0 ? 1 : val)) % MOD;
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::string input;
    std::cin >> n >> input;
    
    std::reverse(input.begin(), input.end());
    const std::string SEQ = "#KCOR";
    Long count[4] = { 1, 0, 0, 0 };

    Long answer = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        for (size_t j = 1; j <= 3; ++j) {
            if (SEQ[j] == input[i]) {
                count[j] += count[j-1];
                count[j] %= MOD;
            }
        }
        if (SEQ.back() == input[i]) {
            answer += count[3] * getModPow(2, input.size()-i-1);
            answer %= MOD;
        }
    }
    std::cout << answer;

    return 0;
}