#include <iostream>
#include <algorithm>

int n, m;
int arr[8];
int answer[8];
bool used[8];

void PrintAll(int start)
{
    if (start >= m)
    {
        for (int i = 0; i < m; ++i)
            printf("%d ", answer[i]);
        printf("\n");
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        if (!used[i])
        {
            used[i] = true;
            answer[start] = arr[i];
            PrintAll(start + 1);
            used[i] = false;
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i);
        
    std::sort(arr, arr + n);
    PrintAll(0);
    return 0;
}