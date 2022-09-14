#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> getFail(std::string& str)
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
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    while (true)
    {
        std::string input;
        std::cin >> input;

        if (input == ".")
            break;

        std::vector<int> fail = getFail(input);
        int pi = fail.back();
        int subLength = (int)input.size() - pi;
        if (pi == 0 || pi % subLength != 0)
            printf("1\n");
        else
            printf("%d\n", (int)input.size() / subLength);
    }

    return 0;
}