#include <iostream>
#include <set>

int arr[100000];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d", arr + i);
        std::set<int> nums;
        for (int i = 0; i < n; ++i)
            nums.insert(arr[i]);

        printf("%d\n", (int)nums.size());
    }

    return 0;
}