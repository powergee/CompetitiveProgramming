#include <iostream>

int main()
{
    long long n;
    scanf("%lld", &n);

    long long left = 1, right = n;
    while (left < right)
    {
        long long mid = (left + right) / 2;
        printf("? %lld\n", mid);
        fflush(stdout);
        int response;
        scanf("%d", &response);

        if (response == 0)
            left = right = mid;
        else if (response > 0)
            right = mid-1;
        else if (response < 0)
            left = mid+1;
    }

    printf("= %lld\n", left);

    return 0;
}