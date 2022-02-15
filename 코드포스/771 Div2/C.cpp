#include <iostream>
#include <vector>
#include <queue>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }

        std::priority_queue<int, std::vector<int>, std::greater<int>> comps;
        for (int i = n-1; i >= 0; --i) {
            int rep = arr[i];
            while (!comps.empty() && comps.top() < arr[i]) {
                rep = std::min(rep, comps.top());
                comps.pop();
            }
            comps.push(rep);
        }
        printf("%d\n", int(comps.size()));
    }

    return 0;
}