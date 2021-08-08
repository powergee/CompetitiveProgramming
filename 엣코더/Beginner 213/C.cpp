#include <iostream>
#include <algorithm>
#include <map>

struct Card {
    int num, row, col;
};

Card cards[100000];

int main() {
    int h, w, n;
    scanf("%d %d %d", &h, &w, &n);

    for (int i = 0; i < n; ++i) {
        cards[i].num = i;
        scanf("%d %d", &cards[i].row, &cards[i].col);
    }

    std::sort(cards, cards+n, [](auto p1, auto p2) -> bool {
        return p1.row < p2.row;
    });

    std::map<int, int> comp;
    for (int i = 0; i < n; ++i) {
        if (comp.find(cards[i].row) == comp.end()) {
            comp[cards[i].row] = (int)comp.size() + 1;
        }
        cards[i].row = comp[cards[i].row];
    }

    std::sort(cards, cards+n, [](auto p1, auto p2) -> bool {
        return p1.col < p2.col;
    });

    comp.clear();
    for (int i = 0; i < n; ++i) {
        if (comp.find(cards[i].col) == comp.end()) {
            comp[cards[i].col] = (int)comp.size() + 1;
        }
        cards[i].col = comp[cards[i].col];
    }

    std::sort(cards, cards+n, [](auto p1, auto p2) -> bool {
        return p1.num < p2.num;
    });

    for (int i = 0; i < n; ++i) {
        printf("%d %d\n", cards[i].row, cards[i].col);
    }

    return 0;
}