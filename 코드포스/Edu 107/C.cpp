#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::list<int> miniDeck;
    for (int i = 1; i <= n; ++i) {
        int card;
        scanf("%d", &card);
        miniDeck.push_back(card);
    }

    for (int i = 0; i < q; ++i) {
        int t;
        scanf("%d", &t);

        auto it = miniDeck.begin();
        int pos = 1;
        for (; it != miniDeck.end(); ++it) {
            if (*it == t) {
                break;
            }
            ++pos;
        }

        printf("%d ", pos);
        miniDeck.erase(it);
        miniDeck.push_front(t);
    }
}