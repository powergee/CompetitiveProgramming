#include <iostream>

using Long = long long;

int n;
Long s;
Long arr[100000];
Long sum[100000];

bool isPossible(int length) {
    Long sub = 0;
    for (int i = 0; i < length; ++i) {
        sub += arr[i];
        if (s <= sub) {
            return true;
        }
    }

    for (int i = 1; i <= n-length; ++i) {
        sub -= arr[i-1];
        sub += arr[i+length-1];
        if (s <= sub) {
            return true;
        }
    }

    return false;
}

int main() {
    scanf("%d %lld", &n, &s);

    for (int i = 0; i < n; ++i) {
        scanf("%lld", arr+i);
    }

    sum[0] = arr[0];
    for (int i = 1; i < n; ++i) {
        sum[i] = sum[i-1] + arr[i];
    }

    int l = 1, r = n;
    while (l < r) {
        int m = (l+r)/2;
        if (isPossible(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    if (isPossible(l)) {
        printf("%d", l);
    } else {
        printf("0");
    }

    return 0;
}