#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, x;
        scanf("%d %d", &n, &x);
        int golds[n];
        bool selected[n] = {false,};

        for (int i = 0; i < n; ++i) {
            scanf("%d", golds+i);
        }

        std::sort(golds, golds+n, std::greater<int>());
        std::vector<int> answer;
        int sum = 0;
        
        for (int i = 0; i < n; ++i) {
            if (sum + golds[i] == x) {
                continue;
            } else {
                sum += golds[i];
                answer.push_back(golds[i]);
                selected[i] = true;
            }
        }

        bool yes = true;;
        for (int i = 0; i < n; ++i) {
            if (!selected[i]) {
                selected[i] = true;
                answer.push_back(golds[i]);
                sum += golds[i];

                if (sum == x) {
                    yes = false;
                    break;
                }
            }
        }

        if (yes) {
            printf("YES\n");
            for (int i = 0; i < n; ++i) {
                printf("%d ", answer[i]);
            }
            printf("\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}