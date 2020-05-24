#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    queue<int> alive;
    queue<int> dead;
    
    for (int i = 1; i <= n; ++i)
    {
        alive.push(i);
    }

    for (int i = 1; !alive.empty(); ++i)
    {
        int num = alive.front();
        alive.pop();

        if (i % k == 0)
        {
            dead.push(num);
        }
        else
        {
            alive.push(num);
        }
    }

    printf("<");
    while (true)
    {
        int num = dead.front();
        dead.pop();
        printf("%d", num);
        
        if (dead.empty())
            break;
        else printf(", ");
    }
    printf(">");

    return 0;
}