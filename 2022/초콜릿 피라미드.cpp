#include <iostream>
#include <valarray>
#include <vector>

typedef long long Long;

Long getArith1(Long count) {
    return count*(count+1) / 2;
}

Long getArith2(Long count) {
    return count*(count+1)*(2*count+1)/6;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        Long r, c;
        std::cin >> r >> c;
        
        Long b = std::min(r-1, c-1);
        Long base = 2*(b+1)*r*c - 2*(r+c)*getArith1(b) + 2*getArith2(b) - (b+1)*r - (b+1)*c + 2*getArith1(b);
        std::cout << base+(b+1) << " " << base << "\n";
    }

    return 0;
}