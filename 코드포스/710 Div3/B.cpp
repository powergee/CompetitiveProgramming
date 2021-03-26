#include <iostream>
#include <cstring>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        char str[51];
        scanf("%d %d", &n, &k);
        scanf("%s", str);

        std::vector<int> pos;
        for (int i = 0; i < n; ++i) {
            if (str[i] == '*') {
                pos.push_back(i);
            }
        }

        int count = 1;
        int last = pos[0];
        for (int i = 1; i < (int)pos.size(); ++i) {
            if (pos[i] - last > k) {
                ++count;
                last = pos[i-1];
            }
        }

        if (last != pos.back()) {
            ++count;
        }

        printf("%d\n", count);
    }
}