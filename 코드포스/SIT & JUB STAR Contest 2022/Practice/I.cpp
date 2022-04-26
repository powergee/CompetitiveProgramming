#include <iostream>
#include <deque>

int main() {
    int n;
    scanf("%d", &n);

    std::deque<int> deck[2];
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            int v;
            scanf("%d", &v);
            deck[i].push_back(v);
        }
    }

    int turn = 0;
    while (!deck[0].empty() && !deck[1].empty()) {
        if (turn == 1000000) {
            turn = -1;
            break;
        }

        ++turn;
        int v1 = deck[0].front();
        deck[0].pop_front();
        int v2 = deck[1].front();
        deck[1].pop_front();

        if (v1 < v2) {
            deck[1].push_back(v2);
            deck[1].push_back(v1);
        } else {
            deck[0].push_back(v1);
            deck[0].push_back(v2);
        }
    }

    printf("%d", turn);

    return 0;
}