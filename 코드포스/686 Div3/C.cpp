#include <iostream>
#include <algorithm>

int segLength[200001];
int lastIndex[200001];
int arr[200001];

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n, answer = 1e9;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", arr+i);
            segLength[arr[i]] += (i - lastIndex[arr[i]] == 1 ? 0 : 1);
            lastIndex[arr[i]] = i;
        }

        for (int i = 1; i <= n; ++i)
        {
            if (lastIndex[arr[i]] < n)
                ++segLength[arr[i]];
            answer = std::min(answer, segLength[arr[i]]);
        }
        printf("%d\n", answer);

        for (int i = 1; i <= n; ++i)
        {
            segLength[arr[i]] = 0;
            lastIndex[arr[i]] = 0;
        }
    }
    
    return 0;
}