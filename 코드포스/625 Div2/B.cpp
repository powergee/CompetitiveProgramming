#include <iostream>
#include <algorithm>
#include <map>

typedef long long Long;

int n;
std::map<int, Long> m;

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int input;
        scanf("%d", &input);
        if (m.find(i - input) == m.end())
            m[i - input] = input;
        else m[i - input] += input;
    }

    Long result = -1;
    for (auto ele : m)
        result = std::max(result, ele.second);

    printf("%lld", result);

    return 0;
}