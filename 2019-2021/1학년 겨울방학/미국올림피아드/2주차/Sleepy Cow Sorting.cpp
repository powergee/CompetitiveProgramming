#include <iostream>
#include <vector>

int main()
{
    int n;
    scanf("%d", &n);
    std::vector<int> vec(n);

    for (int i = 0; i < n; ++i)
        scanf("%d", &vec[i]);

    int rightLen = 1;
    for (int i = n - 1; i > 0; --i)
    {
        if (vec[i - 1] < vec[i])
            ++rightLen;
        else break;
    }

    printf("%d", n - rightLen);

    return 0;
}