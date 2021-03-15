#include <iostream>

typedef long long Long;

Long getModOfPow(Long a, Long b, Long c) {
    if (b == 0LL) {
        return 1LL % c;
    } else if (b == 1LL) {
        return a % c;
    } else if (b % 2LL == 0LL) {
        Long sub = getModOfPow(a, b/2LL, c);
        return (sub*sub) % c;
    } else {
        return (getModOfPow(a, b-1, c) * (a%c)) % c;
    }
}

int main() {
    Long a, b, c;
    std::cin >> a >> b >> c;
    std::cout << getModOfPow(a, b, c);
    return 0;
}