#include <iostream>
#include <algorithm>

int arr[100000];
int count[100000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
            arr[i] %= m;
            count[arr[i]] += 1;
        }

        int answer = 0;
        if (m % 2 == 0) {
            if (count[0]) {
                answer += 1;
            }
            if (count[m/2]) {
                answer += 1;
            }
        } else if (m % 2 == 1 && count[0]) {
            answer += 1;
        }

        for (int i = 1; i <= (m-1)/2; ++i) {
            int min = std::min(count[i], count[m-i]);
            int spare = std::max(count[i], count[m-i]) - min;
            if (min) {
                answer += 1;
            }
            if (spare) {
                answer += spare - (min ? 1 : 0);
            }
        }

        printf("%d\n", answer);

        std::fill(count, count + m, 0);
    }

    return 0;
}