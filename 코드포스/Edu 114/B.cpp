#include <iostream>
#include <algorithm>
#include <numeric>
 
int main() {
    int T;
    scanf("%d", &T);
 
    while (T--) {
        int arr[3], m;
        scanf("%d %d %d %d", arr+0, arr+1, arr+2, &m);
        std::sort(arr, arr+3);
 
        int max = std::accumulate(arr, arr+3, 0) - (arr[0] ? 1 : 0) - (arr[1] ? 1 : 0) - (arr[2] ? 1 : 0);
        int min = std::max(arr[2] - (arr[1]+arr[0]) - 1, 0);
 
        if (min <= m && m <= max) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
 
    return 0;
}