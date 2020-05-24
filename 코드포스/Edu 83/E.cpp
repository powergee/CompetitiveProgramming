#include <iostream>
#include <vector>
#include <list>

typedef std::list<int>::iterator Iter;

std::list<int> arr;

std::vector<std::pair<Iter, bool>> FindTop()
{
    std::vector<std::pair<Iter, bool>> result;
    bool decreasing = false;
    for (Iter it = arr.begin(); it != std::prev(arr.end()); ++it)
    {
        if (*it > *std::next(it))
        {
            if (!decreasing)
            {
                decreasing = true;
                result.emplace_back(it, true);
                for (Iter j = it; j != arr.begin(); --j)
                {
                    if (*j != *std::prev(j))
                    {
                        result.emplace_back(j, false);
                        break;
                    }
                }
            }
        }
        else if (*it < *std::next(it))
            decreasing = false;
    }

    if (!decreasing)
        result.emplace_back(std::prev(arr.end()), false);

    return result;
}

int Merge(Iter start, bool dir)
{
    int count = 0;

    if (!dir)
    {
        for (Iter it = std::prev(start); it != arr.begin() && *it >= *std::prev(it); --it)
        {
            if (*it == *std::prev(it))
            {
                it = std::prev(it);
                arr.erase(std::next(it));
                *it += 1;
                ++count;
            }
        }
    }

    else
    {
        for (Iter it = start; it != std::prev(arr.end()) && *it >= *std::next(it); ++it)
        {
            if (*it == *std::next(it))
            {
                it = std::next(it);
                arr.erase(std::prev(it));
                *it += 1;
                ++count;
            }
        }
    }

    return count;
}


int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int input;
        scanf("%d", &input);
        arr.push_back(input);
    }

    int count = 1;
    while (count)
    {
        count = 0;
        auto tops = FindTop();
        for (auto t : tops)
        {
            printf("%d, %s\n", *t.first, (t.second ? "Right" : "Left"));
            count += Merge(t.first, t.second);
        }
    }

    printf("%d", (int)arr.size());

    return 0;
}