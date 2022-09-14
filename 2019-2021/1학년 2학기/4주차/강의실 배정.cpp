#include <iostream>
#include <algorithm>
#include <vector>
#define START 1
#define END -1

std::vector<std::pair<int, int>> schedule;

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        int start, end;
        scanf("%d %d", &start, &end);

        schedule.push_back({start, START});
        schedule.push_back({end, END});
    }

    std::sort(schedule.begin(), schedule.end());

    int result = 0;
    int current = 0;
    for (int i = 0; i < N * 2; ++i)
    {
        if (schedule[i].second == START)
            ++current;
        else
            --current;

        if (result < current)
            result = current;
    }

    printf("%d", result);

    return 0;
}