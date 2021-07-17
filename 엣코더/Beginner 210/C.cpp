#include <iostream>
#include <map>

int arr[300000];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int currScore = 0;
    int maxScore = 0;
    std::map<int, int> count;

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }
    for (int i = 0; i < k; ++i) {
        count[arr[i]]++;
        if (count[arr[i]] == 1) {
            currScore++;
        }
    }
    maxScore = currScore;

    for (int i = k; i < n; ++i) {
        count[arr[i-k]]--;
        if (count[arr[i-k]] == 0) {
            currScore--;
        }

        count[arr[i]]++;
        if (count[arr[i]] == 1) {
            currScore++;
        }
        maxScore = std::max(maxScore, currScore);
    }

    printf("%d", maxScore);
}