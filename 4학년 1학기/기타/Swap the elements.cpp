#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> arr(n);
    std::map<int, int> count;
    std::map<int, std::vector<int>> valuePos;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
        count[arr[i]]++;
        valuePos[arr[i]].push_back(i);
    }

    std::vector<std::pair<int, int>> countPair(count.begin(), count.end());
    std::sort(countPair.begin(), countPair.end(), [](std::pair<int, int> p1, std::pair<int, int> p2) { return p1.second > p2.second; });
    countPair.push_back(countPair.front());

    std::queue<int> usable;
    for (int c = 0; c < countPair[0].second; ++c) {
        usable.push(countPair[0].first);
    }

    bool possible = true;
    for (int i = 1; i < countPair.size(); ++i) {
        while (usable.size() && usable.front() == countPair[i].first) {
            usable.pop();
        }

        if (usable.size() < countPair[i].second) {
            possible = false;
            break;
        }

        for (int pos : valuePos[countPair[i].first]) {
            arr[pos] = usable.front();
            usable.pop();
            usable.push(countPair[i].first);
        }
    }

    if (possible) {
        for (int i = 0; i < n; ++i) {
            printf("%d ", arr[i]);
        }
    } else {
        printf("-1");
    }

    return 0;
}