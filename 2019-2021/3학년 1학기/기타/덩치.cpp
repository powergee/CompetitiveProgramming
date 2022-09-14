#include <iostream>

int main() {
    int n;
    scanf("%d", &n);

    std::pair<int, int> people[50];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &people[i].first, &people[i].second);
    }

    for (int i = 0; i < n; ++i) {
        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (people[i].first < people[j].first && people[i].second < people[j].second) {
                ++count;
            }
        }

        printf("%d ", count + 1);
    }

    return 0;
}