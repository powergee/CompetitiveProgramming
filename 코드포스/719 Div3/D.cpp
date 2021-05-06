#include <iostream>
#include <map>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::map<int, int> count;
        long long answer = 0;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            answer += count[val-i];
            count[val-i]++;
        }

        printf("%lld\n", answer);
    }

    return 0;
}