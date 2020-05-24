#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

int main()
{
    int N;
    std::vector<std::pair<int, int>> lines;

    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        lines.push_back(std::make_pair(std::min(a, b), std::max(a, b)));
    }

    std::sort(lines.begin(), lines.end());

    std::pair<int, int> current = lines[0];
    int length = current.second - current.first;

    for (int i = 1; i < N; ++i)
    {
        if (current.second >= lines[i].second)
            continue;
        
        else if (current.second >= lines[i].first && current.second <= lines[i].second)
        {
            length += lines[i].second - current.second;
            current.second = lines[i].second;
        }

        else if (current.second < lines[i].first && current.second <= lines[i].second)
        {
            length += lines[i].second - lines[i].first;
            current = lines[i];
        }
    }

    printf("%d", length);

    return 0;
}