#include <iostream>
#include <algorithm>
#include <map>

int n, k;
std::map<int, int> andCache[10001];
std::map<int, int> orCache[10001];
int numbers[10001];

int getAnd(int i, int j) {
    if (andCache[i].find(j) != andCache[i].end()) {
        return andCache[i][j];
    }
    printf("and %d %d\n", i, j);
    fflush(stdout);
    int res;
    scanf("%d", &res);
    return andCache[i][j] = res;
}

int getOr(int i, int j) {
    if (orCache[i].find(j) != orCache[i].end()) {
        return orCache[i][j];
    }
    printf("or %d %d\n", i, j);
    fflush(stdout);
    int res;
    scanf("%d", &res);
    return orCache[i][j] = res;
}

int main() {
    scanf("%d %d", &n, &k);

    // first 3 numbers
    int k1 = getAnd(1, 2) + getOr(1, 2);
    int k2 = getAnd(2, 3) + getOr(2, 3);
    int k3 = getAnd(3, 1) + getOr(3, 1);
    numbers[1] = (k1-k2+k3)/2;
    numbers[2] = (k1+k2-k3)/2;
    numbers[3] = (-k1+k2+k3)/2;
    
    for (int i = 4; i <= n; ++i) {
        int sum = getAnd(i-1, i) + getOr(i-1, i);
        numbers[i] = sum - numbers[i-1];
    }

    std::sort(numbers+1, numbers+1+n);
    printf("finish %d\n", numbers[k]);

    return 0;
}