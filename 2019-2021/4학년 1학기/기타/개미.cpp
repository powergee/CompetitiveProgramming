#include <iostream>

int main() {
    int w, h, p, q, t;
    std::cin >> w >> h >> p >> q >> t;
    
    auto move = [&](int x, int dist, int bound) {
        int nx = x+dist;
        if (nx <= bound) {
            return nx;
        }
        int div = (nx-bound-1) / bound;
        int rest = (nx-bound-1) % bound;
        return div % 2 == 0 ? (bound-1-rest) : (1+rest);
    };

    std::cout << move(p, t, w) << " " << move(q, t, h);

    return 0;
}