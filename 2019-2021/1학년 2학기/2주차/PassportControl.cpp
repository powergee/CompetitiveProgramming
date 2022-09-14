#include <iostream>
#include <vector>

int main()
{
    int N, K, num;
    std::vector<int> v;
    scanf("%d %d", &N, &K);

    scanf("%d", &num);
    v.push_back(num);
    for (int i = 1; i < N; ++i)
    {
        scanf("%d", &num);
        bool edited = false;

        for (int i = 0; i < v.size(); ++i)
        {
            if (v[i] < num)
            {
                v[i] = num;
                edited = true;
                break;
            }
        }

        if (!edited)
            v.push_back(num);
    }

    if (v.size() <= K)
        printf("YES");
    else printf("NO");

    return 0;
}