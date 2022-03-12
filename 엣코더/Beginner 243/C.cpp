#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

struct Person {
    int x, y;
    char dir;
};

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Person> people(n);
    std::map<int, std::vector<Person*>> coord;
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        people[i] = { x, y, '\0' };
        coord[y].push_back(&people[i]);
    }

    char dirs[n+1];
    scanf("%s", dirs);
    for (int i = 0; i < n; ++i) {
        people[i].dir = dirs[i];
    }

    bool yes = false;
    for (auto& [y, xs] : coord) {
        std::sort(xs.begin(), xs.end(), [](Person* p1, Person* p2) -> bool {
            return p1->x < p2->x;
        });
        for (int i = 0; i+1 < xs.size(); ++i) {
            if (xs[i]->dir == 'R' && xs[i+1]->dir == 'L') {
                yes = true;
            }
        }
    }

    if (yes) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}