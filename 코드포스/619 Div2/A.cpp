#include <iostream>
#include <string>

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        std::string a, b, c;
        std::cin >> a >> b >> c;

        bool result = true;
        for (int i = 0; i < a.size() && result; ++i)
        {
            if (a[i] == b[i])
            {
                if (c[i] != a[i])
                    result = false;
            }

            else if (a[i] != c[i] && b[i] != c[i])
                result = false;
        }

        if (result)
            printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}