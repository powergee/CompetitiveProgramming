#include <iostream>
#include <set>

std::set<std::string> haventHeard;
std::set<std::string> result;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::string input;
    std::cin >> n >> m;

    while (n--)
    {
        std::cin >> input;
        haventHeard.insert(input);
    }
    
    while (m--)
    {
        std::cin >> input;
        if (haventHeard.find(input) != haventHeard.end())
            result.insert(input);
    }

    std::cout << result.size() << '\n';
    for (auto name : result)
        std::cout << name << '\n';

    return 0;
}