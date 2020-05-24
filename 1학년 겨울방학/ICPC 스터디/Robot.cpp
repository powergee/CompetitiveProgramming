#include <iostream>
#include <string>

enum Direction {East = 0, West = 1, North = 2, South = 3};
std::pair<int, int> dirs[4] {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int M, n, arg;
    std::string comm;
    std::pair<int, int> pos(0, 0);
    std::pair<int, int>* dir = dirs + East;
    std::cin >> M >> n;

    bool valid = true;
    while (n--)
    {
        std::cin >> comm >> arg;
        
        if (comm == "MOVE")
        {
            pos.first = pos.first + dir->first * arg;
            pos.second = pos.second + dir->second * arg;

            if (pos.first < 0 || M < pos.first || pos.second < 0 || M < pos.second)
            {
                valid = false;
                break;
            }
        }
        else
        {
            switch (dir - dirs)
            {
            case North:
                if (arg) dir = dirs + East;
                else dir = dirs + West;
                break;

            case South:
                if (arg) dir = dirs + West;
                else dir = dirs + East;
                break;

            case East:
                if (arg) dir = dirs + South;
                else dir = dirs + North;
                break;

            case West:
                if (arg) dir = dirs + North;
                else dir = dirs + South;
                break;
            }
        }
    }

    if (valid)
        printf("%d %d", pos.first, pos.second);
    else printf("-1");

    return 0;
}