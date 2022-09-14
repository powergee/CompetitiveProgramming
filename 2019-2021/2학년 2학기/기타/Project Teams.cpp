#include <iostream>
#include <algorithm>

int arr[100000];

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < 2*n; ++i)
        scanf("%d", arr+i);
    
    std::sort(arr, arr+2*n);
    int answer = 1e9;
    for (int i = 0; i < n; ++i)
        answer = std::min(answer, arr[i]+arr[2*n-i-1]);
    printf("%d", answer);

    return 0;
}