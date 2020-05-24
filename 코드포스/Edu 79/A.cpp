#include <iostream>
#include <algorithm>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int colors[3];
        scanf("%d %d %d", colors, colors + 1, colors + 2);

        std::sort(colors, colors + 3);

        if (colors[2] - 1 > colors[1] + colors[0])
            printf("No\n");
        else printf("Yes\n");
    }
}