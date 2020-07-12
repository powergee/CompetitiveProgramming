#include <iostream>
#include <algorithm>

int arr[10000];
int diff[10000];

int main()
{
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t)
    {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
        {
            scanf("%d", arr + i);
            if (i == 0 || arr[i-1] == arr[i])
                diff[i] = 0;
            else if (arr[i-1] < arr[i])
                diff[i] = 1;
            else
                diff[i] = -1;
        }

        int answer = 0;
        int sum = 0;
        int minSum = 0;
        int maxSum = 0;
        for (int i = 1; i < n; ++i)
        {
            sum += diff[i];
            minSum = std::min(minSum, sum);
            maxSum = std::max(maxSum, sum);
            
            if (diff[i-1] == -diff[i] && diff[i] != 0)
            {
                if (diff[i] == 1)
                {
                    sum = 1;
                    minSum = 0;
                    maxSum = 1;
                }
                else if (diff[i] == -1)
                {
                    sum = -1;
                    minSum = -1;
                    maxSum = 0;
                }
            }
            else if (maxSum - minSum == 4)
            {
                ++answer;
                sum = 0;
                minSum = 0;
                maxSum = 0;
            }
        }

        printf("Case #%d: %d\n", t, answer);
    }

    return 0;
}