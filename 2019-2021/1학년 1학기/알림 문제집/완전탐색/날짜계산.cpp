#include <iostream>
using namespace std;

int E, S, M;

int main()
{
    scanf("%d %d %d", &E, &S, &M);

    int x = -1, y = -1, z = -1;

    while (y % 28 != 0 || z % 19 != 0)
    {
        ++x;
        y = 15*x+E-S;
        z = 15*x+E-M;
    }

    printf("%d", 15*x+E);

    return 0;
}