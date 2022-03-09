#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::basic_string<int> arr(n, 0);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }

        std::vector<int> answer;
        for (int i = n-1; i >= 0; --i) {
            int need = i+1;
            int targetIdx = arr.find(need);
            if (targetIdx == i) {
                answer.push_back(0);
            } else {
                int actualShift = targetIdx+1;
                answer.push_back(actualShift);
                arr = arr.substr(actualShift, i+1-actualShift) + arr.substr(0, actualShift) + arr.substr(i+1);
            }
        }

        for (auto it = answer.rbegin(); it != answer.rend(); ++it) {
            printf("%d ", *it);
        }
        printf("\n");
    }

    return 0;
}