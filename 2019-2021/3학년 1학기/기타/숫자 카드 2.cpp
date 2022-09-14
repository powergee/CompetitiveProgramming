#include <iostream>
#include <unordered_map>

int main() {
    int n, m;
    std::unordered_map<int, int> count;

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int card;
        scanf("%d", &card);
        count[card]++;
    }

    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int card;
        scanf("%d", &card);
        if (count.find(card) != count.end()) {
            printf("%d ", count[card]);
        } else {
            printf("0 ");
        }
    }

    return 0;
}