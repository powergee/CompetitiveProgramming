#include <iostream>
#include <unordered_map>

int n, q;
int arr[5001];
int sub[5001][5001];
long long subSum[5001][5001];

int main() {
    scanf("%d %d", &n, &q);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", arr+i);
    }

    for (int i = 1; i <= n; ++i) {
        std::unordered_map<int, int> count;
        for (int j = i+2; j <= n; ++j) {
            count[arr[j-1]] += 1;
            if (count.find(-arr[i]-arr[j]) != count.end()) {
                sub[i][j] = count[-arr[i]-arr[j]];
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            subSum[i][j] = subSum[i][j-1] + subSum[i-1][j] - subSum[i-1][j-1] + sub[i][j];
        }
    }

    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%lld\n", subSum[r][r] - subSum[l-1][r] - subSum[r][l-1] + subSum[l-1][l-1]);
    }

    return 0;
}