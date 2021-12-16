#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
#include <iostream>
#include <set>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::set<int> need;
        std::vector<int> exist;
        for (int i = 0; i < n; ++i) {
            need.insert(i+1);
        }
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            if (need.find(val) != need.end()) {
                need.erase(val);
            } else {
                exist.push_back(val);
            }
        }

        std::sort(exist.begin(), exist.end(), std::greater<int>());
        int count = 0;
        while (!exist.empty()) {
            if (2*(*need.begin())+1 <= exist.back()) {
                count++;
                need.erase(need.begin());
                exist.pop_back();
            } else {
                count = -1;
                break;
            }
        }

        printf("%d\n", count);
    }
}
