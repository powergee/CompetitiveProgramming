#include <iostream>

bool checked[31];

int main()
{
    for (int i = 0; i < 28; ++i)
    {
        int num;
        scanf("%d", &num);
        checked[num] = true;
    }

    for (int i = 1; i <= 30; ++i)
        if (!checked[i])
            printf("%d\n", i);

    return 0;
}