#include <iostream>
#include <algorithm>
#include <set>

int main() {
    std::set<int> xSet, ySet;
    for (int i = 0; i < 3; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (xSet.count(x)) {
            xSet.erase(x);
        } else {
            xSet.insert(x);
        }
        if (ySet.count(y)) {
            ySet.erase(y);
        } else {
            ySet.insert(y);
        }
    }

    printf("%d %d", *xSet.begin(), *ySet.begin());

    return 0;
}