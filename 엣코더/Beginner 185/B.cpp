#include <iostream>
#include <vector>

int main()
{
    int n, m, t;
    scanf("%d %d %d", &n, &m, &t);

    std::vector<int> time;

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        time.push_back(a);
        time.push_back(b);
    }
    time.push_back(t);

    int current = 0;
    int battery = n;
    bool outside = true;
    bool yes = true;
    for (int t : time)
    {
        if (outside)
            battery -= (t - current);
        else
            battery += (t - current);

        if (battery > n)
            battery = n;

        current = t;
        outside = !outside;
        
        if (battery <= 0)
        {
            yes = false;
            break;
        }
    }

    if (yes)
        printf("Yes");
    else printf("No");
}