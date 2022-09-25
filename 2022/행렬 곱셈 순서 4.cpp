#include <iostream>
#include <cassert>

using Long = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    
    Long rs[n], cs[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> rs[i] >> cs[i];
    }

    Long answer = rs[n-2] * cs[n-2] * cs[n-1];
    Long currR = rs[n-2], currC = cs[n-1];
    for (int i = n-3; i >= 0; --i) {
        assert(cs[i] == currR);
        answer += rs[i] * currR * currC;
        currR = rs[i];
    }

    std::cout << answer;

    return 0;
}