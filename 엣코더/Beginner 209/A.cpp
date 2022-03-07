#include <iostream>
#include <algorithm>

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << std::max(b-a+1, 0);

    return 0;
}