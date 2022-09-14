#include <iostream>
#include <numeric>

typedef long long Long;

int arr[500000];

int main() {
    int n, x;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }

    Long sum = 0;
    int count = 0;
    scanf("%d", &x);

    for (int i = 0; i < n; ++i) {
        int gcd = std::gcd(x, arr[i]);
        if (gcd == 1) {
            sum += arr[i];
            ++count;
        }
    }

    printf("%.10lf", (double)sum / count);
}