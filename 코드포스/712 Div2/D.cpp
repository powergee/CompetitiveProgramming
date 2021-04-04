#include <iostream>
#include <queue>

int table[100][100];

void placeAtFront(std::queue<std::pair<int, int>>& q, int value) {
    auto pos = q.front();
    q.pop();
    table[pos.first][pos.second] = value;
    printf("%d %d %d\n", value, pos.first + 1, pos.second + 1);
    fflush(stdout);
}

int main() {
    int n;
    scanf("%d", &n);

    std::queue<std::pair<int, int>> even, odd;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i+j) % 2 == 0) {
                even.emplace(i, j);
            } else {
                odd.emplace(i, j);
            }
        }
    }

    for (int i = 0; i < n*n; ++i) {
        int alice;
        scanf("%d", &alice);

        switch (alice) {
            case 1: {
                if (even.empty()) {
                    placeAtFront(odd, 3);
                } else {
                    placeAtFront(even, 2);
                }
                break;
            }
            case 2: {
                if (odd.empty()) {
                    placeAtFront(even, 3);
                } else {
                    placeAtFront(odd, 1);
                }
                break;
            }
            case 3: {
                if (odd.empty()) {
                    placeAtFront(even, 2);
                } else {
                    placeAtFront(odd, 1);
                }
                break;
            }
        }
    }
}