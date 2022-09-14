#include <iostream>
#include <set>
#include <functional>

std::pair<char, int> GetCommand()
{
    char comm = ' ';
    while (isspace(comm = getchar()));
    int num;
    scanf("%d", &num);
    return {comm, num};
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        std::multiset<int> minQ;
        int k;
        scanf("%d", &k);

        while (k--)
        {
            auto line = GetCommand();
            if (line.first == 'I')
            {
                minQ.insert(line.second);
            }
            else if (!minQ.empty())
            {
                std::multiset<int>::iterator toRemove;
                if (line.second == 1)
                    toRemove = std::prev(minQ.end());
                else if (line.second == -1)
                    toRemove = minQ.begin();
                minQ.erase(toRemove);
            }
        }

        if (minQ.empty())
            printf("EMPTY\n");
        else printf("%d %d\n", *std::prev(minQ.end()), *minQ.begin());
    }

    return 0;
}