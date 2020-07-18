#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main()
{
    std::vector<int> mult, div, pow;

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        char kind;
        int coef;
        scanf(" %c %d", &kind, &coef);
        if (kind == '*')
            mult.push_back(coef);
        else if (kind == '/')
            div.push_back(coef);
        else if (kind == '^')
            pow.push_back(coef);
    }

    std::sort(mult.begin(), mult.end());
    std::sort(div.begin(), div.end());
    std::sort(pow.begin(), pow.end());

    int count = 0;
    if ((int)mult.size() > 2)
        ++count;
    if ((int)pow.size() > 2)
        ++count;

    for (int i = 0; i < (int)mult.size(); ++i)
    {
        if (mult[i] == 0)
            continue;
        
        if (mult[i] > 0)
        {
            auto posIt = std::upper_bound(div.begin(), div.end(), 0);
            int posCount = posIt - 
        }
    }

    return 0;
}