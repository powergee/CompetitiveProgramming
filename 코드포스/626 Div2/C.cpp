#include <iostream>
#include <string>

int n;
std::string str;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n;
    std::cin >> str;

    int cost = 0;
    int start = -1;
    int count = 0;

    for (int i = 0; i < (int)str.size(); ++i)
    {
        count += (str[i] == ')' ? 1 : -1);

        if (count > 0 && start == -1)
            start = i;

        else if (start != -1 && count == 0)
        {
            cost += i - start + 1;
            start = -1;
        }
    }

    if (count != 0)
        printf("-1");
    else printf("%d", cost);

    return 0;
}