#include <iostream>
#include <algorithm>
#include <vector>
#define INF (INT32_MAX/4)
#define UND (INT32_MAX/2)

int n;
int arr[5000];
std::vector<int> people;
int sum[5000];
int dp[5000][5000];

int movePeople(int index, int pCount) {
    if (pCount == 0) {
        return 0;
    }
    if (index == -1) {
        if (pCount) {
            return INF;
        } else {
            return 0;
        }
    }

    int& result = dp[index][pCount];
    if (result != UND) {
        return result;
    }
    
    result = std::min(INF, movePeople(index-1, pCount));
    if (arr[index] == 0) {
        result = std::min(result, movePeople(index-1, pCount-1) + std::abs(index - people[pCount-1]));
    }

    return result;
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
        if (arr[i]) {
            people.push_back(i);
        }
    }

    sum[0] = arr[0];
    for (int i = 1; i < n; ++i) {
        sum[i] = sum[i-1] + arr[i];
    }

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), UND);
    printf("%d", movePeople(n-1, sum[n-1]));

    return 0;
}