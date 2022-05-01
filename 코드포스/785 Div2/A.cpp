#include <iostream>
#include <cstring>

char line[200001];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%s", line);
        int n = strlen(line);
        if (n % 2 == 0) {
            int sum = 0;
            for (int i = 0; i < n; ++i) {
                sum += (line[i]-'a'+1);
            }
            printf("Alice %d\n", sum);
        } else {
            int sum = 0;
            for (int i = 0; i < n; ++i) {
                sum += (line[i]-'a'+1);
            }
            int smaller = std::min(line[0], line[n-1])-'a'+1;
            int alice = sum-smaller;
            int bob = smaller;
            if (alice < bob) {
                printf("Bob %d\n", bob-alice);
            } else {
                printf("Alice %d\n", alice-bob);
            }
        }
    }

    return 0;
}