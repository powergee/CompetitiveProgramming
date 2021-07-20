#include <iostream>
#include <algorithm>
#include <limits>

const int undefined = std::numeric_limits<int>::min();

int n1, n2;
char dna1[1001], dna2[1001];
int dp[1001][1001];
std::pair<int, int> next[1001][1001];

int getMaxScore(int s1, int s2) {
    if (dp[s1][s2] != undefined) {
        return dp[s1][s2];
    }
    if (s1 == n1 || s2 == n2) {
        next[s1][s2] = {undefined, undefined};
        return dp[s1][s2] = 0;
    }

    dp[s1][s2] = (dna1[s1] == dna2[s2] ? 3 : -2) + getMaxScore(s1+1, s2+1);
    next[s1][s2] = {s1+1, s2+1};

    if (dp[s1][s2] < getMaxScore(s1+1, s2) - 2) {
        dp[s1][s2] = getMaxScore(s1+1, s2) - 2;
        next[s1][s2] = {s1+1, s2};
    }

    if (dp[s1][s2] < getMaxScore(s1, s2+1) - 2) {
        dp[s1][s2] = getMaxScore(s1, s2+1) - 2;
        next[s1][s2] = {s1, s2+1};
    }

    if (dp[s1][s2] < (dna1[s1] == dna2[s2] ? 3 : -2)) {
        dp[s1][s2] = (dna1[s1] == dna2[s2] ? 3 : -2);
        next[s1][s2] = {undefined, undefined};
    }

    return dp[s1][s2];
}

int main() {
    scanf("%d", &n1);
    scanf("%s", dna1);
    scanf("%d", &n2);
    scanf("%s", dna2);

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), undefined);

    int answer = undefined;
    int s1, s2, e1, e2;
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            int curr = getMaxScore(i, j);
            if (answer < curr) {
                answer = curr;
                s1 = i, s2 = j;
            }
        }
    }

    printf("%d\n", answer);
    for (e1 = s1, e2 = s2; next[e1][e2].first != undefined; std::tie(e1, e2) = next[e1][e2]);
    for (int i = s1; i <= e1; ++i) {
        putchar(dna1[i]);
    }
    putchar('\n');
    for (int i = s2; i <= e2; ++i) {
        putchar(dna2[i]);
    }

    return 0;
}