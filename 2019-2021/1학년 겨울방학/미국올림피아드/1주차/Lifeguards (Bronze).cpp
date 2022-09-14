#include <iostream>
#include <algorithm>

typedef std::pair<int, int> Range;

int N;
Range shifts[100];

int CalcTime(int ignore)
{
    Range curr = {-1, -1};
    int time = 0;

    for (int i = 0; i < N; ++i)
    {
        if (i == ignore)
            continue;

        if (curr.second < shifts[i].first)
        {
            curr = shifts[i];
            time += shifts[i].second - shifts[i].first;
        }
        else
        {
            time += shifts[i].second - curr.second;
            curr.second = shifts[i].second;
        }
    }

    return time;
}

int main()
{
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
        scanf("%d %d", &shifts[i].first, &shifts[i].second);

    std::sort(shifts, shifts + N);

    int maxTime = -1;
    for (int i = 0; i < N; ++i)
        maxTime = std::max(maxTime, CalcTime(i));

    printf("%d", maxTime);

    return 0;
}