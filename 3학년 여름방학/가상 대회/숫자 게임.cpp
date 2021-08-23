#include <iostream>

int main() {
    int n;
    scanf("%d", &n);

    std::pair<int, int> answer = { -1, 0 };
    for (int i = 0; i < n; ++i) {
        int arr[5];
        for (int j = 0; j < 5; ++j) {
            scanf("%d", arr+j);
        }
        int maxSum = 0;
        for (int j = 0; j < 5; ++j) {
            for (int k = j+1; k < 5; ++k) {
                for (int l = k+1; l < 5; ++l) {
                    maxSum = std::max(maxSum, (arr[j]+arr[k]+arr[l]) % 10);
                }
            }
        }
        answer = std::max(answer, std::make_pair(maxSum, i+1));
    }

    printf("%d", answer.second);

    return 0;
}