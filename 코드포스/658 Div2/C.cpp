#include <iostream>
#include <string>
#include <vector>

bool getFrom(int flipCount, int lastFlip, std::vector<bool> from)
{
    if (flipCount % 2)
    {
        
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        int n;
        std::string fromStr, toStr;
        std::cin >> n >> fromStr >> toStr;

        std::vector<bool> from, to;
        for (char ch : fromStr)
            from.push_back(ch == '1');
        for (char ch : toStr)
            to.push_back(ch == '1');

        std::vector<int> inst;
        bool flipCount = 0;
        int lastFlip = 0;
        for (int i = n-1; i >= 0; --i)
        {
        }

        std::cout << inst.size() << ' ';
        for (int i : inst)
            std::cout << i << ' ';
        std::cout << '\n';
    }

    return 0;
}