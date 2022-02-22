#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        if (n == 3) {
            printf("3 2 1\n");
            printf("1 3 2\n");
            printf("3 1 2\n");
        } else {
            std::vector<int> origin(n);
            for (int i = 0; i < n; ++i) {
                origin[i] = i+1;
            }
            std::swap(origin[1], origin[2]);
            
            auto printSingleAnswer = [&](int start) {
                for (int i = start; i < n; ++i) {
                    printf("%d ", origin[i]);
                }
                for (int i = 0; i < start; ++i) {
                    printf("%d ", origin[i]);
                }
                printf("\n");
            };

            for (int i = 0; i < n; ++i) {
                printSingleAnswer(i);
            }
        }
    }

    return 0;
}