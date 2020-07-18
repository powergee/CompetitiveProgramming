#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main()
{
    std::vector<double> mult, div, pow;

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        char kind;
        double coef;
        scanf(" %c %lf", &kind, &coef);
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

    std::vector<double> multPos, multNeg;
    for (int i = 0; i < (int)mult.size(); ++i)
    {
        if (mult[i] > 0)
            multPos.push_back(mult[i]);
        else if (mult[i] < 0)
            multNeg.push_back(mult[i]);
    }

    std::vector<double> divPos, divNeg;
    for (int i = 0; i < (int)div.size(); ++i)
    {
        if (div[i] > 0)
            divPos.push_back(div[i]);
        else
            divNeg.push_back(div[i]);
    }

    long long count = 0;
    if ((int)mult.size() >= 2)
        ++count;
    if ((int)pow.size() >= 2)
        ++count;

    for (int i = 0; i < (int)div.size(); ++i)
    {
        if (div[i] > 0)
            count += 2*(long long)multPos.size();
        else
            count += 2*(long long)multNeg.size();
    }

    for (int i = 0; i < (int)pow.size(); ++i)
    {
        if (pow[i] == 0)
            count += (long long)div.size();
        else if (pow[i] > 0)
        {
            count += (long long)divPos.size();
            auto bound = std::lower_bound(divNeg.begin(), divNeg.end(), -pow[i] * std::exp(2));
            count += 2*(bound - divNeg.begin());
        }
        else
        {
            count += (long long)divNeg.size();
            auto bound = std::upper_bound(divPos.begin(), divPos.end(), -pow[i] * std::exp(2));
            count += 2*(divPos.end() - bound);
        }
    }

    for (int i = 0; i < (int)pow.size(); ++i)
    {
        if (pow[i] == 0)
            count += multPos.size() + multNeg.size();
        else if (pow[i] > 0)
        {
            count += multNeg.size();
            auto bound = std::lower_bound(multPos.begin(), multPos.end(), pow[i]);
            if (bound != multPos.end())
            {
                if (*bound == pow[i])
                {
                    ++count;
                    count += 2*(multPos.end() - bound - 1);
                }
                else
                    count += 2*(multPos.end() - bound);
            }
        }
        else
        {
            count += multPos.size();
            auto bound = std::lower_bound(multNeg.begin(), multNeg.end(), pow[i]);
            if (bound == multNeg.end())
                count += 2*(long long)multNeg.size();
            else
            {
                if (*bound == pow[i])
                    ++count;
                count += 2*(bound - multNeg.begin());
            }
        }
    }

    for (int i = 0; i < (int)mult.size(); ++i)
    {
        auto divIt = std::lower_bound(div.begin(), div.end(), mult[i]);
        if (divIt == div.end() || *divIt != mult[i])
            continue;
        auto powIt = std::lower_bound(pow.begin(), pow.end(), mult[i]);
        if (powIt == pow.end() || *powIt != mult[i])
            continue;
        count -= 2;
    }

    printf("%lld", count);

    return 0;
}