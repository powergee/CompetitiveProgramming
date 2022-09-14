#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

std::vector<int> getFail(std::vector<int>& str)
{
    std::vector<int> fail(str.size(), 0);
    for (int i = 1, j = 0; i < (int)str.size(); ++i)
    {
        while (j > 0 && str[i] != str[j])
            j = fail[j-1];
        if (str[i] == str[j])
            fail[i] = ++j;
    }

    return fail;
}

int main()
{
    int n;
    std::vector<int> history;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int val;
        scanf("%d", &val);
        history.push_back(val);
    }

    std::reverse(history.begin(), history.end());
    std::vector<int> fail = getFail(history);

    int ans = n, p = 1;
    for (int i = 0; i < n; ++i)
    {
        if (n-fail[i] < ans)
        {
            ans = n-fail[i];
            p = i-fail[i]+1;
        }
    }
    printf("%d %d", ans-p, p);

    return 0;
}