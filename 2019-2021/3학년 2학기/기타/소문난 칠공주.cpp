#include <iostream>
#include <bitset>
#include <functional>

char map[5][6];

inline bool get(int mask, int r, int c) {
    return (mask & (1<<(r*5+c))) > 0;
}

inline void set(int& mask, int r, int c) {
    mask = (mask | (1<<(r*5+c)));
}

inline bool isValid(int r, int c) {
    return 0 <= r && r < 5 && 0 <= c && c < 5;
}

bool areAdjacent(int mask) {
    int visited = 0;
    std::function<void(int, int)> DFS;
    DFS = [&](int r, int c) -> void {
        set(visited, r, c);
        static int dr[] = { 1, -1, 0, 0 };
        static int dc[] = { 0, 0, 1, -1 };
        for (int i = 0; i < 4; ++i) {
            int nr = r+dr[i];
            int nc = c+dc[i];
            if (isValid(nr, nc) && get(mask, nr, nc) && !get(visited, nr, nc)) {
                DFS(nr, nc);
            }
        }
    };

    for (int e = 0; e < 25; ++e) {
        if (mask & (1<<e)) {
            DFS(e/5, e%5);
            break;
        }
    }

    return visited == mask;
}

int countS(int mask) {
    int count = 0;
    for (int e = 0; e < 25; ++e) {
        if ((mask & (1<<e)) == 0) {
            continue;
        }
        int r = e / 5;
        int c = e % 5;
        if (map[r][c] == 'S') {
            ++count;
        }
    }
    return count;
}

int main() {
    for (int i = 0; i < 5; ++i) {
        scanf("%s", map[i]);
    }

    int answer = 0;
    for (int mask = 0; mask < (1<<25); ++mask) {
        if (std::bitset<30>(mask).count() == 7 && areAdjacent(mask) && countS(mask) >= 4) {
            ++answer;
        }
    }
    printf("%d", answer);

    return 0;
}
