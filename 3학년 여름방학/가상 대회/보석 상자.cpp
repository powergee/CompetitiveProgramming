#include <iostream>
#include <map>

int n, m;
int count[300000];

bool isValid(long long maxJeal) {
    long long received = 0;
    for (int i = 0; i < m; ++i) {
        received += (count[i] / maxJeal) + ((count[i] % maxJeal) ? 1 : 0);
    }
    return received <= n;
}

int main() {
    scanf("%d %d", &n, &m);

    long long sum = 0;
    for (int i = 0; i < m; ++i) {
        int color;
        scanf("%d", &color);
        count[i] = color;
        sum += color;
    }

    long long left = 1, right = sum;
    while (left < right) {
        long long med = (left+right)/2;
        if (isValid(med)) {
            right = med;
        } else {
            left = med+1;
        }
    }

    printf("%lld", left);

    return 0;
}