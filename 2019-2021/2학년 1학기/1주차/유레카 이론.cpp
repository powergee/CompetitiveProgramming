#include <iostream>

int GetTri(int n)
{
    return (n * (n + 1)) / 2;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int k;
        scanf("%d", &k);

        bool success = false;
        for (int i = 1; GetTri(i) < k && !success; ++i)
            for (int j = 1; GetTri(j) < k && !success; ++j)
                for (int l = 1; GetTri(l) < k && !success; ++l)
                    if (GetTri(i) + GetTri(j) + GetTri(l) == k)
                        success = true;
        
        if (success)
            printf("1\n");
        else printf("0\n");
    }

    return 0;
}