#include <iostream>
#include <cmath>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        int diff = y - x;
        int h = sqrt(diff);
        int remain = diff - h*h;
        int answer = 2*h - 1;

        int sub = h;
        while (remain)
        {
            if (remain >= sub)
            {
                remain -= sub;
                ++answer;
            }
            else
                sub = remain;
        }

        printf("%d\n", answer);
    }

    return 0;
}