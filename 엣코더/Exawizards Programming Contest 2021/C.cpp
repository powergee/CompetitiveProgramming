#include <iostream>
#include <algorithm>

enum MatchResult {
    Left, Right, Draw
};

struct Player {
    char selected;
    int index;
    int winCount = 0;
};

MatchResult match(char p1, char p2) {
    if (p1 == p2) {
        return Draw;
    }

    switch (p1)
    {
    case 'G': return (p2 == 'C' ? Left : Right);
    case 'C': return (p2 == 'P' ? Left : Right);
    default: return (p2 == 'G' ? Left : Right);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char table[2*n][m+1];
    Player players[2*n];

    for (int i = 0; i < 2*n; ++i) {
        scanf("%s", table[i]);
        players[i].index = i;
    }

    for (int j = 0; j < m; ++j) {
        for (int p = 0; p < 2*n; ++p) {
            players[p].selected = table[players[p].index][j];
        }

        for (int i = 0; i < 2*n; i += 2) {
            auto result = match(players[i].selected, players[i+1].selected);
            if (result == Left) {
                players[i].winCount++;
            } else if (result == Right) {
                players[i+1].winCount++;
            }
        }

        std::sort(players, players+(2*n), [](Player& p1, Player& p2) -> bool {
            if (p1.winCount != p2.winCount) {
                return p1.winCount > p2.winCount;
            }
            return p1.index < p2.index;
        });
    }

    for (int i = 0; i < 2*n; ++i) {
        printf("%d\n", players[i].index+1);
    }

    return 0;
}