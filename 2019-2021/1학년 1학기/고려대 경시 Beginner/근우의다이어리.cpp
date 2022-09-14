#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int goal;
    scanf("%d", &goal);

    if (goal == 0)
    {
        printf("1");
        return 0;
    }

    int need = 1;
    int first = (pow(10, need) - 1) / 9;
    while (!(first <= goal && 10 * first >= goal))
    {
        ++need;
        first = (pow(10, need) - 1) / 9;
    }

    printf("%d", need);
}