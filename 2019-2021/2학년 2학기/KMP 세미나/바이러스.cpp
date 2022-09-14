#include <iostream>
#include <algorithm>
#include <vector>

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

void KMP(std::vector<int>& para, std::vector<int>& target, std::vector<int>& fail, std::vector<int>& found)
{
    fail = getFail(target);
    found.clear();

    for (int i = 0, j = 0; i < (int)para.size(); ++i)
    {
        while (j > 0 && para[i] != target[j])
            j = fail[j-1];
        if (para[i] == target[j])
        {
            if (j == (int)target.size()-1)
            {
                found.push_back(i-target.size()+2);
                j = fail[j];
            }
            else j++;
        }
    }
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    std::vector<std::vector<int>> codes(2*n);

    for (int i = 0; i < n; ++i)
    {
        int length;
        scanf("%d", &length);
        for (int j = 0; j < length; ++j)
        {
            int val;
            scanf("%d", &val);
            codes[2*i].push_back(val);
        }
        codes[2*i+1] = codes[2*i];
        std::reverse(codes[2*i+1].begin(), codes[2*i+1].end());
    }

    for (int c = 0; c < 2; ++c)
    {
        for (int i = 0; i <= (int)codes[c].size() - k; ++i)
        {
            std::vector<int> subCode = std::vector<int>(codes[c].begin() + i, codes[c].begin() + i + k);
            bool success = true;

            for (int j = 1; j < n && success; ++j)
            {
                std::vector<int> fail1, fail2;
                std::vector<int> found1, found2;
                KMP(codes[2*j], subCode, fail1, found1);
                KMP(codes[2*j+1], subCode, fail2, found2);
                success = !found1.empty() || !found2.empty();
            }

            if (success)
            {
                printf("YES");
                return 0;
            }
        }
    }

    printf("NO");
    return 0;
}