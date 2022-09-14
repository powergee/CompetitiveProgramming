#include <iostream>
#include <algorithm>

int cows[3];

int CountMin()
{
    int d1 = cows[1] - cows[0];
    int d2 = cows[2] - cows[1];

    if (d1 == 1 && d2 == 1)
        return 0;
    else if (d1 == 2 || d2 == 2)
        return 1;
    else 
        return 2;
}

int CountMax()
{
    int d1 = cows[1] - cows[0];
    int d2 = cows[2] - cows[1];
    
    if (d1 == 1 && d2 == 1)
        return 0;
    if (d1 < d2)
        return (cows[2] - 1) - cows[1];
    else
        return cows[1] - (cows[0] + 1);
}

int main()
{
    scanf("%d %d %d", cows, cows + 1, cows + 2);
    std::sort(cows, cows + 3);
    printf("%d\n%d", CountMin(), CountMax());

    return 0;
}