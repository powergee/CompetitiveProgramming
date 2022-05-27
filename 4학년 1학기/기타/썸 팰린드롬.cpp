#include <iostream>
#include <algorithm>

typedef long long Long;

int getShortestSide(Long n) {
    if (n) {
        return n / 9 + (n % 9 ? 1 : 0);
    } else {
        return 0;
    }
}

int main() {
    Long n;
    std::cin >> n;
    
    int answer = INT32_MAX;
    if (n % 2 == 0) {
        answer = getShortestSide(n/2)*2;
    }
    for (int m = 1; m <= 9 && m <= n; ++m) {
        if ((n - m) % 2 == 0) {
            answer = std::min(answer, 1+getShortestSide((n-m)/2)*2);
        }
    }
    std::cout << answer;

    return 0;
}