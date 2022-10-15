#include <iostream>
#include <vector>
#include <set>
#include <cassert>

int main() {
    int a, b;
    std::cin >> a >> b;
    
    std::vector<std::pair<int, int>> moves;
    if (a == b) {
        moves = {
            { a, a },
            { a, -a },
            { a, -a },
            { -a, -a },
            { -a, -a },
            { -a, a },
            { a, a }
        };
    } else if (a == 0 || b == 0) {
        int d = a == 0 ? b : a;
        moves = {
            { 0, d },
            { d, 0 },
            { d, 0 },
            { 0, -d },
            { 0, -d },
            { -d, 0 },
            { 0, d }
        };
    } else {
        if (a > b) {
            std::swap(a, b);
        }
        moves = {
            { b, a },
            { a, b },
            { -b, a },
            { -b, -a },
            { a, -b },
            { b, -a },
            { a, b },
            { -a, b },
            { -b, -a },
            { -a, -b },
            { b, -a },
            { b, a },
            { -a, b },
            { -b, a },
            { a, -b }
        };
    }

    int x = 0, y = 0;
    std::set<std::pair<int, int>> visited { { x, y } };
    std::cout << moves.size() << "\n";
    for (auto [dx, dy] : moves) {
        x += dx;
        y += dy;
        std::cout << x << " " << y << "\n";
        assert(visited.count({x, y}) == 0);
        visited.emplace(x, y);
    }
    
    assert(visited.count({x+a, y+b}) == 1);
    assert(visited.count({x-a, y+b}) == 1);
    assert(visited.count({x+a, y-b}) == 1);
    assert(visited.count({x-a, y-b}) == 1);
    assert(visited.count({x+b, y+a}) == 1);
    assert(visited.count({x-b, y+a}) == 1);
    assert(visited.count({x+b, y-a}) == 1);
    assert(visited.count({x-b, y-a}) == 1);

    return 0;
}