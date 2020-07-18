#include <iostream>
#include <stack>
#include <algorithm>

typedef long long Long;

Long hist[100000];

int main()
{
    while (true)
    {
        int n;
        scanf("%d", &n);
        if (n == 0)
            break;
        
        for (int i = 0; i < n; ++i)
            scanf("%lld", hist+i);
        
        std::stack<std::pair<Long, int>> s;
        Long result = 0;
        s.emplace(hist[0], 0);
        for (int i = 1; i < n; ++i)
        {
            while (!s.empty() && hist[i] < s.top().first)
            {
                std::pair<Long, int> prev = s.top();
                s.pop();
                Long height = prev.first;
                int width = (s.empty() ? i : i-s.top().second-1);
                result = std::max(width * height, result);
            }

            s.emplace(hist[i], i);
        }

        while (!s.empty())
        {
            std::pair<Long, int> prev = s.top();
            s.pop();
            Long height = prev.first;
            int width = (s.empty() ? n : n-s.top().second-1);
            result = std::max(width * height, result);
        }
        
        printf("%lld\n", result);
    }

    return 0;
}