#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>
#include <numeric>
#include <array>
#include <queue>
#include <map>
#include <set>
#include <cassert>
#include <cmath>

typedef long long Long;

int chances = 50;

Long query(Long a, Long b) {
    assert(--chances >= 0);
    std::cout << "? " << a << " " << b << "\n";
    std::cout.flush();
    Long res;
    std::cin >> res;
    return res;
}

void answer(Long n) {
    std::cout << "! " << n << "\n";
    std::cout.flush();
    exit(0);
}

int main() {
    for (int i = 3; ; ++i) {
        Long res1 = query(1, i);
        if (res1 == -1) {
            answer(i-1);
        }
        Long res2 = query(i, 1);
        if (res1 != res2) {
            answer(res1+res2);
        }
    }
    
    return 0;
}