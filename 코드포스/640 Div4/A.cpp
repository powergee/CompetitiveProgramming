#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> answer;
        int exp = 1;
        while (n) {
            int curr = n % 10;
            if (curr) {
                answer.push_back(curr*exp);
            }
            exp *= 10;
            n /= 10;
        }

        printf("%d\n", (int)answer.size());
        for (int v : answer) {
            printf("%d ", v);
        }
        printf("\n");
    }

    return 0;
}