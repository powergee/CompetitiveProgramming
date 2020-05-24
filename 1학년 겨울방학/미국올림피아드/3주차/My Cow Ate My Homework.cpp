#include <iostream>
#include <algorithm>

int min[100000];
int sum[100000];
int arr[100000];

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
        scanf("%d", arr + i);

    bool allSame = true;
    for (int i = 1; i < N && allSame; ++i)
    {
        if (arr[i - 1] != arr[i])
            allSame = false;
    }

    if (allSame)
    {
        for (int k = 1; k < N - 1; ++k)
            printf("%d\n", k);
    }
    else
    {
        min[N - 1] = sum[N - 1] = arr[N - 1];
        for (int i = N - 2; i >= 0; --i)
        {
            min[i] = std::min(min[i + 1], arr[i]);
            sum[i] = arr[i] + sum[i + 1];
        }

        double maxScore = -1;
        int properK = -1;

        for (int k = 1; k < N - 1; ++k)
        {
            double score = (sum[k] - min[k]) / (double)(N - k - 1);
            if (maxScore < score)
            {
                maxScore = score;
                properK = k;
            }
        }

        printf("%d", properK);
    }

    return 0;
}