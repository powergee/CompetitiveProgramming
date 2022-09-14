#include <iostream>

int main()
{
    int X, Y, p1, p2;
    scanf("%d %d %d %d", &X, &Y, &p1, &p2);
    
    bool success = false;
    for (int a = 0; a <= 1<<6; ++a)
    {
        if ((X * a + p1 - p2) >= 0 && (X * a + p1 - p2) % Y == 0)
        {
            printf("%d", p1 + a * X);
            success = true;
            break;
        }
    }

    if (!success)
        printf("-1");

    return 0;
}