#include <iostream>
#include <set>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::set<int> added;
        int count = 0;
        while (n > 0) {
            bool found = false;
            int temp;

            for (auto it = added.rbegin(); it != added.rend() && !found; ++it) {
                if (*it + 2 <= n) {
                    temp = *it+2;
                    found = true;
                } else if (*it + 1 <= n) {
                    temp = *it+1;
                    found = true;
                }
            }

            if (!found) {
                temp = 1;
            }

            added.insert(temp);
            ++count;
            n -= temp;
        }

        printf("%d\n", count);
    }

    return 0;
}