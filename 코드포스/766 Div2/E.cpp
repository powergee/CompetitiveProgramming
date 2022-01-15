#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

typedef long long Long;

const Long MAX = INT64_MAX/2;

struct Room;
struct Ladder;

struct Room {
    int r, c;
    Long health;
    Ladder* ladder;
};

struct Ladder {
    Room* src, *dst;
    Long heal;
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);

        std::vector<Long> fire(n+1);
        std::vector<Ladder> ladders(k);
        std::vector<Room> rooms(2*k+2);
        std::vector<std::vector<Room*>> floors(n+1);

        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &fire[i]);
        }

        for (int i = 0; i < k; ++i) {
            int sr, sc, dr, dc;
            Long heal;
            scanf("%d %d %d %d %lld", &sr, &sc, &dr, &dc, &heal);
            rooms[2*i] = { sr, sc, MAX, &ladders[i] };
            rooms[2*i+1] = { dr, dc, MAX, nullptr };
            ladders[i] = { &rooms[2*i], &rooms[2*i+1], heal };
            floors[sr].push_back(&rooms[2*i]);
            floors[dr].push_back(&rooms[2*i+1]);
        }

        rooms[2*k] = { 1, 1, 0, nullptr };
        floors[1].push_back(&rooms[2*k]);
        rooms[2*k+1] = { n, m, MAX, nullptr };
        floors[n].push_back(&rooms[2*k+1]);

        for (int i = 1; i <= n; ++i) {
            std::sort(floors[i].begin(), floors[i].end(), [](Room* r1, Room* r2) -> bool {
                if (r1->c != r2->c) {
                    return r1->c < r2->c;
                }
                return r1->health < r2->health;
            });

            for (int j = 0; j < int(floors[i].size())-1; ++j) {
                Room* r1 = floors[i][j];
                Room* r2 = floors[i][j+1];
                if (r1->health != MAX) {
                    r2->health = std::min(r2->health, r1->health + fire[i]*std::abs(r1->c-r2->c));
                }
            }
            for (int j = int(floors[i].size())-1; j > 0; --j) {
                Room* r1 = floors[i][j-1];
                Room* r2 = floors[i][j];
                if (r2->health != MAX) {
                    r1->health = std::min(r1->health, r2->health + fire[i]*std::abs(r1->c-r2->c));
                }
            }

            for (Room* src : floors[i]) {
                if (src->health != MAX && src->ladder) {
                    auto dst = src->ladder->dst;
                    dst->health = std::min(dst->health, src->health - src->ladder->heal);
                }
            }
        }

        if (rooms.back().health == MAX) {
            printf("NO ESCAPE\n");
        } else {
            printf("%lld\n", rooms.back().health);
        }
    }

    return 0;
}