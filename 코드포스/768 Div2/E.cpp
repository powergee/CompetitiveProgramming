#include <iostream>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> arr(n), maxIdx(n+1, -1);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
        maxIdx[arr[i]] = i;
    }

    int answer = 0, currCoverage = 0, maxCoverage = 0;
    for (int i = 0; i < n; ++i) {
        maxCoverage = std::max(maxCoverage, maxIdx[arr[i]]);
        if (i < currCoverage) {
            ++answer;
        } else {
            currCoverage = maxCoverage;
        }
    }
    printf("%d", answer);
    
    return 0;
}