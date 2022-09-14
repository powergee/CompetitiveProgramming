#include <iostream>
#include <queue>
#include <set>
#include <functional>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m, index = 1;
        std::queue<std::pair<int, int>> q;
        std::multiset<int, std::greater<int>> docSet;
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; ++i) {
            int doc;
            scanf("%d", &doc);
            q.emplace(doc, i);
            docSet.insert(doc);
        }

        while (!q.empty()) {
            auto front = q.front();
            q.pop();
            auto need = docSet.begin();
            
            if (front.first < *need) {
                q.push(front);
            } else {
                docSet.erase(need);
                if (front.second == m) {
                    printf("%d\n", index);
                    break;
                }
                ++index;
            }
        }
    }

    return 0;
}