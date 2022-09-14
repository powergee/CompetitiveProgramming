#include <iostream>

int main()
{
    int n;
    int arr[1000];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", arr+i);
    
    bool isPalin = true;
    for (int i = 0; i < n/2 && isPalin; ++i)
        if (arr[i] != arr[n-1-i])
            isPalin = false;
    
    if (isPalin)
    {
        bool increasing = arr[0] < arr[1];
        bool isMixed = arr[0] == arr[1];
        for (int i = 1; i < (n % 2 == 0 ? n/2-1 : n/2) && !isMixed; ++i)
            if (increasing && arr[i] >= arr[i+1] ||
                !increasing && arr[i] <= arr[i+1])
                isMixed = true;
            
        if (isMixed)
            printf("3");
        else if (increasing)
            printf("1");
        else
            printf("2");
    }
    else
        printf("D");

    return 0;
}