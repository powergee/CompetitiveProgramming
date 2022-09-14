#include <iostream>
#include <map>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        std::map<std::string, int> clothes;
        int n;
        std::cin >> n;

        while (n--)
        {
            std::string name, kind;
            std::cin >> name >> kind;

            if (clothes.find(kind) == clothes.end())
                clothes[kind] = 1;
            else ++clothes[kind];
        }

        int result = 1;
        for (auto& count : clothes)
            result *= count.second + 1;
        std::cout << result - 1 << '\n';
    }

    return 0;
}