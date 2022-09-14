#include <iostream>
#include <algorithm>

int dp[1000001][11];

int countDigits(int val) {
    int count = 0;
    while (val) {
        val /= 10;
        ++count;
    }
    return count;
}

int getDigit(int val, int index) {
    while (index--) {
        val /= 10;
    }
    return val % 10;
}

int get10Pow(int coeff, int exp) {
    int val = coeff;
    while (exp--) {
        val *= 10;
    }
    return val;
}

int changeDigits(int val, int i, int j) {
    int di = getDigit(val, i);
    int dj = getDigit(val, j);

    val -= (get10Pow(di, i) + get10Pow(dj, j));
    val += (get10Pow(di, j) + get10Pow(dj, i));

    return val;
}

int getMax(int val, int swCount) {
    int& result = dp[val][swCount];
    if (result) {
        return result;
    }

    result = -1;
    if (swCount) {
        int count = countDigits(val);

        for (int i = 0; i < count; ++i) {
            for (int j = 0; j < i; ++j) {
                int di = getDigit(val, i);
                int dj = getDigit(val, j);

                if (i != count - 1 || dj != 0) {
                    result = std::max(result, getMax(changeDigits(val, i, j), swCount - 1));
                }
            }
        }
    } else {
        result = val;
    }

    return result;
}

int main() {
    int val, swCount;
    scanf("%d %d", &val, &swCount);

    if (val <= 10 && 1 <= swCount) {
        printf("-1");
    } else {
        printf("%d", getMax(val, swCount));
    }
    return 0;
}