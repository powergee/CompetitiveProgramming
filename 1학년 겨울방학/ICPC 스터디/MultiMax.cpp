#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> pos;
std::vector<int> neg;
bool hasZero;

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int num;
        scanf("%d", &num);

        if (num == 0)
            hasZero = true;
        else if (num < 0)
            neg.push_back(num);
        else
            pos.push_back(num);
    }

    std::sort(pos.begin(), pos.end());
    std::sort(neg.begin(), neg.end());

    std::vector<int> cases;
    if (hasZero)
        cases.push_back(0);
    
    if (neg.size() > 1)
        cases.push_back(neg[0] * neg[1]);
    
    if (pos.size() > 1)
        cases.push_back(pos[pos.size() - 1] * pos[pos.size() - 2]);

    if (!pos.empty() && !neg.empty())
        cases.push_back(pos[0] * neg[neg.size() - 1]);

    if (pos.size() > 2)
        cases.push_back(pos[pos.size() - 1] * pos[pos.size() - 2] * pos[pos.size() - 3]);

    if (!pos.empty() && neg.size() > 1)
        cases.push_back(pos[pos.size() - 1] * neg[0] * neg[1]);
    
    if (!neg.empty() && pos.size() > 1)
        cases.push_back(neg[neg.size() - 1] * pos[0] * pos[1]);

    if (neg.size() > 2)
        cases.push_back(neg[neg.size() - 1] * neg[neg.size() - 2] * neg[neg.size() - 3]);

    printf("%d", *(std::max_element(cases.begin(), cases.end())));
    return 0;
}