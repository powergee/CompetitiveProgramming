#include <iostream>
#include <algorithm>

int n;
int arr[5000];
int palinDP[5000][5000];
int countDP[5000];

bool isPalin(int left, int right) {
    if (right < left) {
        return true;
    }

    int& result = palinDP[left][right];
    if (result != -1) {
        return result == 1;
    }

    if (arr[left] == arr[right] && isPalin(left+1, right-1)) {
        result = 1;
    } else {
        result = 0;
    }

    return result == 1;
}

int countPalin(int start) {
    if (start == n) {
        return 0;
    }

    int& result = countDP[start];
    if (result != -2) {
        return result;
    }

    result = -1;
    for (int i = start + 1; i < n; i += 2) {
        if (isPalin(start, i) && countPalin(i+1) != -1) {
            result = std::max(result, countPalin(i+1) + 1);
        }
    }

    return result;
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
        countDP[i] = -2;
        for (int j = 0; j < n; ++j) {
            palinDP[i][j] = -1;
        }
    }

    printf("%d", countPalin(0));

    return 0;
}