#include <iostream>
using namespace std;

int main ()
{
    int c, k, p;
    scanf("%d %d %d", &c, &k, &p);

    int sum = 0;
    for (int i = 0; i <= c; ++i)
    {
        sum += k*i+p*i*i;
    }
    printf("%d", sum);
    return 0;
}