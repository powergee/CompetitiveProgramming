#include <iostream>
#include <algorithm>

int main() {
    int h, w;
    int arr[500];
    scanf("%d %d", &h, &w);

    for (int i = 0; i < w; ++i) {
        scanf("%d", arr+i);
    }

    int answer = 0;
    for (int i = 0; i < w; ++i) {
        int j = std::max_element(arr+i+1, arr+w) - arr;
        int goal = std::min(arr[i], arr[j]);
        for (int k = i+1; k <= j; ++k) {
            if (arr[k] > goal) {
                break;
            }
            answer += goal-arr[k];
            arr[k] = goal;
        }
    }

    printf("%d", answer);

    return 0;
}