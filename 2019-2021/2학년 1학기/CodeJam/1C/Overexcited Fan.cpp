#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

void Judge(int x, int y, int limit, int& minTime)
{
    int time = abs(x) + abs(y);
    if (time <= limit)
        minTime = std::min(minTime, std::max(time, limit));
}

void Move(char dir, int& x, int& y)
{
    switch (dir)
    {
    case 'N':
        ++y;
        break;

    case 'S':
        --y;
        break;

    case 'E':
        ++x;
        break;

    case 'W':
        --x;
        break;

    default:
        break;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    for (int c = 1; c <= T; ++c)
    {
        std::cout << "Case #" << c << ": ";
        std::string input;
        int x, y;
        int minTime = 987654321;
        int currTime = 0;
        std::cin >> x >> y >> input;

        for (char dir : input)
        {
            Judge(x, y, currTime, minTime);
            Move(dir, x, y);
            ++currTime;
        }
        Judge(x, y, currTime, minTime);

        if (minTime == 987654321)
            std::cout << "IMPOSSIBLE\n";
        else std::cout << minTime << "\n";
    }
}