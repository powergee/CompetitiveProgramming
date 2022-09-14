#include <iostream>

int main() {
    unsigned n;
    std::cin >> n;
    unsigned m = (~n)+1;
    
    int count = 0;
    for (int i = 0; i <= 31; ++i) {
        if ((n&(1U<<i)) != (m&(1U<<i))) {
            ++count;
        }
    }
    std::cout << count;

    return 0;
}