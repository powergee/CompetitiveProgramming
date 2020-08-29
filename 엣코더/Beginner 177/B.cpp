#include <iostream>
#include <algorithm>

int main()
{
    std::string s, t;
    std::cin >> s >> t;

    int minCount = 1e9;
    for (int i = 0; i <= (int)(s.size()-t.size()); ++i)
    {
        int count = 0;
        for (int j = 0; j < (int)t.size(); ++j)
            if (s[i+j] != t[j])
                ++count;
            
        minCount = std::min(minCount, count);
    }

    printf("%d", minCount);

    return 0;
}