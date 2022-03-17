#include <iostream>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> tab(367, 0), space(367, 0);
    int maxDuration = 0;
    for (int i = 0; i < n; ++i) {
        char type[2];
        int s, e;
        scanf("%s %d %d", type, &s, &e);
        maxDuration = std::max(maxDuration, e-s+1);
        auto& timeline = (type[0] == 'T' ? tab : space);
        for (int j = s; j <= e; ++j) {
            timeline[j]++;
        }
    }

    int atLeastOne = 0, maxPeople = 0, fightCount = 0, maxOnNonFight = 0;
    for (int i = 1; i <= 366; ++i) {
        if (tab[i] || space[i]) {
            atLeastOne++;
        }
        maxPeople = std::max(maxPeople, tab[i] + space[i]);

        bool fight = false;
        if (tab[i] && space[i] && tab[i] != space[i]) {
            fight = true;
        }
        if (tab[i] == 0 || space[i] == 0) {
            fight = true;
        }

        fightCount += fight ? 1 : 0;
        if (!fight) {
            maxOnNonFight = std::max(maxOnNonFight, tab[i] + space[i]);
        }
    }

    printf("%d\n", atLeastOne);
    printf("%d\n", maxPeople);
    printf("%d\n", 366-fightCount);
    printf("%d\n", maxOnNonFight);
    printf("%d\n", maxDuration);

    return 0;
}