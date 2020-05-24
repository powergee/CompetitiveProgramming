#include <iostream>
#include <algorithm>

int n;
int guessed[100];
std::pair<int, int> swaps[100];

int GetPoint(int pePos)
{
    int points = 0;
    for (int i = 0; i < n; ++i)
    {
        if (swaps[i].first == pePos)
            pePos = swaps[i].second;
        else if (swaps[i].second == pePos)
            pePos = swaps[i].first;

        if (pePos == guessed[i])
            ++points;
    }

    return points;
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d %d %d", &swaps[i].first, &swaps[i].second, &guessed[i]);
    
    printf("%d", std::max(GetPoint(1), std::max(GetPoint(2), GetPoint(3))));

    return 0;
}