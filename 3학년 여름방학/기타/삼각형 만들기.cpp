#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> lenVec;

    for (int i = 0; i < n; ++i) {
        int length;
        scanf("%d", &length);
        lenVec.push_back(length);
    }
    std::sort(lenVec.begin(), lenVec.end());

    for (int i = n-1; i >= 2; --i) {
        if (lenVec[i] < lenVec[i-1] + lenVec[i-2]) {
            printf("%d", lenVec[i] + lenVec[i-1] + lenVec[i-2]);
            return 0;
        }
    }

    printf("-1");
    return 0;
}