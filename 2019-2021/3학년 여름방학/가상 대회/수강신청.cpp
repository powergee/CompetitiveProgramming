#include <iostream>
#include <map>
#include <algorithm>

int main() {
    int k, l;
    scanf("%d %d", &k, &l);

    std::map<int, int> appeared;

    for (int i = 0; i < l; ++i) {
        int num;
        scanf("%d", &num);
        appeared[num] = i;
    }

    std::vector<std::pair<int, int>> q(appeared.begin(), appeared.end());
    std::sort(q.begin(), q.end(), [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) -> bool {
        return p1.second < p2.second;
    });

    int printed = 0;
    for (auto w : q) {
        printf("%08d\n", w.first);
        ++printed;
        if (printed >= k) {
            break;
        }
    }

    return 0;
}