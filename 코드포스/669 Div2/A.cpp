#include <iostream>

int arr[1000];
int oneCount = 0;

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);
        oneCount = 0;

        for (int i = 0; i < n; ++i)
        {
            scanf("%d", arr+i);
            if (arr[i])
                ++oneCount;
        }

        if (oneCount <= n/2)
        {
            int count = (n-oneCount);
            printf("%d\n", count);
            for (int i = 0; i < count; ++i)
                printf("0 ");
            printf("\n");
        }
        else
        {
            int count = oneCount % 2 ? oneCount-1 : oneCount;
            printf("%d\n", count);
            for (int i = 0; i < count; ++i)
                printf("1 ");
            printf("\n");
        }
    }
}