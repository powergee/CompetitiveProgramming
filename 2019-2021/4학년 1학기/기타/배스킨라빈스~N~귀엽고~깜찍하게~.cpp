#include <iostream>
#include <algorithm>

typedef long long Long;

int main() {
    Long n, m;
    std::cin >> n >> m;

    if ((n-1)%(m+1) == 0 && (n-1)/(m+1) >= 0) {
        std::cout << "Can\'t win";
    } else {
        std::cout << "Can win";
    }

    return 0;
}