#include <iostream>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int h, w, r, c;
    std::cin >> h >> w >> r >> c;
    
    int count = 0;
    auto isValid = [&](int x, int y) { return 1 <= x && x <= h && 1 <= y && y <= w; };
    if (isValid(r-1, c)) { ++count; }
    if (isValid(r, c-1)) { ++count; }
    if (isValid(r+1, c)) { ++count; }
    if (isValid(r, c+1)) { ++count; }

    std::cout << count;

    return 0;
}