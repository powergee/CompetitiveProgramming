#include <iostream>
#include <algorithm>

int a[100000], b[100000];
bool hasOne[100000];
bool hasZero[100000];
bool hasMinus[100000];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d", a + i);
        for (int i = 0; i < n; ++i)
            scanf("%d", b + i);

        hasOne[0] = a[0] == 1;
        hasZero[0] = a[0] == 0;
        hasMinus[0] = a[0] == -1;
        for (int i = 1; i < n; ++i)
        {
            hasOne[i] = a[i] == 1 || hasOne[i-1];
            hasZero[i] = a[i] == 0 || hasZero[i-1];
            hasMinus[i] = a[i] == -1 || hasMinus[i-1];
        }

        bool yes = true;
        
        if (a[0] != b[0])
            yes = false;

        for (int i = n-1; i > 0 && yes; --i)
        {
            int diff = b[i] - a[i];
            if (diff == 0)
                continue;
            else if ((diff > 0 && !hasOne[i - 1]) ||(diff < 0 && !hasMinus[i - 1]))
                yes = false;
        }

        printf("%s\n", yes ? "YES" : "NO");
    }
}