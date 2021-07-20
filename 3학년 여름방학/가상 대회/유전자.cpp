#include <iostream>
#include <algorithm>
#include <cstring>

char dna[501];
int dp[500][500];

bool isUnitKoi(char c1, char c2) {
    return (c1 == 'a' && c2 == 't') ||
           (c1 == 'g' && c2 == 'c');
}

int getMaxLength(int left, int right) {
    int& result = dp[left][right];
    if (result != -1) {
        return result;
    }

    if (right <= left) {
        return result = 0;
    }

    result = 0;
    if (isUnitKoi(dna[left], dna[right])) {
        result = std::max(result, 2 + getMaxLength(left+1, right-1));
    }
    for (int mid = left; mid < right; ++mid) {
        result = std::max(result, getMaxLength(left, mid) + getMaxLength(mid+1, right));
    }

    return result;
}

int main() {
    scanf("%s", dna);
    int n = std::strlen(dna);
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), -1);
    printf("%d", getMaxLength(0, n-1));
    return 0;
}