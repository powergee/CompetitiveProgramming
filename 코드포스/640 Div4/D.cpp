#include <iostream>
#include <deque>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::deque<int> candies;
        for (int i = 0; i < n; ++i) {
            int v;
            scanf("%d", &v);
            candies.push_back(v);
        }

        int move = 0;
        int aliceTotal = 0, bobTotal = 0;
        int alicePrev = 0, bobPrev = 0;
        while (candies.size()) {
            ++move;
            int aliceCurr = 0;
            while (aliceCurr <= bobPrev && candies.size()) {
                aliceCurr += candies.front();
                candies.pop_front();
            }
            aliceTotal += aliceCurr;
            alicePrev = aliceCurr;

            if (candies.empty()) {
                break;
            }
            ++move;
            int bobCurr = 0;
            while (bobCurr <= alicePrev && candies.size()) {
                bobCurr += candies.back();
                candies.pop_back();
            }
            bobTotal += bobCurr;
            bobPrev = bobCurr;
        }

        printf("%d %d %d\n", move, aliceTotal, bobTotal);
    }

    return 0;
}